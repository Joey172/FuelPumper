/*
 * Vision.cpp
 *
 *  Created on: Feb 7, 2017
 *      Author: Joey
 */

#include <Vision.h>

Vision::Vision() {
	// TODO Auto-generated constructor stub

}

Vision::~Vision() {
	// TODO Auto-generated destructor stub
}

void Vision::Init() {
	m_camera = CameraServer::GetInstance()->StartAutomaticCapture("Vision", 0);
	m_camera.SetExposureManual(Preferences::GetInstance()->GetFloat("Exposure", 1));
}

void Vision::SwitchCamera(int camID) {
	//CameraServer::GetInstance()->RemoveCamera(camName);
	CameraServer::GetInstance()->RemoveServer("serve_Vision");
	m_camera = CameraServer::GetInstance()->StartAutomaticCapture("Vision", camID);
}
