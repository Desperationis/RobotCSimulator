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
			port1,	port2,	port3,
			port4,	port5,	port6,
			port7,	port8,	port9,
			port10, MAX_MOTOR_PORT
		};

		enum SensorPort {
			// Digital Ports
			dgtl1,	dgtl2,	dgtl3,
			dgtl4,	dgtl5,	dgtl6,
			dgtl7,	dgtl8,	dgtl9,
			dgtl10,	dgtl11,	dgtl12,

			// Analog Ports
			in1,	in2,	in3,
			in4,	in5,	in6,
			in7,	in8, MAX_SENSOR_PORT
		};

		enum VexRT {
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
			Ch4,   // Left X Axis
			MAX_VEX_RT_PORT
		};

		// Types
		typedef void task;
		typedef signed char byte;
		typedef unsigned char ubyte;
		typedef short tMotor;
		typedef short tSensors;

		// Map to enumeration name
		extern std::map<MotorPort, const char*> motorPortMap;
		extern std::map<SensorPort, const char*> sensorPortMap;
		extern std::map<VexRT, const char*> vexRTPortMap;
	};

	namespace Peripherals {
		// Holds peripheral values.
		extern std::array<Types::byte, Types::MAX_MOTOR_PORT> motor;
		extern std::array<int16_t, Types::MAX_SENSOR_PORT> SensorValue;
		extern std::array<Types::byte, Types::MAX_VEX_RT_PORT> vexRT;


		struct MotorInfo {
			Types::MotorPort motorPort;
			std::string name;
			bool reversed;
		};

		struct SensorInfo {
			Types::SensorPort sensorPort;
			std::string name;
		};

		// Holds configuration information.
		extern std::map<Types::MotorPort, MotorInfo> motorConfigInfo;
		extern std::map<Types::SensorPort, SensorInfo> sensorConfigInfo;

		static void config(std::string name, Types::MotorPort& motorPort, Types::MotorPort port, bool reverse) {
			// Assign the reference to the port.
			motorPort = port;

			// Write down that configuration information for later.
			MotorInfo configInfo;
			configInfo.motorPort = motorPort;
			configInfo.reversed = reverse;
			configInfo.name = name;
			motorConfigInfo[motorPort] = configInfo;
		}

		static void config(std::string name, Types::SensorPort& sensorPort, Types::SensorPort port) {
			// Assign the reference to the port.
			sensorPort = port;

			// Write down that configuration information for later.
			SensorInfo configInfo;
			configInfo.sensorPort = sensorPort;
			configInfo.name = name;
			sensorConfigInfo[sensorPort] = configInfo;
		}
	}

	namespace Threads {
		extern std::vector<std::unique_ptr<std::thread>> threads;
		extern bool killAll;

		static void delay(int ms) {
			std::this_thread::sleep_for(std::chrono::milliseconds(ms));
		}

		static void startTask(std::function<Types::task()> func) {
			if(threads.size() < 20) {
				threads.push_back(std::make_unique<std::thread>(func));
			}
			else {
				printf("RobotC.h: The maximum number of tasks (20) has already been reached!");
			}
		}

		static void stopAllTasks() {
			killAll = true;
		}
	}

	namespace Functions {
		/**
		 * Template function to increment a continous
		 * enumeration. Can fail when enumeration isn't
		 * continous (e.x. enum1 = 0, enum2 = 1, enum 3 = 5)
		 *
		 * \param enumeration - An enumeration, of any kind!
		 * \return The next enumeration.
		 */
		template <class T>
		T IncrementEnum(T enumeration) {
			int increment = static_cast<int>(enumeration) + 1;
			return static_cast<T>(increment);
		}



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


