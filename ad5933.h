
#ifndef header_ad5933 // avoid duplication.

#define header_ad5933

#include<HardwareSerial.h> //  Serial Logging
#include<math.h> //  math functions
#include<Arduino.h> //  access to arduino pins , maintain Arduino conventions
#include<Wire.h> // wire setup of arduino for I2C communications



const int AD5933_ADDR = 0x0D; // Device Serial Bus Address

// defined values for Control Registers

const int POWER_DOWN = 10;
const int STAND_BY = 11;
const int MEAS_TEMP = 9;

class AD5933_Class
{
public: 

	// function details with argument descriptions are in "ad5933.cpp" file.
		
	bool set_ctrl_reg(byte); // Sends a command to the control register without assumming the it's contents.
	bool set_ctrl_reg(byte, int); // Sends a command instruction to the control register with explicit content that will overwrite the existing content.

	double get_internal_temp(); // gets the internal temperature of the device

	bool update_temperature(); // Updates temperature without writing to a variable.

	
private:	// Internal fucntions and variables used within the library

	static const byte Address_Ptr = 0xB0; 	// Address Pointer to read register values.

	/*
	*	Inline Function for getting status register.
	*/
	inline byte get_status()
	{
		return (get_i2c_reg(0x8F) & 0x07);
	}


	int get_i2c_reg(int);
	bool set_i2c_reg(int, int);

};

extern AD5933_Class AD5933;

#endif

