#include <iostream>
#include <memory>
#include <string>

#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <WPILib.h>
#include "RobotMap.h"
#include "TankDrive.h"
#include "Pickup.h"
#include "BoilerVision.h"
#include "Vision.h"
using frc::SmartDashboard;
using namespace std;
using namespace frc;
class Robot: public frc::IterativeRobot {
	TankDrive m_tank;
	Vision m_vision;
	grip::BoilerVision m_boilerVision;
	CameraServer *cameraServer = nullptr;
	cs::CvSource m_outputStream;
	cs::UsbCamera camera;
	Pickup m_pickup;
	Joystick m_leftStick, m_rightStick;
public:
	Robot()
		: m_leftStick(1), m_rightStick(2)
	{

	}

	void RobotInit() {

	}

	void TeleopInit() {

	}

	void TeleopPeriodic() {
		m_tank.Drive(m_leftStick.GetY(), -m_rightStick.GetY());

		if(m_leftStick.GetRawButton(PICKUP)) {
			m_pickup.Intake(true);
		} else m_pickup.stop();


		if(m_leftStick.GetRawButton(CAMERA1)) {
			m_vision.SwitchCamera(0);
		}
		else if(m_leftStick.GetRawButton(CAMERA2)) {
			m_vision.SwitchCamera(1);
		}
	}

	void AutonomousInit() override {
		cameraServer = CameraServer::GetInstance();
		camera = cameraServer->StartAutomaticCapture();
		m_outputStream = CameraServer::GetInstance()->PutVideo("thresh", 640, 480);
		camera.SetResolution(640, 480);
		camera.SetExposureManual(1);
	}

	void AutonomousPeriodic() {
		cv::Mat frame;

		cameraServer->GetVideo().GrabFrame(frame);
		m_boilerVision.process(frame);
		std::vector<std::vector<cv::Point>> foundContours;
		foundContours = *m_boilerVision.getfindContoursOutput();

		vector<cv::Moments> mu(foundContours.size());

		vector<cv::Point2f> mc(foundContours.size());

		for( unsigned i = 0; i < foundContours.size(); i++ ) {
			mu[i] = moments( foundContours[i], false );
		}

		for(unsigned i = 0; i < foundContours.size(); i++) {
			mc[i] = cv::Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
		}

		for(unsigned i = 0; i < foundContours.size(); i++) {
			printf("Found Contours!:  x: %f, y: %f\n", mc[i].x, mc[i].y);
		}

//		cv::Mat contourImg;
//		cv::Mat mymat;
//		for(auto contour : foundContours) {
//			cv::drawContours(contourImg, contour, {255, 0, 0});
//			cv::Mat mymat = *Vision.gethsvThresholdOutput();
//		}
//		m_outputStream.PutFrame(mymat);
	}

	void TestPeriodic() {

	}
};

START_ROBOT_CLASS(Robot)
