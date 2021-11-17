#include "Galil.h"
#include <iostream>
#include <conio.h>
#include <sstream>
#include <string>
#include <stdio.h>
#include <ctype.h>
#include <bitset>
//Constructors
Galil::Galil() {
	// Default constructor. Initialize variables, open Galil connection and allocate memory. NOT AUTOMARKED
}												
Galil::Galil(EmbeddedFunctions * Funcs, GCStringIn address) {
	// Constructor with EmbeddedFunciton initialization
	g = GCon{ 0 };
	Funcs->GOpen(address, &g);
	Functions = Funcs;
	std::cout << ReadBuffer;
	std::cout << "Connected" << std::endl;
}

void Galil::DigitalOutput(uint16_t value) {
	// Write to all 16 bits of digital output, 1 command to the Galil
	std::string CommandStr = "OP" + std::to_string(value) + "," + std::to_string(value);
	Functions->GCommand(g, CommandStr.c_str(), ReadBuffer, sizeof(ReadBuffer), 0);
}
void Galil::DigitalByteOutput(bool bank, uint8_t value) {
	// Write to one byte, either high or low byte, as specified by user in 'bank'
	// 0 = low, 1 = high
	if (bank == TRUE) {
		std::string CommandStr = "OP," +  std::to_string(value);
		Functions->GCommand(g, CommandStr.c_str(), ReadBuffer, sizeof(ReadBuffer), 0);
	}
	else {
		std::string CommandStr = "OP" + std::to_string(value);
		Functions->GCommand(g, CommandStr.c_str(), ReadBuffer, sizeof(ReadBuffer), 0);
	}
}
void Galil::DigitalBitOutput(bool val, uint8_t bit) {
	// Write single bit to digital outputs. 'bit' specifies which bit
	std::string CommandStr = "OB" + std::to_string(bit) + ","+std::to_string(val);
	Functions->GCommand(g, CommandStr.c_str(), ReadBuffer, sizeof(ReadBuffer), 0);
}
// DIGITAL INPUTS
uint16_t Galil::DigitalInput() {
	// Return the 16 bits of input data
	// Query the digital inputs of the GALIL, See Galil command library @IN
	uint16_t inputData = 0x0;

	for (int i = 15; i >= 0; i--) {
		std::cout << i << std::endl;
		inputData = inputData | DigitalBitInput(i)<<i;
	}
	/*std::bitset<16> x(inputData);
	std::cout << x << std::endl;*/
	return inputData;
}
uint8_t Galil::DigitalByteInput(bool bank) {	// Read either high or low byte, as specified by user in 'bank'
										/// 0 = low, 1 = high
	return 0;
}
bool Galil::DigitalBitInput(uint8_t bit) {		// Read single bit from current digital inputs. Above functions
												// may use this function
	bool input{ FALSE };
	std::string CommandStr = "MG@IN[" + std::to_string(bit) + "]";
	Functions->GCommand(g, CommandStr.c_str(), ReadBuffer, sizeof(ReadBuffer), 0);
	input = atoi(ReadBuffer);
	return input;
}

bool Galil::CheckSuccessfulWrite() {	// Check the string response from the Galil to check that the last 
								// command executed correctly. 1 = succesful. NOT AUTOMARKED
	return TRUE;
}

// ANALOG FUNCITONS
float Galil::AnalogInput(uint8_t channel) {						// Read Analog channel and return voltage	
	std::string CommandStr = "MG@AN[" + std::to_string(channel) + "]";
	float voltage = 0;
	char voltageData[] = "";
	Functions-> GCommand(g, CommandStr.c_str(), ReadBuffer, sizeof(ReadBuffer), 0);
	voltage = atof(ReadBuffer);
	return voltage;
}
void Galil::AnalogOutput(uint8_t channel, double voltage) {		// Write to any channel of the Galil, send voltages as
	//char command[128] = "";
	//sprintf_s(command, "AO%d,%lf", channel, voltage);
	std::string CommandStr = "AO" + std::to_string(channel) + "," + std::to_string(voltage);
	Functions->GCommand(g, CommandStr.c_str(), ReadBuffer, sizeof(ReadBuffer), 0);
}
void Galil::AnalogInputRange(uint8_t channel, uint8_t range) {	// Configure the range of the input channel with												// the desired range code
	std::string CommandStr = "AQ" + std::to_string(channel) + "," + std::to_string(range);
	Functions->GCommand(g, CommandStr.c_str(), ReadBuffer, sizeof(ReadBuffer), 0);
}

// ENCODER / CONTROL FUNCTIONS
void Galil::WriteEncoder() {								// Manually Set the encoder value to zero
	//NOT COMPLETE
	std::string CommandStr = "WE,0,0";
	Functions->GCommand(g, CommandStr.c_str(), ReadBuffer, sizeof(ReadBuffer), 0);
}
int Galil::ReadEncoder() {									// Read from Encoder
	return 0;
}
void Galil::setSetPoint(int s) {							// Set the desired setpoint for control loops, counts or counts/sec

}
void Galil::setKp(double gain) {							// Set the proportional gain of the controller used in controlLoop()

}
void Galil::setKi(double gain) {							// Set the integral gain of the controller used in controlLoop()

}
void Galil::setKd(double gain) {						// Set the derivative gain of the controller used in controlLoop()

}
Galil:: ~Galil() {
	if (g) {
		Functions->GClose(g);
	}
}												// Default destructor. Deallocate memory and close Galil connection. NOT AUTOMARKED
