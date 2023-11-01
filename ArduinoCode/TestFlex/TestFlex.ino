#include <MusicWithoutDelay.h>
#include <synth.h>
#include <tables.h>
#include <Wire.h>

#include <MPU6050_tockn.h>

MusicWithoutDelay buzzer;

const int flexPinOne = A0;
const int flexPinTwo = A1;
const int flexPinThree = A2;
const int flexPinFour = A3;
const int flexPinFive = A4;
const int flexPinSix = A5;
const int flexPinSeven = A6;
const int flexPinEight = A7;

MPU6050 mpu6050(Wire);

void setup() 
{
    // put your setup code here, to run once:
  Serial.begin(9600);

  Wire.begin();
  mpu6050.begin();
  //mpu6050.calcGyroOffsets(true);

  buzzer.begin(CHB, TRIANGLE, ENVELOPE0, 0);

  Serial.print("Hlo");
}

void loop() 
{
   mpu6050.update();

  // buzzer.update();
  // buzzer.setFrequency(440);

  // Serial.print("MPU Y Angle - ");
  // Serial.print(mpu6050.getAngleY());
  // Serial.print("\n");

  int flexValue;

  // flexValue = analogRead(flexPinOne);
  // Serial.print("Flex A0 - ");
  // Serial.print(flexValue);
  // Serial.print("\n");
  

  // flexValue = analogRead(flexPinTwo);
  // Serial.print("Flex A1 - ");
  // Serial.print(flexValue);
  // Serial.print("\n");

  // flexValue = analogRead(flexPinThree);
  // Serial.print("Flex A2 - ");
  // Serial.print(flexValue);
  // Serial.print("\n");

  // flexValue = analogRead(flexPinFour);
  // Serial.print("Flex A3 - ");
  // Serial.print(flexValue);
  // Serial.print("\n");

  // flexValue = analogRead(flexPinFive);
  // Serial.print("Flex A4 - ");
  // Serial.print(flexValue);
  // Serial.print("\n");

  flexValue = analogRead(flexPinSix);
  Serial.print("Flex A5 - ");
  Serial.print(flexValue);
  Serial.print("\n");

  // flexValue = analogRead(flexPinSeven);
  // Serial.print("Flex A6 - ");
  // Serial.print(flexValue);
  // Serial.print("\n");

  // flexValue = analogRead(flexPinEight);
  // Serial.print("Flex A7 - ");
  // Serial.print(flexValue);
  // Serial.print("\n");
}
