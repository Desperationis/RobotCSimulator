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
	startTask(GamerControl);
	startTask(MotorSpeed);

	while(true) {
		// Keep program alive.
		delay(20);
	}
}

task MotorSpeed() {
	while(true){
		if(vexRT[Btn8D]){
			SetControllerSpeed(2);
		}
		else {
			SetControllerSpeed(1);
		}

		delay(GetDelay());
	}
}
