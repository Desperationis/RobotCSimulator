#include "../RobotC.h"
#include "../stdafx.h"
#include "Externs.h"
using namespace RobotC::Types;
using namespace RobotC::Threads;
using namespace RobotC::Types;
using namespace RobotC::Peripherals;
using namespace RobotC::Functions;
#ifndef SETUP_HEADER
#define SETUP_HEADER

/*
 * Setup.h
 *
 * The place for setup functions and variables.
 * @setup Can be used in comments to tell RobotCDocs
 * whether a function should be under the Setup tag.
*/

/*
 * @setup
 *
 * Initializes the library. Should be called
 * BEFORE anything else.
*/
void InitCustomLibrary();

#endif
