import bluetooth as BL


# 타겟 = 각각의 ( 블루투스 주소 , 포트넘버)
bird = ( "98:D3:51:FD:E5:0B" , 1);
cat = ( "98:D3:C1:FD:7C:52" , 1 );
tree = ("98:D3:61:FD:82:93" , 1 );
bt02=("98:D3:71:FD:B4:0E", 1);


class BlueT:
    def __init__(self, addList):        #생성자 타겟 리스트를 받음
        self.addList = addList;         #연결한 타겟 리스트
        self.count =len(addList);       #타겟 리스트의 길이
        self.bl = BL.BluetoothSocket(BL.RFCOMM);    #블루투스 소켓 생성

    def get(self, target):                          #타겟이 주어지면 연결하여 데이터를 받음
        self.bl = BL.BluetoothSocket(BL.RFCOMM);    #재연결시 필요 초기화 역활
        self.bl.connect(target);                #타겟과 라즈베리 블루투스 페어링
        packet = False;                         #최종적으로 받게 될 성공적인 패킷 즉 목표
        while(not packet):                      #패킷이 아직 완성되지 않음
            packet = getPacket(self.bl);        #패킷이 있다면 반환하고 아니면 False
        self.bl.close()                         #성공적으로 통신이 되었으므로 블루투스 연결 종료
        return packet;                          #패킷 반환

    def getAll(self):                           #객체의 모든 타겟 리스트 패킷 반환
        result = [];                        #결과가 될 리스트
        for target in self.addList:             #순차적으로 결과에 더함
            result.append(self.get(target));
        return result;



def getPacket(bl):          #연결된 상태의 블루투스 모듈에서 패킷을 찾아서 얻는 함수

    buf="";         #버퍼 준비

    finish = False;     #완료됬다면 패킷이 됨

    while( not finish ):

        msg = bl.recv(28);          #블루투스 수신 (byte 형)
        msg = str(msg.decode());    #수신된 데이터 문자열(아스키)로 변경
        buf += msg.rstrip();        #최종적으로 공백을 지워 깨끗하게 버퍼에 담음
        print(buf);                 #버퍼가 쌓이는 과정 출력 (디버그 함수)
        finish = findPacket(buf);   #만약 버퍼에 패킷이 온전히 있다면 그 패킷을 반환

    return finish;



def findPacket(msg):    #온전한 패킷을 찾는 함수 (버퍼를 매개변수로)
    st = 0;
    #print(type(msg));
    st = msg.find('<'); #패킷의 시작이 있다면 해당 위치를 반환 (첫번째)

    if(st < 0):         #없었다면 -1을 반환하고 패킷을 찾지 못함
        return False;

    ed = msg[st:].find('>')+st; #있다면 그 뒤로부터 하여 닫히는 패킷 '>'을 찾음

    if(ed < 0):             #역시 없었다면 -1 반환
        return False;

    return msg[st:ed+1];    #최종적으로 찾은 패킷의 시작과 끝을 기준으로 버퍼 짤라 반환
#arr = [tree, bird];
#test = BlueT(tree);
#print test.get(tree);
#print(test.getAll());
