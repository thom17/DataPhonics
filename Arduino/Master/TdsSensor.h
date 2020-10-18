#include "Arduino.h"
class TdsSensor {
private:
  uint8_t dataPin;        //데이터 입력 핀
  float VREF = 5.0;       //공급 전압 (값 측정시 사용되는 변수)
public:
  TdsSensor(uint8_t pin);  //TDS 센서 객체 생성
  /*
   *핀 세팅후  
   *setup함수 호출
  */
  
  void setup();         //TDS 센서 세팅
  /*
    핀모드를 설정하는 세팅
  */
  
  float sense(float temp);    //
  /*
   * temp 온도를 기준으로 값 측정 아래의 식을 따름
   * result = analogRead*VREF/1024/(1.0+0.02*(temp-25.0));
   */

};
