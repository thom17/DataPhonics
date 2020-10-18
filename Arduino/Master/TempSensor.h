#include <OneWire.h>  //1 와이어 모듈
#include <DallasTemperature.h>  //oneWire 온도센서

class TempSensor
{
private:
  OneWire *oneWire;                 //1wire 클래스 pin번호를 매게변수로 생성
  DallasTemperature *sensors;       //온도 센서 라이브러리 클래스 (1wire를 매개변수로 생성)
  DeviceAddress insideThermometer;  //unint8_t[] 장치 주소 (핀 번호는 아닌듯 함)

  uint8_t dataPin;                  //온도센서 입력 pin 번호
  
public:
  TempSensor(uint8_t dataPin);  //온도센서 객체 생성
  /*
   * 라이브러리 객체들 초기화
  */
  
  float sense();                //온도 측정 반환
  /*
   * 예제 기반으로 값 측정 하여 float 반환
   */

  void setup();                 //온도센서 초기화 세팅
  /*
   * 라이브러리 객체들 초기 세팅
   */

   // float main(); //예제 원본
};
