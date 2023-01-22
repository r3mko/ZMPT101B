#ifndef ZMPT101B_h
#define ZMPT101B_h

#include <Arduino.h>

#define ADC_SCALE 1023.0
#define VREF 5.0
#define FREQUENCY 50
#define ZEROPOINT 512

class ZMPT101B {
public:
	ZMPT101B(uint8_t _pin);
	int calibrate();
	void setZeroPoint(int _zero);
	void setVref(float _Vref);
	void setSensitivity(float sens);
	float getVoltageDC();
	float getVoltageAC(uint16_t frequency = FREQUENCY);

private:
	int zero = ZEROPOINT;
	float Vref = VREF;
	float sensitivity;
	uint8_t pin;
};

#endif