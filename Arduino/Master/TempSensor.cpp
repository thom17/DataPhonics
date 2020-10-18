#include <OneWire.h>
#include <DallasTemperature.h>
#include "TempSensor.h"

TempSensor::TempSensor(uint8_t dataPin)
{
   oneWire = new OneWire(dataPin);
   sensors = new DallasTemperature(oneWire);
   this->dataPin = dataPin;

    setup();
   
};

void TempSensor::setup()
{
  if (!sensors->getAddress(insideThermometer, 0))
   Serial.println("Unable to find address for Device 0");
  sensors->begin();  
  sensors->setResolution(insideThermometer, 10); 
}

float TempSensor::sense()
{
  sensors->requestTemperaturesByIndex(0);   
  float  tempC = sensors->getTempC(insideThermometer);
      
 // Serial.print("Temp C: ");
 // Serial.print(tempC);
 // Serial.print(" Temp F: ");


  //Serial.print(DallasTemperature::toFahrenheit(tempC));
  //Serial.print(" Temp C: ");
 // Serial.println(tempC);
  return tempC;
};

/*
float TempSensor::main()
{
  OneWire oneWire(dataPin);  
    
// oneWire선언한 것을 sensors 선언시 참조함.  
DallasTemperature sensors(&oneWire);  
    
//다비아스 주소를 저장할 배열 선언  

Serial.begin(9600);  
  Serial.println("Dallas Temperature IC Control Library Demo");  
    
  //1-wire 버스 초기화  
  sensors.begin();  
      
     
  //버스에서 첫번째 장치의 주소를 가져온다.  
  if (!sensors.getAddress(insideThermometer, 0))
  Serial.println("Unable to find address for Device 0");   
      
  
    
  //데이터시트에서 확인결과 9~12비트까지 설정 가능  
 sensors.setResolution(insideThermometer, 10); 
   Serial.print("Requesting temperatures...");  
  //sensors.requestTemperatures();   //연결되어 있는 전체 센서의 온도 값을 읽어옴  
  sensors.requestTemperaturesByIndex(0); //첫번째 센서의 온도값 읽어옴  
  Serial.println("DONE");  
     
  float  tempC = sensors.getTempC(insideThermometer);  
      
  Serial.print("Temp C: ");  
  Serial.print(tempC);  
  Serial.print(" Temp F: ");  
      
  //화씨 온도로 변환  
  Serial.println(DallasTemperature::toFahrenheit(tempC));   

  return tempC;
}
*/
