#include "RobotC.h"


int RobotC::Functions::sgn(int input) {
	if (input < 0) {
		return -1;
	}
	if (input > 0) {
		return 1;
	}

	return 0;
}