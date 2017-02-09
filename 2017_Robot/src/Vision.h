/*
 * Vision.h
 *
 *  Created on: Feb 7, 2017
 *      Author: Joey
 */

#ifndef SRC_VISION_H_
#define SRC_VISION_H_
#include <WPILib.h>
using namespace frc;

class Vision {
	cs::CvSource m_outputStream;
	cs::UsbCamera m_camera;
public:
	Vision();
	virtual ~Vision();
	void Init();
	void SwitchCamera(int camID);
};

#endif /* SRC_VISION_H_ */
