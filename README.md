# ZMPT101B

An Arduino library to interact with the [ZMPT101B](http://www.zeming-e.com/file/0_2013_10_18_093344.pdf), an active single phase AC voltage sensor module.

This library is based on [Ruslan Koptev](https://github.com/rkoptev) ACS712 current sensors library for Arduino <https://github.com/rkoptev/ACS712-arduino>. This library is modified so that it can be used with ZMPT101B voltage sensor with the same code principle.

## Methods

### **Constructor**

```c++
ZMPT101B(uint8_t _pin)
```

The constructor with the analog input to which it is connected.

### **getVoltagetAC()**

```c++
float getVoltageAC(uint16_t frequency )
```

This method allows you to measure AC voltage. Frequency is measured in Hz. By default frequency is set to 50 Hz. We use the Root Mean Square technique for the measurements. The measurement itself takes time of one full period (1 second / frequency). The RMS calculation allows us to measure more complex signals that are different from the perfect sine wave.

### **calibrate()**

```c++
int calibrate()
```

This method reads the current value of the sensor and sets it as the reference point for future measurements, after which the value is returned. By default, this parameter is equal to half of the maximum value of the analog input: (1024/2) 512. However, sometimes (in most cases) this value may vary. It depends on the individual sensor, power issues etc… Note that when performing this method, no current must flow through the sensor, and since this is not always possible - there is the following method:

### **calibrateLive()**

```c++
int calibrateLive()
```

This method allows you to calibrate the sensor while current is active. It takes a larger sample size then "calibrate()" and calculates the average of multiple waves as the treference point for future measurements. See this sketch for an example: [Calibrate_zeropoint.ino](https://github.com/r3mko/ZMPT101B/blob/master/examples/Calibrate/Calibrate_zeropoint.ino)

### **calibrateVoltage()**

```c++
float calibrateVoltage()
```

This method also calibrates the sensor, like "calibrateLive()", but returns the current voltage instead of the analog value.

### **setZeroPoint()**

```c++
void setZeroPoint( int _zero )
```

This method sets the obtained value as a zero point for measurements. You can use the previous method "calibrate()" once, in order to find out zero point of your sensor and then use this method in your code to set the starting zero point without clibrating the sensor everytime.
You can also use "calibrateLive()" if you want to calibrate it everytime before calling "getVoltageAC()".

### **setSensitivity()**

```c++
void setSensitivity( float sens )
```

This method sets the sensitivity value of the sensor. The sensitivity value indicates how much the output voltage value, read by the ADC, is compared to the value of the measured voltage source. The default value is 0.010000.
You can calculate an estimate by using the following method:

```
Sensor ouput Vmax - (Vref / 2) / Sensor input Vmax
```

To calulate the input Vmax use the following method:

```
Input Vmax = Vrms * sqrt(2) = Vrms * 1.414
```

## Examples

This is an example of measuring electrical power using the zmpt101b sensor for voltage measurement and acs712 sensor for current measurements.
There are also examples for calibrating the sensor itself (with the Arduino IDE serial plotter) and finding the zero point offset.

### Circuit

![circuit](/img/schematic.png)

### Code

```c++
#include <ZMPT101B.h>

// ZMPT101B sensor connected to the A0 pin
ZMPT101B voltageSensor(A0);

void setup()
{
  Serial.begin(9600);

  // Set Vref, defaults to 5.0 (V)
  voltageSensor.setVref(5.0);

  // Set zero point, defaults to 512
  // or use calibrateLive() in the main loop
  voltageSensor.setZeroPoint(512);

  // Set sensitivity, to give you an estimate use the following method:
  // Sensor ouput Vmax - (Vref / 2) / Sensor input Vmax = sensitivity value
  voltageSensor.setSensitivity(0.010000);
}

void loop()
{
  // Set zero point while sensor is live
  voltageSensor.calibrateLive();

  // To measure the voltage we need to know the frequency
  // By default 50Hz is used, but you can specify the desired frequency
  // as the first argument for "getVoltageAC()"
  float V = voltageSensor.getVoltageAC();

  Serial.println(String(V) + " V");

  delay(1000);
}
```
