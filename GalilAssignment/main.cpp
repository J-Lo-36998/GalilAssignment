#include <stdlib.h>
#include <gclib.h>
#include <gclibo.h>
#include <gclib_errors.h>
#include <gclib_record.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Galil.h"
#include "EmbeddedFunctions.h"
using namespace System;
using namespace System::IO;
using namespace System::Collections::Generic;
using namespace System::Threading::Tasks;

GCon g = 0;

int main() {
	Galil Galil;
	/*char buf[1024];
	char Command[128] = "";

	GOpen("192.168.0.120 -d", &g);*/
	Galil.AnalogOutput('A0', 5.00);

	if (g) {
		GClose(g);
	}
	Console::WriteLine("Termindating!");
	Console::ReadKey();

	return G_NO_ERROR;

}