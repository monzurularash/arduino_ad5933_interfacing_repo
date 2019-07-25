********* snippet of AD5933 Arduino Library ***********
AD5933 Arduino Library for Temperature Reading:
This is a simple library for using the AD5933 impedance convert system with an Arduino compatible device.

AD5933:
The AD5933 is developed by Analog Devices. 

The AD5933 is a high precision impedance converter system solution that combines an on-board frequency generator with a 12-bit, 1 MSPS, analog-to-digital converter (ADC). The frequency generator allows an external complex impedance to be excited with a known frequency. The response signal from the impedance is sampled by the on-board ADC and a discrete Fourier transform (DFT) is processed by an on-board DSP engine. 
	The AD5933 can be also used to read it's internal temperature. In this project AD5933 is interfaced with an Arduino Uno and the internal temperature of AD5933 is read via I2C. 


Brief Overview:

Get the internal temperature of the AD5933 device using: 
double temp = AD5933::get_internal_temp()
