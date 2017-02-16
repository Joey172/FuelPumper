/*
 * RobotMap.h
 *
 *  Created on: Jan 24, 2017
 *      Author: Joey
 *
 *      2017 Robot Map
 */


#ifndef SRC_ROBOTMAP_H_
#define SRC_ROBOTMAP_H_

enum ManStickMap {
	BUTTON_M_SHOOT = 5,
	BUTTON_M_LIMIT_SHOOT = 1,
	BUTTON_M_SPINUP = 2,
	BUTTON_M_REVERSEINDEX = 6, //TODO find real number for this.
	BUTTON_M_CLIMB = 7, //TODO find real number for this
	BUTTON_M_REVERSECLIMB = 8 //TODO find real number for this
};

enum LStickMap {
	BUTTON_L_PICKUP = 1,
	BUTTON_L_REVERSEPICKUP = 4, // TODO Figure out actual button value
	BUTTON_L_GEAR_RELEASE,
	BUTTON_L_SHIFT_LOW = 3,
	BUTTON_L_SHIFT_HIGH = 2,
	BUTTON_L_AIM_LIGHT = 5
};



enum RStickMap {
	BUTTON_R_REVERSE_DRIVE = 1,
	BUTTON_R_SET_SPEED_MODE = 10,
	BUTTON_R_SET_VBUS_MODE = 11,
	BUTTON_R_RELEASE_GEAR = 3
};

enum DS_USBMap {
	STICK_LEFT = 0,
	STICK_RIGHT = 1,
	STICK_MAN = 2,
};

enum DIOMap {
	LIGHT_AIM = 9,
	LIGHT_RUN_GUN = 8
};

enum SolenoidMap {
	SOLENOID_GEAR_SHIFT=0
};

enum CANTalonMap {
	MOTOR_RIGHT_DRIVE1 = 5,
	MOTOR_RIGHT_DRIVE2 = 6,
	MOTOR_LEFT_DRIVE1 = 7,
	MOTOR_LEFT_DRIVE2 = 8,
	MOTOR_SHOOT1 = 4,
	MOTOR_SHOOT2 = 3,
	MOTOR_SHOOT3 = 2,
	MOTOR_SHOOT4 = 1,
	MOTOR_INDEXER = 9,
	MOTOR_CLIMB = 10,
};

enum PWMMap {
	MOTOR_PICKUP_INTAKE = 0,
	MOTOR_PICKUP_HOPPER = 1,
	MOTOR_LEFT_GEAR_SERVO = 2,
	MOTOR_RIGHT_GEAR_SERVO = 3,
};

#endif /* SRC_ROBOTMAP_H_ */

