/* 
  Calibrate the ZMPT101B with the serial plotter in the Arduino IDE.
  Connect the sensor to the input source.
  Make sure the waveform is not cut off on the top and bottom
  by turning the potentiometer on the module to display the full waveform.
*/

void setup() {
  Serial.begin(9600);

  // Set analoge pin to input
  pinMode(A0, INPUT);
}

void loop() {
  // Read analog input
  Serial.println(analogRead(A0));
  delay(20);
}