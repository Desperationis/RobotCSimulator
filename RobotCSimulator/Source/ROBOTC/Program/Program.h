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
	config("rightMotor", rightMotor, port2, true);
}

task MotorSpeed();
task programMain() {
	SetAverageDelay(20);
	SetLeftMotor(port1);
	SetRightMotor(port2);
	SetLeftEncoder(leftEncoder);
	SetRightEncoder(rightEncoder);
	SetControllerSpeed(1);


	startTask(MotorSpeed);


	while(true) {
		// Keep program alive.
		delay(GetDelay());
	}
}

task MotorSpeed() {
	while(true){
		if(abs(SensorValue[leftEncoder]) > 300){
			motor[leftMotor] = 0;
			break;
		}

		motor[leftMotor] = 127;

		delay(GetDelay());
	}
}
