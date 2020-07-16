#include "Globals.h"
#include "../RobotC.h"
#include "../stdafx.h"
using namespace RobotC::Types;
using namespace RobotC::Threads;
using namespace RobotC::Types;
using namespace RobotC::Peripherals;
using namespace RobotC::Functions;
#ifndef PID_HEADER
#define PID_HEADER


/*
 * PID.h
 *
 * PID system. Deals with controlling the chassis through a PID controller.
*/


typedef struct {
	float kP;
	float kI;
	float kD;
	short proportion;
	short integral;
	short derivative;
	short pastError;
} PIDInfo;


/*
 * Resets PID. Called by InitCustomLibrary() automatically.
*/
void InitPID();


/*
 * Sets kP, kI, and kD. Used to tune the PID.
*/
void SetK(float kP, float kI, float kD);


/*
 * Passively PID's chassis motors. Needs to be started to take effect.
*/
task PID();


/*
 * Calculate the motor speed of a motor given its encoder and information.
*/
short PIDCalculate(short encoderValue, short target, PIDInfo* info );


/*
 * Sets the target value of the left and right motors used in PID.
*/
void SetPIDTarget(MOTOR side, short targetValue);


/*
 * Allows the chassis to be controlled by PID. Motors and encoders
 * most be defined beforehand in Setup. By default, the chassis
 * aren't controlled by PID.
*/
void AllowPID(bool active);


/*
 * Returns whether or not the chassis is being controlled by PID or not.
*/
bool CanPID();

#endif
