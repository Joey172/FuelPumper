/*
 * Shooter.h
 *
 *  Created on: Jan 16, 2017
 *      Author: Joey
 */

#ifndef SRC_SHOOTER_H_
#define SRC_SHOOTER_H_

#include <WPILib.h>
#include <CANTalon.h>
#include "RobotMap.h"


class Shooter {
	CANTalon& m_shootWheel1;
	CANTalon& m_shootWheel2;
	CANTalon& m_indexMotor;
	frc::DigitalOutput& m_aimLight;

	//	int m_shootButton;
	//	frc::Joystick& m_joystickForShootButton;
	//	int m_reverseIndexButton;
	//	frc::Joystick& m_joystickForReverseIndexButton;
	//	int m_aimingLightButton;
	//	frc::Joystick& m_joystickForAimingLightButton;

	frc::JoystickButton& shootJoystickButton;
	frc::JoystickButton& reverseIndexJoystickButton;
	frc::JoystickButton& aimingLightJoystickButton;

	PowerDistributionPanel m_pdp;

	float m_shooterSpeed;

public:
	Shooter(
			CANTalon &m_shootWheel1
			, CANTalon &m_shootWheel2
			, CANTalon &m_indexMotor
			, frc::DigitalOutput &m_aimLight
			, frc::JoystickButton &shootJoystickButton
			, frc::JoystickButton &reverseIndexJoystickButton
			, frc::JoystickButton &aimingLightJoystickButton
			, float m_shooterSpeed
	);
	virtual ~Shooter();
	void TeleopInit();
	void TeleopPeriodic();

	//Want to allow it to activate shooter motors let
	//then get up to speed then activate index motor
	void Shoot(float);
	void Stop();
	void ReverseIndex();
	void Init();
	void AimLight(bool state);

};

#endif /* SRC_SHOOTER_H_ */
