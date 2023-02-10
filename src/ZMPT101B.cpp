#include "ZMPT101B.h"

ZMPT101B::ZMPT101B(uint8_t _pin) {
	pin = _pin;

	// Sensor ouput Vmax - (Vref / 2) / Sensor input Vmax
	// Input Vmax = Vrms * sqrt(2) = Vrms * 1.414
	sensitivity = 0.010000;
}

int ZMPT101B::calibrate() {
	uint16_t acc = 0;

	for (int i = 0; i < 10; i++) {
		acc += analogRead(pin);
	}
	zero = acc / 10;

	return zero;
}

int ZMPT101B::calibrateLive() {
	uint16_t acc = 0;

	for (int i = 0; i < 100; i++) {
		acc += analogRead(pin);
		delayMicroseconds(1000);
	}
	zero = acc / 100;

	return zero;
}

float ZMPT101B::calibrateVoltage() {
	uint16_t acc = 0;

	for (int i = 0; i < 100; i++) {
		acc += analogRead(pin);
		delayMicroseconds(1000);
	}
	zero = acc / 100;
	Vzero = zero * Vref / ADC_SCALE;

	return Vzero;
}

void ZMPT101B::setZeroPoint(uint16_t _zero) {
	zero = _zero;
}

void ZMPT101B::setVref(float _Vref) {
	Vref = _Vref;
}

void ZMPT101B::setSensitivity(float sens) {
	sensitivity = sens;
}

float ZMPT101B::getVoltageDC() {
	int16_t acc = 0;

	for (int i = 0; i < 10; i++) {
		acc += analogRead(pin) - zero;
	}
	float V = (float)acc / 10.0 / ADC_SCALE * Vref / sensitivity;

	return V;
}

float ZMPT101B::getVoltageAC(uint16_t frequency) {
	uint32_t period = 1000000 / frequency;
	uint32_t t_start = micros();

	uint32_t Vsum = 0;
	uint32_t measurements_count = 0;
	int32_t Vnow;

	while (micros() - t_start < period) {
		Vnow = analogRead(pin) - zero;
		Vsum += Vnow * Vnow;
		measurements_count++;
	}
	float Vrms = sqrt(Vsum / measurements_count) / ADC_SCALE * Vref / sensitivity;

	return Vrms;
}
