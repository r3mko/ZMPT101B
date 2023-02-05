#include <ZMPT101B.h>
#include <ACS712.h>

/*
  This example shows how to measure the power consumption
  of a devices in an AC electrical system
*/

// We have the ZMPT101B sensor connected to the A0 pin of the arduino
ZMPT101B voltageSensor(A0);

// We have a 5 amps version the sensor connected to the A1 pin of the arduino
// Code at <https://github.com/rkoptev/ACS712-arduino>
ACS712 currentSensor(ACS712_05B, A1);

void setup()
{
  Serial.begin(9600);

  // calibrate() method calibrates zero point of sensor,
  // It is necessary and has a positively affect on the accuracy
  // Ensure that no current flows through the sensor at this moment
  // If you are not sure that the current through the sensor will not leak during calibration comment out this method
  Serial.println("Calibrating... Ensure that no current flows through the sensor at this moment");
  delay(100);
  voltageSensor.calibrate();
  currentSensor.calibrate();
  Serial.println("Done!");
}

void loop()
{
  // To measure a voltage/current we need to know the frequency of the voltage/current
  // By default 50Hz is used, but you can specify a desired frequency
  // as the first argument for "getVoltageAC()"

  float U = voltageSensor.getVoltageAC();
  float I = currentSensor.getCurrentAC();

  // To calculate the power we need the voltage multiplied by the current
  float P = U * I;

  Serial.println(String("U = ") + U + " V");
  Serial.println(String("I = ") + I + " A");
  Serial.println(String("P = ") + P + " Watts");

  delay(1000);
}