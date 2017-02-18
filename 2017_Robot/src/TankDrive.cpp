
/*
 * TankDrive.cpp
 *
 *  Created on: Jan 14, 2017
 *      Author: Joey
 */

#include "TankDrive.h"

TankDrive::TankDrive(
		frc::Joystick &m_leftStick
		,frc::Joystick &m_rightStick
		,frc::Solenoid &m_gearShift
		,CANTalon &m_leftMotor1
		,CANTalon &m_leftMotor2
		,CANTalon &m_rightMotor1
		,CANTalon &m_rightMotor2
	)
	:
	m_leftStick(m_leftStick)
	, m_rightStick(m_rightStick)
	, m_gearShift(m_gearShift)
	, m_leftMotor1(m_leftMotor1)
	, m_leftMotor2(m_leftMotor2)
	, m_rightMotor1(m_rightMotor1)
	, m_rightMotor2(m_rightMotor2)
{
	m_leftMotor1.SetControlMode(CANTalon::ControlMode::kPercentVbus);
	m_leftMotor1.ConfigEncoderCodesPerRev(120);
	m_leftMotor2.SetControlMode(CANTalon::ControlMode::kFollower);
	m_leftMotor2.ConfigEncoderCodesPerRev(120);
	m_rightMotor1.SetControlMode(CANTalon::ControlMode::kPercentVbus);
	m_rightMotor1.ConfigEncoderCodesPerRev(120);
	m_rightMotor2.SetControlMode(CANTalon::ControlMode::kFollower);
	m_rightMotor2.ConfigEncoderCodesPerRev(120);
	m_leftMotor2.Set(MOTOR_LEFT_DRIVE1);
	m_rightMotor2.Set(MOTOR_RIGHT_DRIVE1);
	m_leftMotor1.SetPID(1,0,0);
	m_rightMotor1.SetPID(1,0,0);
	direction = 1;
	highGear = true;
	leftPosOld = 0;
	rightPosOld = 0;
	m_xPosition = 0;
	m_yPosition = 0;
	distance = 0;
	angle = 0;
	heading = 0;
}

TankDrive::~TankDrive() {
 	 }

void TankDrive::TeleopInit() {
	SmartDashboard::PutNumber("robot x", 0);
	SmartDashboard::PutNumber("robot y", 0);
	m_leftMotor1.SetPosition(0);
	m_rightMotor1.SetPosition(0);
}
void TankDrive::TeleopPeriodic() {
	if (direction == 1 && m_rightStick.GetRawButton(BUTTON_R_REVERSE_DRIVE)) {
		direction = -1;
	} else if (direction == -1 && !m_rightStick.GetRawButton(BUTTON_R_REVERSE_DRIVE)) {
		direction = 1;
	}

	this->Drive(this->m_leftStick.GetY() * direction, this->m_rightStick.GetY() * direction);


	Position();
	float WheelSpeed = ((fabs(m_rightMotor1.GetSpeed())+fabs(m_leftMotor1.GetSpeed()))/60)/2;
	//^^above^^Gives us the average rotations per second of the two encoders

	float DriveSpeed = fabs((WheelSpeed*(4*3.1415))/12);
	//^^above^^Gives us speed in feet per second
	SmartDashboard::PutNumber("Drive Speed", DriveSpeed);
	if (DriveSpeed >= 6.4){
		TankDrive::HighGear();
	}

	if (this->highGear && m_leftStick.GetRawButton(BUTTON_L_SHIFT_LOW)){
		TankDrive::LowGear();
	}
	else if (!this->highGear && m_leftStick.GetRawButton(BUTTON_L_SHIFT_HIGH)){
		TankDrive::HighGear();
	}
}

void TankDrive::Position() {
	const float Circumference = 95.819;
	const float Pi = 3.141592;
	float rightPosition = m_rightMotor1.GetPosition()*(4*Pi);
	float leftPosition = -m_leftMotor1.GetPosition()*(4*Pi);
	SmartDashboard::PutNumber("leftPos", leftPosition);
	SmartDashboard::PutNumber("rightPos", rightPosition);
	SmartDashboard::PutNumber("LeftEncVal", m_leftMotor1.GetPosition());
	SmartDashboard::PutNumber("RightEncVal", m_rightMotor1.GetPosition());
	distance = ((rightPosition - rightPosOld)+(leftPosition - leftPosOld))/2;
	//this->angle += ((((rightPosition - rightPosOld)-(leftPosition - leftPosOld))/Circumference)*180);
	angle = m_gyro.GetAngle();
	m_yPosition = distance * cos((angle*Pi)/180) + m_yPosition;
	m_xPosition = (distance * sin((angle*Pi)/180) + m_xPosition);
	SmartDashboard::PutNumber("robot x", -m_xPosition);
	SmartDashboard::PutNumber("robot y", m_yPosition);
	SmartDashboard::PutNumber("robot angle", angle);
	rightPosOld = rightPosition;
	leftPosOld = leftPosition;
}

void TankDrive::Drive(const float leftVal, const float rightVal) {
	//left motor speed is inverted because the motors are physically opposite the right motors
	float left = leftVal, right = rightVal;
	if(direction == -1) {
		std::swap(left, right);
	}
	m_leftMotor1.SetSetpoint(right);
	m_rightMotor1.SetSetpoint(-left);
}

void TankDrive::LowGear() {
	m_gearShift.Set(false);
	this->highGear = false;

}

void TankDrive::HighGear() {
	m_gearShift.Set(true);
	this->highGear = true;
}

void TankDrive::PositionDrive(const float leftPos, const float rightPos) {

	m_leftMotor1.SetSetpoint(rightPos * m_countsPerInch);
	m_rightMotor1.SetSetpoint(-leftPos * m_countsPerInch);

	SmartDashboard::PutNumber("Tank_leftPos", leftPos * m_countsPerInch);
	SmartDashboard::PutNumber("Tank_rightPos", rightPos * m_countsPerInch);
}

void TankDrive::SpeedDrive(const float leftSpeed, const float rightSpeed) {
//	static Timer timer;
//	float dt = timer.Get();
//
//	if(dt > 0.025) {
//		dt = 0.025;
//	}
//
//	m_leftDistance += leftSpeed*dt;
//	m_rightDistance += rightSpeed*dt;
//
//	m_leftMotor1.Set(-m_leftDistance*m_countPerInch);
//	m_rightMotor1.Set(m_rightDistance*m_countPerInch);
//
//	timer.Reset();
//	timer.Start();
}

void TankDrive::SetMode(DriveMode mode){
	Zero();
	switch(mode){

	case DriveMode::SPEED:

		m_leftMotor1.SetControlMode(frc::CANSpeedController::kSpeed);
		m_rightMotor1.SetControlMode(frc::CANSpeedController::kSpeed);
		break;
	case DriveMode::POSITION:

		m_leftMotor1.SetControlMode(frc::CANSpeedController::kPosition);
		m_rightMotor1.SetControlMode(frc::CANSpeedController::kPosition);
		break;

	case DriveMode::VBUS:

		m_leftMotor1.SetControlMode(frc::CANSpeedController::kPercentVbus);
		m_rightMotor1.SetControlMode(frc::CANSpeedController::kPercentVbus);
		break;
	}
	m_leftMotor1.Set(0);
	m_rightMotor1.Set(0);
}

void TankDrive::Zero()
{
	m_leftMotor1.SetPosition(0.0);
	m_rightMotor1.SetPosition(0.0);
	m_leftMotor1.Set(0);
	m_rightMotor1.Set(0);
	m_leftDistance = 0;
	m_rightDistance = 0;
}
