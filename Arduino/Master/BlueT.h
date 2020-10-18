#pragma
#include <SoftwareSerial.h>
#include "Arduino.h"
class BlueT {
private:
    uint8_t vPin = NULL;  //전원 핀 GND는 항상 LOW임
    SoftwareSerial *bluetooth;
public:
    BlueT(uint8_t adin, uint8_t adout);
    BlueT(uint8_t vPin, uint8_t gPin, uint8_t bT_aR, uint8_t bR_aT); 
    /*
     * 블루투스 시리얼 통신 초기화후 셋업함수 호출
     */
    bool checkBlueStack();
    /*
     * 블루투스 시리얼 통신 버퍼에 값이 있으면 true 
     * 아니면 false
     */
    void setup(long spd = 9600);
    /*
     * spd의 속도로 블루투스 통신 시작(설정)
     * vPin을 사용한다면 전원 공급
     */
    void sendData(String data = "test Data Set 1 2 3");
    /*
     * 매개변수 data를 블루투스 연결 대상에게 전달.
     */
};
