/*
 * Vision.h
 *
 *  Created on: Feb 13, 2017
 *      Author: administrator
 */

#ifndef SRC_VISION_H_
#define SRC_VISION_H_

#include <WPILib.h>
#include "BoilerVision.h"
#include <CameraServer.h>
class Vision {
	CameraServer *m_cameraServer = nullptr;
	cs::CvSource m_outputStream;
	cs::UsbCamera camera;
	grip::BoilerVision m_boilerVision;


public:
	Vision();
	virtual ~Vision();
	void Init();
	void TeleopInit();
	void TeleopPeriodic();

	// Returns the distance the robot needs to move in order to shoot into the High Goal.
	double GetCorrectionDistance();
};

#endif /* SRC_VISION_H_ */
