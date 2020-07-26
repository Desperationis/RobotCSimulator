#include "RobotC.h"

using namespace RobotC::Types;

std::map<MotorPort, const char*> RobotC::Types::motorPortMap = {
	{port1,  "port1"},
	{port2,  "port2"},
	{port3,  "port3"},
	{port4,  "port4"},
	{port5,  "port5"},
	{port6,  "port6"},
	{port7,  "port7"},
	{port8,  "port8"},
	{port9,  "port9"},
	{port10, "port10"},
};

std::map<SensorPort, const char*> RobotC::Types::sensorPortMap = {
	{dgtl1,  "dgtl1"},
	{dgtl2,  "dgtl2"},
	{dgtl3,  "dgtl3"},
	{dgtl4,  "dgtl4"},
	{dgtl5,  "dgtl5"},
	{dgtl6,  "dgtl6"},
	{dgtl7,  "dgtl7"},
	{dgtl8,  "dgtl8"},
	{dgtl9,  "dgtl9"},
	{dgtl10, "dgtl10"},
	{dgtl11, "dgtl11"},
	{dgtl11, "dgtl11"},
	{dgtl12, "dgtl12"},

	{in1, "int1"},
	{in2, "int2"},
	{in3, "int3"},
	{in4, "int4"},
	{in5, "int5"},
	{in6, "int6"},
	{in7, "int7"},
	{in8, "int8"},
};

std::map<VexRT, const char*> RobotC::Types::vexRTPortMap = {
	{Btn5U, "Btn5U"},
	{Btn5D, "Btn5D"},
	{Btn6U, "Btn6U"},
	{Btn6D, "Btn6D"},
	{Btn7L, "Btn7L"},
	{Btn7R, "Btn7R"},
	{Btn7U, "Btn7U"},
	{Btn7D, "Btn7D"},
	{Btn8L, "Btn8L"},
	{Btn8R, "Btn8R"},
	{Btn8U, "Btn8U"},
	{Btn8D, "Btn8D"},
	{Ch1,   "Ch1"},
	{Ch2,   "Ch2"},
	{Ch3,   "Ch3"},
	{Ch4,   "Ch4"}
};
