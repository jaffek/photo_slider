#include "PinChangeInterrupt.h"
#include "IRLremote.h"

#define pinIR 11
#define pinLed LED_BUILTIN
#define kranL 5
#define kranP 6
#define ms1 10
#define ms2 9
#define ms3 8
#define stepPin 3
#define dirPin 4
#define sleep 2
#define res 7

CNec IRLremote;
int ruch = 1;
int ruch1 = 0;

void ruchy()
{
  if (IRLremote.available())
  {
    auto data = IRLremote.read();
    if (data.address != 65535)
    {
      ruch1 = ruch;
      ruch = data.command;
    }
  }
}
void petla(int pin, int dela)
{
  while (digitalRead(pin) == LOW && ruch != 67 && ruch != 9 && ruch != 1)
  {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(dela);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(dela);
    ruchy();
    if (ruch == 67 || ruch == 9)
    {
      ruch1 = ruch;
      ruch = 1;
      break;
    }
  }
}
void tryb(uint8_t m1, uint8_t m2, uint8_t m3, int del)
{
  digitalWrite(ms1, m1);
  digitalWrite(ms2, m2);
  digitalWrite(ms3, m3);
  if (ruch1 == 7 || ruch == 68)
  {
    digitalWrite(dirPin, LOW);
    petla(kranL, del);
    ruch1 = ruch;
    ruch = 1;
  }
  if (ruch1 == 21 || ruch == 64)
  {
    digitalWrite(dirPin, HIGH);
    petla(kranP, del);
    ruch1 = ruch;
    ruch = 1;
  }
  if (ruch1 == 69)
  {
    while (ruch != 67 && ruch != 9 && ruch != 1)
    {
      digitalWrite(dirPin, LOW);
      petla(kranL, del);
      digitalWrite(dirPin, HIGH);
      petla(kranP, del);
    }
    ruch1 = ruch;
    ruch = 1;
  }
  if (ruch1 == 71)
  {
    while (ruch != 67 && ruch != 9 && ruch != 1)
    {
      digitalWrite(dirPin, HIGH);
      petla(kranP, del);
      digitalWrite(dirPin, LOW);
      petla(kranL, del);
    }
    ruch1 = ruch;
    ruch = 1;
  }
  if (ruch == 9)
    digitalWrite(sleep, LOW);

}
void setup()
{
  pinMode(pinLed, OUTPUT);
  pinMode(ms1, OUTPUT);
  pinMode(ms2, OUTPUT);
  pinMode(ms3, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(sleep, OUTPUT);
  pinMode(res, OUTPUT);
  digitalWrite(res, HIGH);
  pinMode(kranL,  INPUT_PULLUP);
  pinMode(kranP,  INPUT_PULLUP);
  // Start reading the remote. PinInterrupt or PinChangeInterrupt* will automatically be selected
  if (!IRLremote.begin(pinIR))
    Serial.println(F("You did not choose a valid pin."));

}

void loop()
{
  digitalWrite(stepPin, LOW);
  ruchy();
  if (ruch == 9 || ruch == 1)
    digitalWrite(sleep, LOW);
  else digitalWrite(sleep, HIGH);
  if (ruch == 12 && (ruch1 == 69 || ruch1 == 71 || ruch1 == 7 || ruch1 == 21)) tryb(LOW, LOW, LOW, 1000);
  if (ruch == 24 && (ruch1 == 69 || ruch1 == 71 || ruch1 == 7 || ruch1 == 21)) tryb(HIGH, LOW, LOW, 1000);
  if (ruch == 94 && (ruch1 == 69 || ruch1 == 71 || ruch1 == 7 || ruch1 == 21)) tryb(LOW, HIGH, LOW, 1000);
  if (ruch == 8 && (ruch1 == 69 || ruch1 == 71 || ruch1 == 7 || ruch1 == 21)) tryb(HIGH, HIGH, LOW, 1000);
  if (ruch == 28 && (ruch1 == 69 || ruch1 == 71 || ruch1 == 7 || ruch1 == 21)) tryb(LOW, LOW, HIGH, 1000);
  if (ruch == 90 && (ruch1 == 69 || ruch1 == 71 || ruch1 == 7 || ruch1 == 21)) tryb(HIGH, LOW, HIGH, 1000);
  if (ruch == 66 && (ruch1 == 69 || ruch1 == 71 || ruch1 == 7 || ruch1 == 21)) tryb(HIGH, LOW, HIGH, 2000);
  if (ruch == 82 && (ruch1 == 69 || ruch1 == 71 || ruch1 == 7 || ruch1 == 21)) tryb(HIGH, LOW, HIGH, 4000);
  if (ruch == 74 && (ruch1 == 69 || ruch1 == 71 || ruch1 == 7 || ruch1 == 21)) tryb(HIGH, LOW, HIGH, 8000);
  if (ruch == 68) tryb(LOW, LOW, LOW, 500);
  if (ruch == 64) tryb(LOW, LOW, LOW, 500);

}

