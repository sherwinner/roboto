#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


RF24 radio(7, 10); // CE, CSN
const byte address[6] = "00001";

const int leftFor = 3;  // (pwm) pin 9 connected to pin A1     left
const int leftBack = 5;  // (pwm) pin 5 connected to pin A2     left

const int rightFor = 6; // (pwm) pin 10 connected to pin B1    Right
const int rightBack = 9;  // (pwm) pin 6 connected to pin B2    Right

int leftJoystick;
int rightJoystick;

byte lForSpeed;// change this (0-255) to control the speed of the motors
byte lBackSpeed;
byte rForSpeed;
byte rBackSpeed;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  pinMode(leftFor, OUTPUT); // set pins to output
  pinMode(leftBack, OUTPUT);
  pinMode(rightFor, OUTPUT);
  pinMode(rightBack, OUTPUT);
}

void loop() {
  radio.startListening();
  if (radio.available()) 
  {
    radio.read(&lForSpeed, sizeof(lForSpeed));
    analogWrite(leftFor, lForSpeed);

    radio.read(&lBackSpeed, sizeof(lBackSpeed));
    analogWrite(leftBack, lBackSpeed);

    radio.read(&rForSpeed, sizeof(rForSpeed));
    analogWrite(rightFor, rForSpeed);

    radio.read(&rBackSpeed, sizeof(rBackSpeed));
    analogWrite(rightBack, rBackSpeed);
    
  }
  /*
    forward();
    delay(1000);
    backward();
    delay(1000);
    left();
    delay(1000);
    right();
    delay(1000);
  */

}


void leftChannel()
{
  analogWrite(leftFor, lForSpeed);
  analogWrite(leftBack, lBackSpeed);
}

void rightChannel()
{
  analogWrite(rightFor, rForSpeed);
  analogWrite(rightBack, rBackSpeed);
}

//disregard this bullshit
/*
  void backward()
  {
  analogWrite(LeftFor, 0);
  analogWrite(LeftBack, speed);
  analogWrite(RightFor, 0);
  analogWrite(RightBack, speed);
  }

  void forward()
  {
  analogWrite(LeftFor, speed);
  analogWrite(LeftBack, 0);
  analogWrite(RightFor, speed);
  analogWrite(RightBack, 0);
  }

  void left()
  {
  analogWrite(LeftFor, speed);
  analogWrite(LeftBack, 0);
  analogWrite(RightFor, 0);
  analogWrite(RightBack, speed);
  }

  void right()
  {
  analogWrite(LeftFor, 0);
  analogWrite(LeftBack, speed);
  analogWrite(RightFor, speed);
  analogWrite(RightBack, 0);
  }
*/
