#include "Master.h"
#include <DallasTemperature.h>
#include <OneWire.h>

#define BT_V 4
#define BT_GN 5
#define BT_RX_AO 6
#define BT_TX_AI 7

#define PH_SIG A0

#define TEMP_DAT A1

#define TDS_DAT A2

//각각의 센서 추가
BlueT bl( BT_V ,BT_GN ,BT_TX_AI , BT_RX_AO);   //4 핀 모드 생성자 
//PhSensor ph( PH_SIG);
Master ms(&bl);
TempSensor tp(TEMP_DAT);
TdsSensor tds(TDS_DAT);
D_HumidSensor d_h(PH_SIG);
void setup() 
{
  Serial.begin(9600);
   ms.setup();
  
   //연결된 각각의 센서 더함
  // ms.addPh(&ph);
   ms.addD_H(&d_h);
   ms.addTemp(&tp);
   ms.addTds(&tds);

  //각각의 센서 보정
  // ph.setDif(0.5); 
} 

void loop() {
  ms.loop();
  delay(1000);

}
