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

extern std::vector<std::unique_ptr<std::thread>> threads;
extern std::array<int, 10> motors;

// Currently, these functionalities are not supported:
//			stopTask()
//			stopAllTasks()
void startTask(std::function<task()> func);
void delay(int ms);
void config(std::string name, MotorPort& motor, MotorPort port);