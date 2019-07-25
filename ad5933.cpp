#include "ad5933.h"

AD5933_Class AD5933;
/*
 * gets the internal temperature of the device
 */
double AD5933_Class::get_internal_temp() {

	if ( update_temperature() == false )
		return -1;
	
	int temp_t[2];
	long temp_tVal;
	double cTemp;

	temp_t[0] = get_i2c_reg(0x92);
	temp_t[1] = get_i2c_reg(0x93);
	temp_tVal = (temp_t[0] % (12 * 16)) * 16 * 16 + temp_t[1];
	
	cTemp=(bitRead(temp_t[0], 5) == 0) ? (double)temp_tVal / 32 : (temp_tVal - 16384.0) / 32 ; // according to temperature formula
	
	return cTemp;
}


/*
 * Sends a command instruction to the control register with explicit content that will overwrite the existing content.
 *
 * @argument switch_mode One of the available modes of the AD5933
 * @argument control_reg new contents of the control resister.
 */
bool AD5933_Class::set_ctrl_reg(byte switch_mode, int control_reg) {

	control_reg &= 0x0F; // Get the last 4 digits.
	switch (switch_mode)
	{

	case POWER_DOWN:
		control_reg |= 0xA0;
		break;
	case STAND_BY:
		control_reg |= 0xB0;
		break;
	case MEAS_TEMP:
		control_reg |= 0x90;
		break;
	default:

		return false; // return the signal of fail if there is not valid argumenteter.
		break;
	}
	return set_i2c_reg(0x80, control_reg); // return signal depends on the result of setting control register.

}

/*
 * Sends a command to the control register without assumming the it's contents.
 *
 * @argument switch_mode One of the available modes of the AD5933.
 */

bool AD5933_Class::set_ctrl_reg(byte switch_mode) {
	return set_ctrl_reg(switch_mode, get_i2c_reg(0x80));
}


/*
 * Function to set an I2C address.
 *
 * @argument address The I2C register address to write to
 * @argument value The value to be writen
 */

bool AD5933_Class::set_i2c_reg(int address, int value) {

	Wire.beginTransmission(AD5933_ADDR); // Begin I2C Transmission.
	Wire.write(address); // Write Address
	Wire.write(value); // Write Value
	int return_of_i2c = Wire.endTransmission(); // Terminate the transmission.

	return  (return_of_i2c)? true : false ;
}

/*
 * Function to read the contents of a register address via I2C.
 * Returns retrived byte data.
 *
 * @argument address The I2C register address to read from
 */

int AD5933_Class::get_i2c_reg(int address) {

	int receive_byte;


	if ( !set_i2c_reg(Address_Ptr, address))
		return false;

	Wire.requestFrom(AD5933_ADDR, 1); // Request the value of the written address.

	receive_byte = (1 <= Wire.available()) ? Wire.read() : -1 ; // If the MCU get the value, Read the value. or else Returns -1 if fails.
	
	return receive_byte;
}


/*
 * Updates temperature without writing to a variable.
 */

bool AD5933_Class::update_temperature {

	if (set_ctrl_reg(MEAS_TEMP) == false)
	{
		return false;
	}

	while ( (get_status() & 0x01) != 0x01)
	{
		; // Wait Until Get Vaild Temperature.
	}

	return true;
}

