#include <SPI.h>
#include <MFRC522.h>
#include<Servo.h>

Servo myservo;
int pos = 0;
int count_tem = 0;

#define RST_PIN         9
#define SS_PIN          10
MFRC522 mfrc522(SS_PIN, RST_PIN);
unsigned long uidDec, uidDecTemp;

void setup() {
  myservo.attach(5);
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  
  myservo.write(0);
}
void loop() {
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  uidDecTemp = 0 ;
  uidDec = 0;
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    uidDecTemp = mfrc522.uid.uidByte[i];
    uidDec = uidDec*256+uidDecTemp;
    
  } 
  Serial.println(uidDec);
  
  if(uidDec == 3672568903){
    count_tem++;
    if(count_tem%2 == 0){
      myservo.write(0);
    }else{
      myservo.write(180);
    }
    Serial.println(count_tem%2);
  }
  
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
  
}
