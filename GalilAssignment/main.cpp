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

void clearOutputs(Galil* g) {
	g->DigitalOutput(0);

	for (uint8_t i = 0; i < 8; i++) {
		g->AnalogOutput(i, 0);
	}

	g->WriteEncoder();
}

// TODO: run "IQ 65535" before running this function
int testingGalil() {
	EmbeddedFunctions funcs;
	GCStringIn addr = "192.168.0.120 -d";
	Galil* g = new Galil(&funcs, addr);

	clearOutputs(g);
	assert(g->DigitalInput() == 0);

	clearOutputs(g);
	g->DigitalOutput(1);
	assert(g->DigitalInput() == 1);

	clearOutputs(g);
	g->DigitalOutput(10);//
	assert(g->DigitalInput() == 10);

	clearOutputs(g);
	g->DigitalOutput(0xFF);
	assert(g->DigitalInput() == 0xFF);

	clearOutputs(g);
	g->DigitalOutput(0x1FF);
	assert(g->DigitalInput() == 0xFF);

	clearOutputs(g);
	g->DigitalOutput(0xFFFF);
	assert(g->DigitalInput() == 0xFF);

	clearOutputs(g);
	g->DigitalByteOutput(false, 1);
	assert(g->DigitalInput() == 1);
	assert(g->DigitalByteInput(false) == 1);
	assert(g->DigitalByteInput(true) == 0);


	clearOutputs(g);
	g->DigitalByteOutput(false, 0xF);
	assert(g->DigitalInput() == 0xF);
	assert(g->DigitalByteInput(false) == 0xF);
	assert(g->DigitalByteInput(true) == 0);


	clearOutputs(g);
	g->DigitalByteOutput(true, 0xF);
	assert(g->DigitalInput() == 0);
	assert(g->DigitalByteInput(false) == 0);
	assert(g->DigitalByteInput(true) == 0);

	clearOutputs(g);
	g->DigitalBitOutput(true, 4);
	assert(g->DigitalInput() == 0x10);
	assert(g->DigitalByteInput(false) == 0x10);
	assert(g->DigitalByteInput(true) == 0x0);

	clearOutputs(g);
	g->DigitalBitOutput(true, 10);
	assert(g->DigitalInput() == 0);
	assert(g->DigitalByteInput(false) == 0x0);
	assert(g->DigitalByteInput(true) == 0x0);

	clearOutputs(g);
	g->DigitalOutput(0xFFFF);
	g->DigitalBitOutput(false, 10);
	assert(g->DigitalInput() == 0xFF);
	assert(g->DigitalByteInput(false) == 0xFF);
	assert(g->DigitalByteInput(true) == 0x00);

	clearOutputs(g);
	g->DigitalOutput(0xFFFF);
	g->DigitalBitOutput(false, 4);
	assert(g->DigitalInput() == 0xEF);
	assert(g->DigitalByteInput(true) == 0x00);
	assert(g->DigitalByteInput(false) == 0xEF);

	clearOutputs(g);
	assert(g->ReadEncoder() == 0);

	clearOutputs(g);
	g->AnalogOutput(0, 5);
	Sleep(500);
	assert(g->ReadEncoder() > 0);

	clearOutputs(g);
	Sleep(1000);
	clearOutputs(g);
	g->AnalogOutput(0, -5);
	Sleep(500);
	assert(g->ReadEncoder() < 0);

	clearOutputs(g);

	Console::WriteLine("*** All tests passed!! ***");
	Sleep(2000);
	return 1;
}
int main() {
	EmbeddedFunctions Funcs;
	GCStringIn addr = "192.168.0.120 -d";
	Galil MyGalil(&Funcs, addr);
	//
	///*
	//std::cout << galil->AnalogInput(0) << std::endl;
	//galil->CheckSuccessfulWrite();
	//std::cout << galil.AnalogInput(1) << std::endl;
	//std::cout << galil.AnalogInput(2) << std::endl;
	//std::cout << galil.AnalogInput(3) << std::endl;
	//std::cout << galil.AnalogInput(4) << std::endl;
	//std::cout << galil.AnalogInput(5) << std::endl;
	//std::cout << galil.AnalogInput(6) << std::endl;
	//std::cout << galil.AnalogInput(7) << std::endl;*/
	//std::cout<<galil->AnalogOutput(0, 1) << std::endl;
	//std::cout <<unsigned int(galil->DigitalByteInput(0))<<std::endl;
	//galil.DigitalOutput(0);
	//for (uint8_t i = 0; i < 8; i++) {
	//	galil.AnalogOutput(i, 0);
	//}
	//galil->AnalogOutput(0, 1);
	//galil.WriteEncoder();
	//galil.DigitalBitOutput(1, 4);
	//std::cout << (galil.DigitalInput() == 0x10);
	//std::cout<< (galil.DigitalByteInput(FALSE) == 0x10);
	////galil.DigitalInput();
	////galil.DigitalByteInput(1);
	//
	//testingGalil();
	//galil->
	//galil->;
	std::cout << MyGalil;
	Console::WriteLine("Terminating!");
	Console::ReadKey();
	
	//delete MyGalil;
	return G_NO_ERROR;

}