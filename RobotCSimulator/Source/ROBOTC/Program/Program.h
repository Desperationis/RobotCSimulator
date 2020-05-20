#include "../ROBOTCtoC++/RobotC.h"
#include "CLibrary.h"


SensorPort leftEncoder;
SensorPort rightEncoder;
MotorPort leftMotor;
MotorPort rightMotor;
void SetUp() {
	config("leftEncoder", leftEncoder, dgtl1);
	config("rightEncoder", rightEncoder, dgtl3);
	config("leftMotor", leftMotor, port1, false);
	config("rightMotor", rightMotor, port5, true);
}

task programMain() {
	ResetEncoders();

	SetLeftMotor(port1);
	SetRightMotor(port5);
	SetLeftEncoder(leftEncoder);
	SetRightEncoder(rightEncoder);
	SetAverageDelay(20);
	SetControllerSpeed(1);

	MoveUntil(2000, 127, 127);
	delay(4000);
	MoveUntil(500, -127, 127);
	delay(4000);
	MoveUntil(2000, 127, 127);

	while(true) {
		// Keep program alive.
		delay(GetDelay());
	}
}
