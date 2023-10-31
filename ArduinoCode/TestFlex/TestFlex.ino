const int flexPin = A0;
const int flexTest = A1;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
int flexValue;
flexValue = analogRead(flexPin);

int testValue;
testValue = analogRead(flexTest);
Serial.print(flexValue);
Serial.print("\n");
Serial.print("\n");
Serial.print(flexTest);
Serial.print("\n");

delay(20);
}
