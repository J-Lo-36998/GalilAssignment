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
#include <bitset>
using namespace System;
using namespace System::IO;
using namespace System::Collections::Generic;
using namespace System::Threading::Tasks;

int main() {
	EmbeddedFunctions Funcs;
	GCStringIn addr = "192.168.0.120 -d";
	Galil MyGalil(&Funcs, addr);
	std::cout << MyGalil;

	for (int n = 0; n <= 7; n++) {
		MyGalil.DigitalBitOutput(1, n);
		MyGalil.DigitalBitOutput(1, n+8);
		Sleep(200);
		MyGalil.DigitalOutput(0);
	}
	for (int n = 7; n >= 0; n--) {
		MyGalil.DigitalBitOutput(0, n);
		MyGalil.DigitalBitOutput(0, n + 8);
		Sleep(200);
		MyGalil.DigitalOutput(0);
	}
	
	MyGalil.AnalogOutput(0, 3);
	int encoder = 0;
	MyGalil.WriteEncoder();
	while (1) {
		encoder = MyGalil.ReadEncoder();
		//std::cout << std::bitset<8>(encoder) << std::endl;
		MyGalil.DigitalByteOutput(0, encoder);
	}
	return G_NO_ERROR;

}