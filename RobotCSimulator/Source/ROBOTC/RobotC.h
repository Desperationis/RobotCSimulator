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
 * Provides RobotC enumerations, functions, and variables.
 */

typedef void task;

enum MotorPort { port1, port2, port3, port4, port5, port6, port7, port8, port9, port10 };
enum VexRt { Btn5U, Btn5D, Btn6U, Btn6D, Btn7L, Btn7R, Btn7U, Btn7D, Btn8L, Btn8R, Btn8U, Btn8D, Ch1, Ch2, Ch3, Ch4};

struct MotorInfo {
	std::string name;
	bool reversed;

	MotorInfo(std::string _name, bool _reversed) {
		name = _name;
		reversed = _reversed;
	}
};

extern std::vector<std::unique_ptr<std::thread>> threads;
extern std::array<int, 10> motor;
extern std::array<std::unique_ptr<MotorInfo>, 10> motorInfo;
extern std::array<int, 16> vexRT;

// Currently, these functionalities are not supported:
//			stopTask()
//			stopAllTasks()
void startTask(std::function<task()> func);
void delay(int ms);
void config(std::string name, MotorPort& motorPort, MotorPort port, bool reversed = false);