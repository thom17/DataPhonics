#include "TdsSensor.h"

TdsSensor::TdsSensor(uint8_t dataPin)
{
  this->dataPin = dataPin;
  setup();
};

void TdsSensor::setup()
{
  pinMode(dataPin, INPUT);
};

float TdsSensor::sense(float temp)
{
    float averageVoltage = analogRead(dataPin) * (float)VREF / 1024.0; // read the analog value more stable by the median filtering algorithm, and convert to voltage value
    float compensationCoefficient=1.0+0.02*(temp-25.0);    //temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0));
    float compensationVolatge=averageVoltage/compensationCoefficient;  //temperature compensation
    float tdsValue=(133.42*compensationVolatge*compensationVolatge*compensationVolatge - 255.86*compensationVolatge*compensationVolatge + 857.39*compensationVolatge)*0.5; //convert voltage value to tds value
      //Serial.print("voltage:");
      //Serial.print(averageVoltage,2);
      //Serial.print("V   ");
     // Serial.print("TDS Value:");
      //Serial.print(tdsValue,0);
     // Serial.println("ppm");
      return tdsValue;

};
