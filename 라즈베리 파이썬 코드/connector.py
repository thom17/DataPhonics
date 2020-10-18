import BlueT
import mysql.connector as connector
from datetime import datetime
import time;
import requests
class Connector:                    #DB와 Post를 통신함
    def __init__(self):             #생성자로 DB를 연결하고 쿼리문과 url을 저장함
        self.db = connectDatabase();    #DB를 연결하여 반환하는 함수
        self.sql = """INSERT INTO ptt (arduino_id, log, pH, temperature, TDS)
        VALUES (%s, %s, %s, %s, %s)"""
        url = 'http://192.168.1.34/selabfarm/recv_test2.php'

    def checkData(self):                #객체에 저장된 DB의 PTT 테이블을 검색
        cursor = self.db.cursor()           #db의 커서 생성
        cursor.execute("SELECT * FROM ptt") #커서로 쿼리문 실행
        myresult = cursor.fetchall() # 커서의 쿼리문 결과 반환
        for x in myresult:          #결과들 탐색
            print(x)

    def postServer(self, bt, val):          #블루투스 객체, 패킷으로 받은 리스트
        json = {            #서버로 보낼 json 택스트
        "info": { "db":"selabfarm", "security_code":"123" },
         "sensors": []
         };
        index = 0;
        for target : bt.addList:        #블루투스로 연결한 리스트 탐색
            json["sensors"].append(
            {                       #각각의 아두이노의 데이터 값 추가
            "module_id" : target[index][0],
            "log" : val[index][1],
            "ph" : val[index][2],
            "temp" : val[index][3],
            "tds" :val[index][4]
            } )
            index += 1;         #아두이노 인덱스 = 아두이노 번호
        x = requests.post(self.url, json=json); #post 요청
        print(x.text);

    def insertDB(self, bt):         #블루투스 객체를 기준으로 각각 연결하여 DB 삽입
        cursor = self.db.cursor()   #db 커서 생성
        index = 0;              #아두이노의 번호
	    val = [];              #패킷의 데이터 내용
        for target in bt.addList:   #bt 객체의 연결 주소 순환
            rightPacket = False;
            while (not rightPacket):    #올바른 패킷이 될때 까지
                packet = bt.get(target); #패킷을 찾으면(<내용>) 패킷을 아니면 False 반환  <3/5.5/25.55/54/>
               # bt.setTimeout(30);     #차피 연결이 죽어도 쉘에서 블루투스와 파이썬 재시작
               # print(packet);
                rightPacket = decodePacket(packet, str(index) );    #내용의 검증과 삽입하기 위한 리스트로 변경

            index += 1;     #다음 아두이노를 위한 번호 증가
            val.append(rightPacket);        #삽입될 데이터의 리스트에 해당 패킷 데이터 추가

        #print("val =" , val);
        #cursor.execute(sql, val)
        cursor.executemany(self.sql, val);      #최종적인 삽입 쿼리문 실행

        self.db.commit();           #변경 적용
        postServer(bt, val);        #서버에 해당 데이터 전송
        print(cursor.rowcount, "was inserted.")

def decodePacket(packet, index):            #패킷과 아두이노 번호가 들어옴
    strList = packet[1:-2].split("/");              # packet[1:-2] = <내용>\n 에서 내용만 분리 , 그리고 /로 자르기

    if( int(strList[0]) == len(strList)-1 ):        #첫번째 패킷값은 실수 값(데이터)의 개수 로 체크섬
        strList[0] = str(index);                #체크섬을 아두이노 번호로 변경
        now = datetime.now()                #현제 시간 측정

        now = now.strftime('%Y-%m-%d %H:%M:%S');    #시간 형식 지정
        print ("Right packet Make:", now, strList);

        strList.insert(1, now);             #현제 시간을 패킷에 추가 (아두이노 번호 앞)
        print (strList);
        return strList;
    else :                              #체크섬 실패시 잘못된 패킷으로 판단
        return False;


def connectHost():
    # connect to server
    db = connector.connect(
    host="localhost",
    user="james",
    password="1234"
    )
    return db

def connectDatabase():
    # connect to server
    db = connector.connect(
    host="localhost",
    user="james",
    password="1234",
    database="hydrophonics_db"
    )
    return db

# Create DB
def createDB(str):
    newDB = connectHost()
    cursor = newDB.cursor()
    cursor.execute("CREATE DATABASE IF NOT EXISTS " + str + ";") # Create DB called 'center_db'
    cursor.execute("SHOW DATABASES")
    for x in cursor:
        print(x)

# Create ptt Table
def createPttTable():
    currentDB = connectDatabase()
    cursor = currentDB.cursor()
    cursor.execute("USE hydrophonics_db;")
    cursor.execute("CREATE TABLE IF NOT EXISTS ptt (arduino_id TINYINT NOT NULL, log datetime NOT NULL, pH FLOAT, temperature FLOAT, TDS FLOAT);")

# Insert Dummy data
def insertDummies():
    currentDB = connectDatabase()
    cursor = currentDB.cursor()
    now = datetime.now()
    now = now.strftime('%Y-%m-%d %H:%M:%S')
    print(type(now))
    #now = "\'"+now+"\'"
    print("Current Time =", now)
    sql = """INSERT INTO ptt (arduino_id, log, pH, temperature, TDS)
    VALUES (%s, %s, %s, %s, %s)"""

    val = [(2, now, 7.2, 25.43, 800.78),
    (2, now, 7.2, 25.43, 800.78),
    (2, now, 7.2, 25.43, 800.78),
    (2, now, 7.2, 25.43, 800.78),
    (2, now, 7.2, 25.43, 800.78),
    (2, now, 7.2, 25.43, 800.78),
    (2, now, 7.2, 25.43, 800.78),
    (2, now, 7.2, 25.43, 800.78),

    (2, now, 7.2, 25.43, 800.78),
    (2, now, 7.2, 25.43, 800.78),

    ]
    #cursor.execute(sql, val)
    cursor.executemany(sql, val)

    currentDB.commit()

    print(cursor.rowcount, "was inserted.")


# Check data in the table
def checkData():
    currentDB = connectDatabase()
    cursor = currentDB.cursor()
    cursor.execute("SELECT * FROM ptt")
    myresult = cursor.fetchall() # return list of all item from query
    for x in myresult:
        print(x)


"""
# Create lt Table
def createLtTable():
currentDB = connectDatabase()
cursor = currentDB.cursor()
cursor.execute("CREATE TABLE IF NOT EXISTS lt (arduino_id TINYINT NOT NULL, log datetime NOT NULL, pH FLOAT, temperature FLOAT, TDS FLOAT" + ";")
"""

#Drop the Database
"""
def dropDatabase(str):
newDb = connectHost()
cursor = newDB.cursor()
cursor.execute("DROP DATABASE [IF EXISTS] " + str)

"""
#connect to the localHost
#connectHost()

# create DB called with "DB_NAME callsed hydrophonics_db"
#createDB("hydrophonics_db")

# create ptt table
#createPttTable()

# Insert Dummy data
#insertDummies()





# connect BL Data

bird = ( "98:D3:51:FD:E5:0B" , 1);
cat = ( "98:D3:C1:FD:7C:52" , 1 );
tree = ("98:D3:61:FD:82:93" , 1 );
bt02=("98:D3:71:FD:B4:0E", 1);

start = time.time()-120;
#arr = [tree];
arr = [tree, bird, cat, bt02];
blt = BlueT.BlueT(arr);
con = Connector();
while(True):
    now = time.time();
    if ( 60 < now-start ):
        start = time.time();
        print(start);
        con.insertDB(blt);
        con.checkData();
