#pragma once
#include <string>
using namespace std;

/*
 * UnitTestAttacher.h
 *
 * Provides functions, typedefs, and enumerations that attach to RobotC code for unit testing.
 *
 */

// Define incompatible types.
typedef int byte;
typedef void task;

// Define incompatible enumerations.
enum SensorType { Motor };
enum MotorType{ tmotorVex393_HBridge , tmotorVex393_MC29};
enum Ports{port1, port2, port3, port4, port5, port6, port7, port8};
enum Misc { openLoop };

// Configure unit tester's "ports" for motors.
void configMotor(SensorType sensorType, Ports port, string, MotorType, Misc) {

}