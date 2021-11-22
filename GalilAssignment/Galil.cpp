#include "Galil.h"
#include "EmbeddedFunctions.h"
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
	memset(ReadBuffer, 0, sizeof(ReadBuffer));
	Funcs->GOpen(address, &g);
	Functions = Funcs;
	std::string set_iq = "IQ65535;";
	Functions->GCommand(g, set_iq.c_str(), ReadBuffer, sizeof(ReadBuffer), 0);
	std::cout << "Connected" << std::endl;
}

void Galil::DigitalOutput(uint16_t value) {
	// Write to all 16 bits of digital output, 1 command to the Galil
	memset(ReadBuffer, 0, sizeof(ReadBuffer));
	uint8_t highByte = (value >> 8) & 0xFF;
	uint8_t lowByte = (value & 0xFF);
	std::string CommandStr = "OP" + std::to_string(lowByte) + "," + std::to_string(highByte) + ";";
	Functions->GCommand(g, CommandStr.c_str(), ReadBuffer, sizeof(ReadBuffer), 0);
	if (CheckSuccessfulWrite() == TRUE) {
		std::cout << "Write Successful"<<std::endl;
	}
	else {
		std::cout << "Write Unsuccessful" << std::endl;
	}
}
void Galil::DigitalByteOutput(bool bank, uint8_t value) {
	// Write to one byte, either high or low byte, as specified by user in 'bank'
	// 0 = low, 1 = high
	memset(ReadBuffer, 0, sizeof(ReadBuffer));
	if (bank == TRUE) {
		std::string CommandStr = "OP," +  std::to_string(value) + ";";
		Functions->GCommand(g, CommandStr.c_str(), ReadBuffer, sizeof(ReadBuffer), 0);
		if (CheckSuccessfulWrite() == TRUE) {
			std::cout << "Write Successful" << std::endl;
		}
		else {
			std::cout << "Write Unsuccessful" << std::endl;
		}
	}
	else {
		std::string CommandStr = "OP" + std::to_string(value) + ";";
		Functions->GCommand(g, CommandStr.c_str(), ReadBuffer, sizeof(ReadBuffer), 0);
		if (CheckSuccessfulWrite() == TRUE) {
			std::cout << "Write Successful" << std::endl;
		}
		else {
			std::cout << "Write Unsuccessful" << std::endl;
		}
	}
}
void Galil::DigitalBitOutput(bool val, uint8_t bit) {
	// Write single bit to digital outputs. 'bit' specifies which bit
	memset(ReadBuffer, 0, sizeof(ReadBuffer));
	std::string CommandStr = "OB" + std::to_string(bit) + ","+std::to_string(val)+";";
	Functions->GCommand(g, CommandStr.c_str(), ReadBuffer, sizeof(ReadBuffer), 0);
	if (CheckSuccessfulWrite() == TRUE) {
		std::cout << "Write Successful" << std::endl;
	}
	else {
		std::cout << "Write Unsuccessful" << std::endl;
	}
}
// DIGITAL INPUTS
uint16_t Galil::DigitalInput() {
	// Return the 16 bits of input data
	// Query the digital inputs of the GALIL, See Galil command library @IN
	uint16_t inputData = 0x0;
	for (int i = 15; i >= 0; i--) {
		inputData = inputData | DigitalBitInput(i)<<i;
	}
	return inputData;
}
uint8_t Galil::DigitalByteInput(bool bank) {	
	// Read either high or low byte, as specified by user in 'bank'
	// 0 = low, 1 = high
	uint16_t Data = 0x0;
	Data = DigitalInput();
	if (bank == TRUE) {//High Byte
		uint8_t highByte = (Data >> 8) & 0xFF;
		return highByte;
	}
	else {//Low Byte
		uint8_t lowByte = (Data & 0xFF);
		//std::cout << lowByte;
		return lowByte;
	}
}
bool Galil::DigitalBitInput(uint8_t bit) {		// Read single bit from current digital inputs. Above functions
												// may use this function
	bool input{ FALSE };
	std::string CommandStr = "MG@IN[" + std::to_string(bit) + "];";
	Functions->GCommand(g, CommandStr.c_str(), ReadBuffer, sizeof(ReadBuffer), 0);
	input = atoi(ReadBuffer);
	return input;
}

bool Galil::CheckSuccessfulWrite() {	// Check the string response from the Galil to check that the last 
								// command executed correctly. 1 = succesful. NOT AUTOMARKED
	
	if (ReadBuffer[0] == ':') {
		return 1;
	}
	else {
		return 0;
	}
}

// ANALOG FUNCITONS
float Galil::AnalogInput(uint8_t channel) {						// Read Analog channel and return voltage	
	std::string CommandStr = "MG@AN[" + std::to_string(channel) + "];";
	float voltage = 0;
	char voltageData[] = "";
	Functions-> GCommand(g, CommandStr.c_str(), ReadBuffer, sizeof(ReadBuffer), 0);
	//std::cout << "hi";
	//std::cout << ReadBuffer;
	voltage = atof(ReadBuffer);
	return voltage;
}
void Galil::AnalogOutput(uint8_t channel, double voltage) {		// Write to any channel of the Galil, send voltages as
	memset(ReadBuffer, 0, sizeof(ReadBuffer));
	std::string CommandStr = "AO" + std::to_string(channel) + "," + std::to_string(voltage) + ";";
	Functions->GCommand(g, CommandStr.c_str(), ReadBuffer, sizeof(ReadBuffer), 0);
	if (CheckSuccessfulWrite() == TRUE) {
		std::cout << "Write Successful" << std::endl;
	}
	else {
		std::cout << "Write Unsuccessful" << std::endl;
	}
}
void Galil::AnalogInputRange(uint8_t channel, uint8_t range) {	// Configure the range of the input channel with												// the desired range code
	std::string CommandStr = "AQ" + std::to_string(channel) + "," + std::to_string(range) + ";";
	Functions->GCommand(g, CommandStr.c_str(), ReadBuffer, sizeof(ReadBuffer), 0);
}

// ENCODER / CONTROL FUNCTIONS
void Galil::WriteEncoder() {								// Manually Set the encoder value to zero
	//NOT COMPLETE
	std::string CommandStr = "WE0,0;";
	Functions->GCommand(g, CommandStr.c_str(), ReadBuffer, sizeof(ReadBuffer), 0);
}
int Galil::ReadEncoder() {									// Read from Encoder
	int encoderVal{ 0 };
	std::string CommandStr = "QE0;";
	Functions->GCommand(g, CommandStr.c_str(), ReadBuffer, sizeof(ReadBuffer), 0);
	encoderVal = atoi(ReadBuffer);
	return encoderVal;
}
void Galil::setSetPoint(int s) {							// Set the desired setpoint for control loops, counts or counts/sec
	setPoint = s;
}
void Galil::setKp(double gain) {							// Set the proportional gain of the controller used in controlLoop()
	ControlParameters[0] = gain;
}
void Galil::setKi(double gain) {							// Set the integral gain of the controller used in controlLoop()
	ControlParameters[1] = gain;
}
void Galil::setKd(double gain) {						// Set the derivative gain of the controller used in controlLoop()
	ControlParameters[2] = gain;
}
std::ostream& operator<<(std::ostream& output, Galil& galil) {
	// Operator overload for '<<' operator. So the user can say cout << Galil; This function should print out the
	// output of GInfo and GVersion, with two newLines after each.
	galil.Functions->GInfo(galil.g, galil.ReadBuffer, sizeof(galil.ReadBuffer));
	//std::cout << galil.ReadBuffer<<std::endl;
	output <<"Galil Info: "<<galil.ReadBuffer<<"\n\n";
	galil.Functions->GVersion(galil.ReadBuffer, sizeof(galil.ReadBuffer));
	output << "Galil Version: "<<galil.ReadBuffer<<"\n\n";
	//output << "Hello World";
	return output;
}
Galil:: ~Galil() {
	if (g) {
		Functions->GClose(g);
	}
}												// Default destructor. Deallocate memory and close Galil connection. NOT AUTOMARKED
