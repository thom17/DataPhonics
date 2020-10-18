#include "BlueT.h"
#include "arduino.h"
#include<SoftwareSerial.h>
void BlueT::setup(long spd = 9600)
{
   bluetooth->begin(spd);
   if( !vPin == NULL)
   {
      digitalWrite(vPin, HIGH); 
   }
}
BlueT::BlueT(uint8_t vPin, uint8_t gPin, uint8_t bT_aR, uint8_t bR_aT)
{
  this->vPin = vPin;
  
  pinMode(vPin, OUTPUT);
  pinMode(gPin, OUTPUT);
  digitalWrite(gPin, LOW);
  this->bluetooth = new SoftwareSerial(bR_aT, bT_aR);
  setup();
}

BlueT::BlueT(uint8_t bT_aR, uint8_t bR_aT)
{
  vPin = NULL;
   this->bluetooth = new SoftwareSerial(bR_aT, bT_aR);
   this->setup();
}
bool BlueT::checkBlueStack()
{
  Serial.println("avail is ");
  Serial.println(bluetooth->available());
  
    if (bluetooth->available())
    {
        char c = bluetooth->read();
        Serial.print("bl read is ");
        Serial.println(c);
        return true;
    }
    else
        return false;

};


void BlueT::sendData( String data = "test Data Set 1 2 3")
{
  Serial.println("data is "+data);
   bluetooth->println(data);
}
