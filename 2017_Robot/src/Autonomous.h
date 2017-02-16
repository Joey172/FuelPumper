/*
 * Autonomous.h
 *
 *  Created on: Feb 13, 2017
 *      Author: Joey
 */
#include <WPILib.h>

#ifndef SRC_AUTONOMOUS_H_
#define SRC_AUTONOMOUS_H_
#include "Vision.h"

class Autonomous {
	Vision m_vision;
public:
	Autonomous();
	virtual ~Autonomous();

	void AutonomousPeriodic();
	void AutonomousInit();
};

#endif /* SRC_AUTONOMOUS_H_ */
