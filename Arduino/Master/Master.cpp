#include <DallasTemperature.h>
#include <OneWire.h>
#include "Master.h"

#define N 30

Master::Master(BlueT *bt)
{
  Serial.begin(9600);
  this->blueT = bt;
  bt->setup();
}

//add list 각 센서의 객체를 더해주는 함수 리스트 count++

  void Master::addD_H(D_HumidSensor* d_h)
  {
    this->d_h = d_h;
    count++;
  }
  void Master::addTemp(TempSensor* temp)
  {
    this->temp = temp;
    count++;
  }
  void Master::addTds(TdsSensor* tds)
  {
    this->tds = tds;
    count++;
  }

// Sense List
String Master::d_hSense()
{
  if (this->d_h == NULL)
    return "n/";
  else
  {

    String str = "";
    float f=0.0;
    for(int i=0; i<repeat; i++) f += d_h->sense();
    str += f/repeat;
    return str+"/";
   
  }
}


String Master::tempSense()
{
  if (this->temp == NULL)
    return "n/";
  else
  {

    String str = "";
    float f=0.0;
    int r = repeat/10 + 1;
  
    
    for(int i=0; i<r; i++) f += temp->sense();
    tempC = f/r;
    str += tempC;
    return str+"/";
  }
}

String Master::tdsSense()
{
  if (this->tds == NULL)
    return "n/";
  else
  {

    String str = "";
    float f=0.0;
    for(int i=0; i<repeat; i++) f += tds->sense(tempC);
    str += f/repeat;
    return str+"/";
   
  }
}

String Master::sensWrite()
{
  String str = "<";
 str += count;
 
  str += "/" + d_hSense() + tempSense();
  str += tdsSense()+">";

  return str;
}
void Master::setup()
{
  blueT->setup();
}
void Master::loop()
{
//  if (blueT->checkBlueStack())
 // {
    blueT->sendData(sensWrite());
 // }
}
