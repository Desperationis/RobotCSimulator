/*****************************************************************//**
 * \file   RobotC.h
 * \brief  A file that deals with binding RobotC into C++.
 * 
 * \author smart
 * \date   July 2020
 *********************************************************************/

#pragma once
#include <SFML/Graphics.hpp>
#include "stdafx.h"

namespace RobotC {
	namespace Types {
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

		typedef void task;
		typedef signed char byte;
		typedef unsigned char ubyte;
		typedef short tMotor;
		typedef short tSensors;
	};

	namespace Peripherals {
		static std::array<int, 10> motor;
		static std::array<int, 50> SensorValue;
		static std::array<int, 20> vexRT;

		static void config(std::string name, Types::MotorPort& motorPort, Types::MotorPort port, bool reverse) {
			motorPort = port;
		}

		static void config(std::string name, Types::SensorPort& sensorPort, Types::SensorPort port) {
			sensorPort = port;
		}
	}

	namespace Threads {
		static std::vector<std::unique_ptr<std::thread>> threads;
		static bool active = true;


		static void delay(int ms) {
			std::this_thread::sleep_for(std::chrono::milliseconds(ms));
		}

		static void startTask(std::function<Types::task()> func) {
			threads.push_back(std::make_unique<std::thread>(func));
		}
	}

	namespace Functions {

		static int sgn(int input) {
			if (input < 0) {
				return -1;
			}
			if (input > 0) {
				return 1;
			}

			return 0;
		}
	
	}
};




