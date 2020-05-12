#include <iostream>
#include <memory>
#include "ProgramRunner.h"

int main()
{
	std::unique_ptr<ProgramRunner> programRunner = std::make_unique<ProgramRunner>();
	programRunner->RunProgram();

	system("pause");
	return 0;
}