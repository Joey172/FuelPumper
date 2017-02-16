/*
 * Pickup.h
 *
 *  Created on: Jan 24, 2017
 *      Author: Joey
 */

#ifndef SRC_PICKUP_H_
#define SRC_PICKUP_H_

#include <WPILib.h>
#include <CANTalon.h>
#include "RobotMap.h"

class Pickup {
	frc::Joystick& m_leftStick;
	int pickupButton;
	// Intake Motor picks up balls
	frc::Talon& m_intakeMotor;
	// Hopper Motor pushs into Hopper
	frc::Talon& m_hopperMotor;
	PowerDistributionPanel m_pdp;

public:
	Pickup(
		frc::Joystick &
		, int
		,frc::Talon &
		,frc::Talon &
		);
	void TeleopInit();
	void TeleopPeriodic();
	virtual ~Pickup();
	//Chose between 2 speeds to intake the Fuel
	void Intake();
	void stop();
	void Reverse();
};

#endif /* SRC_PICKUP_H_ */

