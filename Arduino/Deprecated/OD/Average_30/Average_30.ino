int diodePin = A0;    // select the input pin for the potentiometer
int ledPin = 12;      // select the pin for the LED
int switchPin = 9;
int sum;
float avg = 0;
int zero = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(switchPin, INPUT);
  digitalWrite(ledPin, HIGH);
  analogReadResolution(12);
}

void loop() {
  // put your main code here, to run repeatedly:
 // digitalWrite(ledPin, HIGH);
  sum = 0;
  avg = 0;
  for (int i = 0; i < 30; i++) {
    sum += analogRead(diodePin);
  }
  avg = sum / 30;
  Serial.print("Average of past 30 readings: ");
  Serial.print(avg - zero);
  Serial.print("\n");
  
  if (Serial.available()) {
    Serial.read();
    zero = avg;
  }
}
