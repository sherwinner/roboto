//radio setup
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 10); // CE, CSN
const byte address[6] = "00001";

const int leftPot = A4;
const int rightPot = A5;

int lForSpeed;
int lBackSpeed;
int rForSpeed;
int rBackSpeed;

void setup()
{
  Serial.begin(9600);

  //radio initialisation
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop()
{
  radio.stopListening();
  sendSpeed(leftPot, valPot0, 310, 345, "base_turn", baseTurnCur, 70, 520);
}

int sendSpeed(int potread, int potsend, int dbLow, int dbHigh, String joint, int &servCur, int servMin, int servMax)
{
  potsend = analogRead(potread);
  if (potsend < dbLow)
  {
    if (!(servCur < servMin))
    {
      doMove(-20, servCur, joint);
    }
  }
  if (potsend > dbHigh)
  {
    if (!(servCur > servMax))
    {
      doMove(20, servCur, joint);
    }
  }
  return servCur;
}
int doMove(int move, int &subServCur, String subJoint)
{
  subServCur = subServCur + move;
  radio.write(&subServCur, sizeof(subServCur));
  Serial.println(subJoint);
  Serial.println(subServCur);
  delay (100);
}
