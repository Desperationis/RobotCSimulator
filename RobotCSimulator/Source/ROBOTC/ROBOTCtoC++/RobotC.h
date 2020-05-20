#pragma once
#include <thread>
#include <functional>
#include <array>
#include <vector>
#include <string>
#include <memory>

/*
 * RobotC.h
 *
 * Instantiates core RobotC variables and provides compatibility with my classes.
 */

// Typedefs
typedef void task;

// Ports
enum MotorPort { 
	port1, 
	port2, 
	port3,
	port4, 
	port5, 
	port6, 
	port7, 
	port8, 
	port9, 
	port10 
};

enum SensorPort { 
	// Digital Ports
	dgtl1, 
	dgtl2, 
	dgtl3, 
	dgtl4, 
	dgtl5, 
	dgtl6, 
	dgtl7, 
	dgtl8, 
	dgtl9, 
	dgtl10, 
	dgtl11, 
	dgtl12, 

	// Analog Ports
	in1, 
	in2, 
	in3, 
	in4, 
	in5, 
	in6, 
	in7, 
	in8
};

enum VexRt {
	// PS4 Controller Support
	Btn5U, // Left Bumper
	Btn5D, // Left Trigger
	Btn6U, // Right bumper
	Btn6D, // Right Trigger
	Btn7L, // Left hat
	Btn7R, // Right hat
	Btn7U, // Top hat
	Btn7D, // Bottom hat
	Btn8L, // Square
	Btn8R, // Circle
	Btn8U, // Triangle
	Btn8D, // X
	Ch1,   // Right X Axis
	Ch2,   // Right Y Axis
	Ch3,   // Left Y Axis
	Ch4    // Left X Axis
};

// Information Classes
struct MotorInfo {
	std::string name;
	bool reversed;

	MotorInfo(std::string _name, bool _reversed) {
		name = _name;
		reversed = _reversed;
	}
};

struct SensorInfo {
	std::string name;

	SensorInfo(std::string _name) {
		name = _name;
	}
};

// Pure RobotC Variables
extern std::array<short, 10> motor;
extern std::array<short, 20> SensorValue;
extern std::array<short, 16> vexRT;

// My own classes
extern std::vector<std::unique_ptr<std::thread>> threads;
extern std::array<std::unique_ptr<SensorInfo>, 20> sensorInfo;
extern std::array<std::unique_ptr<MotorInfo>, 10> motorInfo;

// RobotC Functions
void startTask(std::function<task()> func);
void delay(int ms);
void config(std::string name, MotorPort& motorPort, MotorPort port, bool reversed = false);
void config(std::string name, SensorPort& motorPort, SensorPort port);