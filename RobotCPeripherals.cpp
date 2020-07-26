#include "RobotC.h"

using namespace RobotC::Types;
using namespace RobotC::Peripherals;

std::array<byte, MAX_MOTOR_PORT>          RobotC::Peripherals::motor;
std::array<int16_t, MAX_SENSOR_PORT>      RobotC::Peripherals::SensorValue;
std::array<byte, MAX_VEX_RT_PORT>         RobotC::Peripherals::vexRT;

std::map<MotorPort, MotorInfo>            RobotC::Peripherals::motorConfigInfo;
std::map<SensorPort, SensorInfo>          RobotC::Peripherals::sensorConfigInfo;


void RobotC::Peripherals::config(std::string name, MotorPort& motorPort, MotorPort port, bool reverse) {
	// Assign the reference to the port.
	motorPort = port;

	// Write down that configuration information for later.
	MotorInfo configInfo;
	configInfo.motorPort = motorPort;
	configInfo.reversed = reverse;
	configInfo.name = name;
	motorConfigInfo[motorPort] = configInfo;
}

void RobotC::Peripherals::config(std::string name, SensorPort& sensorPort, SensorPort port) {
	// Assign the reference to the port.
	sensorPort = port;

	// Write down that configuration information for later.
	SensorInfo configInfo;
	configInfo.sensorPort = sensorPort;
	configInfo.name = name;
	sensorConfigInfo[sensorPort] = configInfo;
}

