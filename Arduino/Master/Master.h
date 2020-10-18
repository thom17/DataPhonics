#pragma once
#include "BlueT.h"
//#include "PhSensor.h"
#include "TempSensor.h"
#include "TdsSensor.h"
#include "D_HumidSensor.h"
//#include "LightSensor.h"


class Master
{
private:
  int count= 0;       //연결된 센서의 개수
  int repeat = 10;  //측정 반복 수 (대략) - 최종적으로 중앙 및 평균 값 도출

  float tempC = 26.6;

  BlueT *blueT;           //필수 블루투스 객체 해당 객체를 기반으로 마스터 생성
  
  //이후 각각의 객체는 연결하면 포인터로 연결 없다면 연결되지 않은 센서
  D_HumidSensor *d_h = NULL; 
  TempSensor *temp = NULL;
  TdsSensor *tds = NULL;
 // LightSensor *light = NULL; //<-- 1

  //repeat 값을 기반으로 반복 측정후 결과 값(float)을 문자열로 반환
  String d_hSense();
  String tempSense();
  String tdsSense();
//  String lightSense(); //<-- 2

public:
  Master(BlueT *bt);  //Bt 모듈을 기반으로 생성
  /* 블루투스 기반 마스터 객체 생성
   * 시리얼통신, 블루투스 setup()
   */
   
  //add list: 연결된 각 센서의 객체를 더해주는 함수 리스트 count++
//  void addPh(PhSensor* ph);
  void addTemp(TempSensor *temp);
  void addTds(TdsSensor *tds);
  void addD_H(D_HumidSensor *d_h);
 // void addLight(LightSensor *light); //<-- 3

  String Master::sensWrite(); //최종적으로 패킷을 생성하는 함수
  /*
   * return "<"+count+"/" + phSense(3) + tempSense(5) + tdsSense(30)+">";
   * 패킷 내용 작업
   */

  void setup(); //블루투스 셋업
  void loop();  //main함수 핵심적인 함수들의 모임 
  /*senseWrite로 패킷 생성
   * 생성된 패킷 블루투스에게 통신 요청 
   * 필요한 통신 작업 여기서
  */
};
