/*
 * Vision.cpp
 *
 *  Created on: Feb 13, 2017
 *      Author: administrator
 */

#include <Vision.h>
#include <vector>
#include <CameraServer.h>
using namespace std;
Vision::Vision() {
	// TODO Auto-generated constructor stub

}

Vision::~Vision() {
	// TODO Auto-generated destructor stub
}
void Vision::Init() {
	camera = m_cameraServer->StartAutomaticCapture(0);
	//m_outputStream = CameraServer::GetInstance()->PutVideo("thresh", 640, 480);
	camera.SetResolution(640, 480);
	camera.SetExposureManual(1);
}

void Vision::TeleopInit() {

}

void Vision::TeleopPeriodic() {

}

double Vision::GetCorrectionDistance() {
	cv::Mat frame;

	m_cameraServer->GetVideo().GrabFrame(frame);
	m_boilerVision.process(frame);

	std::vector<std::vector<cv::Point>> *foundContours
		= m_boilerVision.getfindContoursOutput();

	if(foundContours == nullptr) {
		return 0;
	}

	// Moments of countours.
	vector<cv::Moments> mu(foundContours->size());

	// Centor of the contours.
	vector<cv::Point2f> momentCenters(foundContours->size());

	cv::Rect boundingRect = {-1,-1,-1,-1};

	for(unsigned i = 0; i < foundContours->size(); i++) {
		mu[i] = moments( foundContours[i], false );
		momentCenters[i]
			= cv::Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);

		boundingRect = cv::boundingRect(foundContours[i]);

		printf("Found Contour %i:", i);
		printf("  Center:\n\tx: %f, y: %f\n", momentCenters[i].x, momentCenters[i].y);
		printf("  Bounding Rect:\n\tX: %i, Y: %i, W: %i, H: %i\n\n",
				boundingRect.x, boundingRect.y, boundingRect.width, boundingRect.height);
	}

	// TODO actually calculate and return distance.
	return 0;
}
