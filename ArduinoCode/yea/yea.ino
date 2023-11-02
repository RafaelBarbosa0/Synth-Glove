const int pin = A0;

void setup() {
  // put your setup code here, to run once:
  Serial.Begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
int value = analogRead(pin);
Serial.print(value);
}
