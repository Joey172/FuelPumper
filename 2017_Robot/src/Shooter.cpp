/*
 * Shooter.cpp
 *
 *  Created on: Jan 16, 2017
 *      Author: Joey
 */


#include "Shooter.h"
#include "RobotMap.h"

Shooter::Shooter(
		CANTalon* m_shootWheel1
		, CANTalon* m_shootWheel2
		, CANTalon* m_indexMotor
		, frc::Talon* m_shooterFeeder
		, OI *oi
		, CI *ci
		, frc::DigitalOutput* m_aimLight
		, frc::JoystickButton* joystickButton_shoot
		, frc::JoystickButton* joystickButton_reverseIndex
		, frc::JoystickButton* joystickButton_aimingLight
		, float m_shooterSpeed
)
	:
	m_particleAccelerator(m_shootWheel1)
	, m_afterBurner(m_shootWheel2)
	, m_indexMotor(m_indexMotor)
	, m_aimLight(m_aimLight)
	, m_OI(oi)
	, m_CI(ci)
	, joystickButton_shoot(joystickButton_shoot)
	, joystickButton_reverseIndex(joystickButton_reverseIndex)
	, joystickButton_aimingLight(joystickButton_aimingLight)
	, m_shooterSpeed(m_shooterSpeed)
	, m_shooterFeeder(m_shooterFeeder)
{
	m_shootWheel1->SetControlMode(frc::CANSpeedController::kSpeed);
	m_shootWheel2->SetControlMode(frc::CANSpeedController::kSpeed);
	m_indexMotor->SetControlMode(frc::CANSpeedController::kSpeed);
}

Shooter::~Shooter() {
	// TODO Auto-generated destructor stub
}

void Shooter::TeleopInit() {
	float P = SmartDashboard::GetNumber("Shooter P", 0);
	float I = SmartDashboard::GetNumber("Shooter I", 0);
	float D = SmartDashboard::GetNumber("Shooter D", 0);
	float F = SmartDashboard::GetNumber("Shooter F", 0);
	m_particleAccelerator->SetPID(P, I, D, F);
	m_afterBurner->SetPID(P, I, D, F);
}

void Shooter::TeleopPeriodic() {
	static bool firstTime = true;
	static Timer pickupTimer;
	if(firstTime) {
		pickupTimer.Start();
	}

	static bool pickingUp = false;
	if (joystickButton_shoot->Get() || m_OI->joyStickButton_adjShoot->Get()) {
		m_particleAccelerator->SetControlMode(CANTalon::ControlMode::kSpeed);
		m_afterBurner->SetControlMode(CANTalon::ControlMode::kSpeed);
		Shoot();
	}
	else if(m_OI->joystickButton_reverseIndex->Get()) {
		ReverseIndex();
	}
	else  {
		m_particleAccelerator->SetControlMode(CANTalon::ControlMode::kPercentVbus);
		m_afterBurner->SetControlMode(CANTalon::ControlMode::kPercentVbus);
		Stop();
	}

	SmartDashboard::PutBoolean("Shooter_ShootBtn", joystickButton_shoot->Get());
}


void Shooter::Shoot() {
	double IndexVoltageFactor = 1;
	double IndexMotorAmps = m_pdp.GetCurrent(4);
	SmartDashboard::PutNumber("Index Current", IndexMotorAmps);

	// TODO Figure out actual threshold
//	if (abs(IndexMotorAmps) > 7.5) {
//		IndexVoltageFactor -= .005;
//		SmartDashboard::PutBoolean ("Indexer Is Jammed.", true);
//	}
//	else {
//		SmartDashboard::PutBoolean ("Indexer Is Jammed.", false);
//		IndexVoltageFactor += .005;
//	}
	float ballsPS;
	float speedAdjust = 0;
	float sliderPos =  m_OI->joystick_manipulator->GetRawAxis(3);
	bool AdjBtn = m_OI->joyStickButton_adjShoot->Get();

	if(AdjBtn) {
		speedAdjust = 150 * (sliderPos);
	}

	const float acceleratorSpeed = 3200 - speedAdjust;
	const float afterBurnerSpeed = 3800 - speedAdjust; //was 3550
	float paSpeed = m_particleAccelerator->GetSpeed();
	float abSpeed = m_afterBurner->GetSpeed();

	SmartDashboard::PutNumber("PASpeed", fabs(paSpeed));
	SmartDashboard::PutNumber("ABSpeed", fabs(abSpeed));

	m_particleAccelerator->SetSetpoint(acceleratorSpeed);
	m_afterBurner->SetSetpoint(afterBurnerSpeed);
	static bool firstTime = true;
	static Timer pickupTimer;

	static bool pickingUp = false;
	if (fabs(fabs(paSpeed)-fabs(acceleratorSpeed))<=150 && fabs(fabs(abSpeed)-fabs(afterBurnerSpeed)) <= 150) {
		ballsPS = Preferences::GetInstance()->GetDouble("IndexBallsPS", 4);
		SetIndexer(ballsPS);

		//Pulse pickup.
		if(firstTime) {
			pickupTimer.Start();
		}

		if(pickupTimer.Get() >= 1) {
			m_CI->canTalon_hopper->Set(-1);
			m_CI->canTalon_intake->Set(-1);
			pickingUp = true;
			pickupTimer.Reset();
		}
		if (pickingUp == true && pickupTimer.Get() >= 0.5) {
			m_CI->canTalon_hopper->Set(0);
			m_CI->canTalon_intake->Set(0);
		}
	}
}

void Shooter::SetIndexer(float speed) {
	speed *= 15;
	m_indexMotor->SetSetpoint(speed);
	m_shooterFeeder->Set(.5);
}

void Shooter::ReverseIndex() {
	m_indexMotor->SetSetpoint(-20);
}


void Shooter::Stop() {
	m_particleAccelerator->SetSetpoint(0);
	m_afterBurner->SetSetpoint(0);
	m_indexMotor->SetSetpoint(0);
	m_shooterFeeder->Set(0);
}

void Shooter::Init() {
	m_particleAccelerator->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Relative);
	m_afterBurner->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Relative);
	m_indexMotor->SetFeedbackDevice(CANTalon::CtreMagEncoder_Relative);

	m_particleAccelerator->ConfigEncoderCodesPerRev(4096);
	m_afterBurner->ConfigEncoderCodesPerRev(4096);

	m_particleAccelerator->SetVelocityMeasurementPeriod(CANTalon::VelocityMeasurementPeriod::Period_1Ms);
	m_afterBurner->SetVelocityMeasurementPeriod(CANTalon::VelocityMeasurementPeriod::Period_1Ms);
	m_particleAccelerator->SetVelocityMeasurementWindow(16);
	m_afterBurner->SetVelocityMeasurementWindow(16);

	m_particleAccelerator->SetSensorDirection(false);
	m_afterBurner->SetSensorDirection(false);
	m_particleAccelerator->SetInverted(true);
	m_afterBurner->SetInverted(true);
	m_particleAccelerator->SetControlMode(frc::CANSpeedController::kSpeed);
	m_afterBurner->SetControlMode(frc::CANSpeedController::kSpeed);

	m_indexMotor->SetControlMode(frc::CANSpeedController::kSpeed);

	m_particleAccelerator->SetPID(.5, 0, 0, 0.028);
	m_afterBurner->SetPID(.5, 0, 0, 0.028);
	m_particleAccelerator->SetIzone(4000);
	m_afterBurner->SetIzone(4000);

	m_indexMotor->SetPID(2,0,0, 1);
	m_indexMotor->ConfigPeakOutputVoltage(+12,-12);
	m_indexMotor->SetVoltageRampRate(50);
	//the encoder is on backwards
	m_indexMotor->SetSensorDirection(true);
	m_indexMotor->ConfigEncoderCodesPerRev(4096);

	m_indexMotor->SetSetpoint(0);
	m_particleAccelerator->SetSetpoint(0);
	m_afterBurner->SetSetpoint(0);

	SmartDashboard::PutNumber("Shooter P", 0.5);
	SmartDashboard::PutNumber("Shooter I", 0);
	SmartDashboard::PutNumber("Shooter D", 0);
	SmartDashboard::PutNumber("Shooter F", 0.028);
}
void Shooter::Spinup() {
	const float acceleratorSpeed = -3150;
	const float afterBurnerSpeed = -3550;

	m_particleAccelerator->SetSetpoint(acceleratorSpeed);
	m_afterBurner->SetSetpoint(afterBurnerSpeed);
}
void Shooter::AimLight(bool state) {

	if(state)
		m_aimLight->UpdateDutyCycle(0.7);
	else
		m_aimLight->UpdateDutyCycle(0);

}
