#include <ZMPT101B.h>

// Set analoge pin
ZMPT101B voltageSensor(A0);

void setup() {
  Serial.begin(9600);

  //Set Vref
  voltageSensor.setVref(5.0);

  Serial.println("");
  Serial.println("+=================+");
  Serial.println("|Zero |Live |Volts|");
}

void loop() {
  // Zero point (Without power input)
  int Z = voltageSensor.calibrate();

  // Zero point (With power input)
  int ZL = voltageSensor.calibrateLive();

  // Zero point voltage (With or without power input)
  float ZV = voltageSensor.calibrateVoltage();

  if (Z <= (ZL + 3) && Z >= (ZL - 3)) {
    Serial.print(String("| ") + Z);
  } else {
    Serial.print(String("| ---"));
  }
  Serial.print(String(" | ") + ZL);
  Serial.println(String(" |") + ZV + "V|");

  delay(1000);
}