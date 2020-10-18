#pragma once
#include "arduino.h"
class D_HumidSensor 
{
private:
	uint8_t sigPin;                 //데이터 핀
	float maxValue = 500;     //최대 값 
	int dif = -300;            //보정 값

public:
	  D_HumidSensor(uint8_t sig = A0)
 {
    this->sigPin = sig;
    pinMode(sigPin, INPUT);
 }
  float sense()
 {
    float value = analogRead(sigPin);
    value += dif;
    if (value < 0 ) return 0.0;
    else if(maxValue <= value) return 100.0;
    else return value*100.0/maxValue;
    
 }

};
