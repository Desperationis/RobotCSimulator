#include "RobotC.h"

// Define external variables once
std::array<RobotC::Types::byte, 10> RobotC::Peripherals::motor;
std::array<int16_t, 20> RobotC::Peripherals::SensorValue;
std::array<RobotC::Types::byte, 16> RobotC::Peripherals::vexRT;

std::vector<std::unique_ptr<std::thread>> RobotC::Threads::threads;
bool RobotC::Threads::killAll = false;
