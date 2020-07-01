#include "Globals.h"
#include "../ROBOTCtoC++/RobotC.h"
#include <iostream>
#include <cmath>

#ifndef GLOBALS_SOURCE
#define GLOBALS_SOURCE


// Globals
tMotor leftMotorPort;
tSensors leftEncoderPort;
tMotor rightMotorPort;
tSensors rightEncoderPort;

ubyte taskDelay;
float maxSpeed;


// Setters
void SetLeftMotor(tMotor port) {
	leftMotorPort = port;
}


void SetRightMotor(tMotor port) {
	rightMotorPort = port;
}


void SetLeftEncoder(tSensors port) {
	leftEncoderPort = port;
}


void SetRightEncoder(tSensors port) {
	rightEncoderPort = port;
}


void SetMaxSpeed(float speed) {
	if(speed <= 1) {
		maxSpeed = speed;
	}
}


void SetAverageDelay(ubyte delayTime) {
	taskDelay = delayTime;
}


// Getters
tMotor GetLeftMotor(){
	return leftMotorPort;
}


tMotor GetRightMotor(){
	return rightMotorPort;
}


tSensors GetLeftEncoder(){
	return leftEncoderPort;
}


tSensors GetRightEncoder(){
	return rightEncoderPort;
}


ubyte GetDelay() {
	return taskDelay;
}


double GetMaxSpeed(){
	return maxSpeed;
}


#endif
