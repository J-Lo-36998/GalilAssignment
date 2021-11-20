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




#include <assert.h>

void clearOutputs(Galil& g) {
	g.DigitalOutput(0);

	for (uint8_t i = 0; i < 8; i++) {
		g.AnalogOutput(i, 0);
	}

	g.WriteEncoder();
}

// TODO: run "IQ 65535" before running this function
int testingGalil() {
	EmbeddedFunctions funcs;
	GCStringIn addr = "192.168.0.120 -d";
	Galil g (&funcs, addr);
	std::cout << g;
	clearOutputs(g);
	assert(g.DigitalInput() == 0);

	clearOutputs(g);
	g.DigitalOutput(1);
	assert(g.DigitalInput() == 1);

	clearOutputs(g);
	g.DigitalOutput(10);//
	assert(g.DigitalInput() == 10);

	clearOutputs(g);
	g.DigitalOutput(0xFF);
	assert(g.DigitalInput() == 0xFF);

	clearOutputs(g);
	g.DigitalOutput(0x1FF);
	assert(g.DigitalInput() == 0xFF);

	clearOutputs(g);
	g.DigitalOutput(0xFFFF);
	assert(g.DigitalInput() == 0xFF);

	clearOutputs(g);
	g.DigitalByteOutput(false, 1);
	assert(g.DigitalInput() == 1);
	assert(g.DigitalByteInput(false) == 1);
	assert(g.DigitalByteInput(true) == 0);


	clearOutputs(g);
	g.DigitalByteOutput(false, 0xF);
	assert(g.DigitalInput() == 0xF);
	assert(g.DigitalByteInput(false) == 0xF);
	assert(g.DigitalByteInput(true) == 0);


	clearOutputs(g);
	g.DigitalByteOutput(true, 0xF);
	assert(g.DigitalInput() == 0);
	assert(g.DigitalByteInput(false) == 0);
	assert(g.DigitalByteInput(true) == 0);

	clearOutputs(g);
	g.DigitalBitOutput(true, 4);
	assert(g.DigitalInput() == 0x10);
	assert(g.DigitalByteInput(false) == 0x10);
	assert(g.DigitalByteInput(true) == 0x0);

	clearOutputs(g);
	g.DigitalBitOutput(true, 10);
	assert(g.DigitalInput() == 0);
	assert(g.DigitalByteInput(false) == 0x0);
	assert(g.DigitalByteInput(true) == 0x0);

	clearOutputs(g);
	g.DigitalOutput(0xFFFF);
	g.DigitalBitOutput(false, 10);
	assert(g.DigitalInput() == 0xFF);
	assert(g.DigitalByteInput(false) == 0xFF);
	assert(g.DigitalByteInput(true) == 0x00);

	clearOutputs(g);
	g.DigitalOutput(0xFFFF);
	g.DigitalBitOutput(false, 4);
	assert(g.DigitalInput() == 0xEF);
	assert(g.DigitalByteInput(true) == 0x00);
	assert(g.DigitalByteInput(false) == 0xEF);

	clearOutputs(g);
	assert(g.ReadEncoder() == 0);

	clearOutputs(g);
	g.AnalogOutput(0, 5);
	Sleep(500);
	assert(g.ReadEncoder() > 0);

	clearOutputs(g);
	Sleep(1000);
	clearOutputs(g);
	g.AnalogOutput(0, -5);
	Sleep(500);
	assert(g.ReadEncoder() < 0);

	clearOutputs(g);

	Console::WriteLine("*** All tests passed!! ***");
	Sleep(2000);
	return 1;
}
int main() {
	EmbeddedFunctions Funcs;
	GCStringIn addr = "192.168.0.120 -d";
	Galil MyGalil(&Funcs, addr);
	std::cout << MyGalil<<std::endl;
	//
	//
	std::cout << MyGalil.AnalogInput(0) << std::endl;
	std::cout << MyGalil.AnalogInput(1) << std::endl;
	std::cout << MyGalil.AnalogInput(2) << std::endl;
	std::cout << MyGalil.AnalogInput(3) << std::endl;
	std::cout << MyGalil.AnalogInput(4) << std::endl;
	std::cout << MyGalil.AnalogInput(5) << std::endl;
	std::cout << MyGalil.AnalogInput(6) << std::endl;
	std::cout << MyGalil.AnalogInput(7) << std::endl;
	/*MyGalil.AnalogOutput(0, 0);
	std::cout <<unsigned int(MyGalil.DigitalByteInput(0))<<std::endl;
	MyGalil.DigitalOutput(0xFF);
	
	MyGalil.WriteEncoder();
	MyGalil.DigitalBitOutput(0, 1);*/
	MyGalil.AnalogOutput(0, 0);
	MyGalil.WriteEncoder();
	//MyGalil.AnalogOutput(0, 1);
	MyGalil.setSetPoint(5000);
	MyGalil.setKp(1);
	MyGalil.setKi(1);
	MyGalil.setKd(1);
	std::cout << MyGalil.ReadEncoder() << std::endl;
	//MyGalil.PositionControl(0, MyGalil.ReadEncoder());
	MyGalil.SpeedControl(1, MyGalil.ReadEncoder());
	
	//Console::ReadKey();

	//galil.DigitalInput();
	//galil.DigitalByteInput(1);
	//
	//testingGalil();
	//galil->
	//galil->;
	
	Console::WriteLine("Terminating!");
	Console::ReadKey();
	
	//delete MyGalil;
	return G_NO_ERROR;

}