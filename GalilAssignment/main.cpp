#include <stdlib.h>
#include <gclib.h>
#include <gclibo.h>
#include <gclib_errors.h>
#include <gclib_record.h>
#include <iostream>
#include <fstream>
#include <string>
#include "EmbeddedFunctions.h"
#include "Galil.h"

using namespace System;
using namespace System::IO;
using namespace System::Collections::Generic;
using namespace System::Threading::Tasks;

GCon g = 0;

int main() {
	EmbeddedFunctions Funcs;
	Galil galil (&Funcs, "192.168.0.120 -d");
	
	//galil.AnalogOutput(0, 0);
	
	std::cout << galil.AnalogInput(0) << std::endl;
	std::cout << galil.AnalogInput(1) << std::endl;
	std::cout << galil.AnalogInput(2) << std::endl;
	std::cout << galil.AnalogInput(3) << std::endl;
	std::cout << galil.AnalogInput(4) << std::endl;
	std::cout << galil.AnalogInput(5) << std::endl;
	std::cout << galil.AnalogInput(6) << std::endl;
	std::cout << galil.AnalogInput(7) << std::endl;
	galil.DigitalOutput(255);
	galil.DigitalByteOutput(1, 0);
	galil.DigitalByteOutput(0, 1);
	//galil.DigitalBitOutput(1, 8);
	galil.DigitalInput();
	Console::WriteLine("Terminating!");
	Console::ReadKey();
	
	return G_NO_ERROR;

}