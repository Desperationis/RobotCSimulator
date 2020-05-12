#pragma once
#include <thread>
#include <functional>
#include <vector>
#include <memory>

/*
 * RobotC.h
 *
 * Provides RobotC enumerations, functions, and variables.
 */

typedef void task;

extern std::vector<std::unique_ptr<std::thread>> threads;

// Currently, these functionalities are not supported:
//			stopTask()
//			stopAllTasks()
void startTask(std::function<task()> func);
void delay(int ms);