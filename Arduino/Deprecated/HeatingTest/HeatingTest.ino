int sensorPin = A1;
int resistorPin = 9;
int sensorValue;
int pulseWidth = 0;
float voltageValue;
float temperature;

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
  pinMode(resistorPin, OUTPUT);
  analogWrite(resistorPin, 0);
  analogReadResolution(12);  
}

void loop() {
  if(Serial.available() > 0) {
    pulseWidth = Serial.parseInt();
    analogWrite(resistorPin, pulseWidth);
  }
  delay(1000);
  sensorValue = analogRead(sensorPin);
  voltageValue = 2 * (float(sensorValue) / 4095) * 3.3; // Output voltage from temperature sensor
  temperature = ((voltageValue / (5.04 / 5)) - 1.375) / .0225; // Transfer function
  Serial.print(temperature);
  Serial.print(" ");
  Serial.print(pulseWidth);
  Serial.print("\n");
}
