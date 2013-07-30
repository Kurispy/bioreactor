int sensorPin = A1;
int sensorValue;
float voltageValue;
float temperature;

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
  analogReadResolution(12);  
}

void loop() {
  sensorValue = analogRead(sensorPin);
  // Output voltage from temperature sensor
  voltageValue = 2 * (float(sensorValue) / 4095) * 3.3;
  // Transfer function
  temperature = ((voltageValue / (5.04 / 5)) - 1.375) / .0225;
  Serial.println(temperature);
  delay(1000);             
}
