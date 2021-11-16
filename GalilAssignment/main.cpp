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
	
	galil.AnalogOutput(0, 1);

	Console::WriteLine("Termindating!");
	Console::ReadKey();
	
	return G_NO_ERROR;

}