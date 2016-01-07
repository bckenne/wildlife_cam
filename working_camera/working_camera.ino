#include <SoftwareSerial.h> 

byte incomingbyte;
int pirPin = P8_7;
//Configure pin 2 and 3 as soft serial port
//SoftwareSerial Serial1 = SoftwareSerial(P4_3, P4_2); 

int a=0x0000,  //Read Starting address     
    j=0,
    k=0,
    count=0;
uint8_t MH,ML;
boolean EndFlag=0;


void setup() { 
  Serial.begin(115200);
  Serial1.begin(38400);
  delay(3000);
  Serial.println();
  Serial.println("Sending reset");
  SendResetCmd();
  delay(3000);
  while(Serial1.available()>0){
       incomingbyte=Serial1.read();
  }
  Serial.println();
  Serial.println("sending change baud");
  ChangeBaud();
  delay(100);
  while(Serial1.available()>0){
       incomingbyte=Serial1.read();
  }
  Serial1.begin(115200);
  pinMode(pirPin, INPUT);
  Serial.println();
  Serial.println("READY");
  Serial.println();
  /*while(Serial1.available()>0){
       incomingbyte=Serial1.read();
           if(incomingbyte<0x10) Serial.print("0");
           Serial.print(incomingbyte,HEX);
           Serial.print(" ");
     }*/
}

void loop() {
 int pirVal = analogRead(pirPin);
  //Serial.println(pirVal);
  if(pirVal <  200){ //was motion detected
    //Serial.println("Motion Detected"); 
    getPic(); 
    delay(1000);
  }
}

//Send Reset command
void SendResetCmd() {
  Serial1.write((byte)0x56);
  Serial1.write((byte)0x00);
  Serial1.write((byte)0x26);
  Serial1.write((byte)0x00);   
}

//Send take picture command
void SendTakePhotoCmd() {
  Serial1.write((byte)0x56);
  Serial1.write((byte)0x00);
  Serial1.write((byte)0x36);
  Serial1.write((byte)0x01);
  Serial1.write((byte)0x00);
    
  a = 0x0000; //reset so that another picture can taken
}

void FrameSize() {
  Serial1.write((byte)0x56);
  Serial1.write((byte)0x00);
  Serial1.write((byte)0x34);
  Serial1.write((byte)0x01);
  Serial1.write((byte)0x00);  
}

//Read data
void SendReadDataCmd() {
  MH=a/0x100;
  ML=a%0x100;
      
  Serial1.write((byte)0x56);
  Serial1.write((byte)0x00);
  Serial1.write((byte)0x32);
  Serial1.write((byte)0x0c);
  Serial1.write((byte)0x00);
  Serial1.write((byte)0x0a);
  Serial1.write((byte)0x00);
  Serial1.write((byte)0x00);
  Serial1.write((byte)MH);
  Serial1.write((byte)ML);
  Serial1.write((byte)0x00);
  Serial1.write((byte)0x00);
  Serial1.write((byte)0x00);
  Serial1.write((byte)0x08);
  Serial1.write((byte)0x00);
  Serial1.write((byte)0x0a);

  a+=0x08; 
}

void StopTakePhotoCmd() {
  Serial1.write((byte)0x56);
  Serial1.write((byte)0x00);
  Serial1.write((byte)0x36);
  Serial1.write((byte)0x01);
  Serial1.write((byte)0x03);        
}

void ChangeSizeSmall() {
    Serial1.write((byte)0x56);
    Serial1.write((byte)0x00);
    Serial1.write((byte)0x31);
    Serial1.write((byte)0x05);
    Serial1.write((byte)0x04);
    Serial1.write((byte)0x01);
    Serial1.write((byte)0x00);
    Serial1.write((byte)0x19);
    Serial1.write((byte)0x22);      
}

void ChangeSizeMedium()
{
    Serial1.write((byte)0x56);
    Serial1.write((byte)0x00);
    Serial1.write((byte)0x31);
    Serial1.write((byte)0x05);
    Serial1.write((byte)0x04);
    Serial1.write((byte)0x01);
    Serial1.write((byte)0x00);
    Serial1.write((byte)0x19);
    Serial1.write((byte)0x11);      
}

void ChangeSizeBig()
{
    Serial1.write((byte)0x56);
    Serial1.write((byte)0x00);
    Serial1.write((byte)0x31);
    Serial1.write((byte)0x05);
    Serial1.write((byte)0x04);
    Serial1.write((byte)0x01);
    Serial1.write((byte)0x00);
    Serial1.write((byte)0x19);
    Serial1.write((byte)0x00);      
}

void ChangeBaud()
{
    Serial1.write((byte)0x56);
    Serial1.write((byte)0x00);
    Serial1.write((byte)0x24);
    Serial1.write((byte)0x03);
    Serial1.write((byte)0x01);
    Serial1.write((byte)0x0d);
    Serial1.write((byte)0xa6);
          
}

void getPic(){
  SendTakePhotoCmd();
  Serial.println();
  Serial.println("START"); 
  delay(100);

  while(Serial1.available()>0) {
    incomingbyte=Serial1.read();
  }
  byte b[10];
      
  while(!EndFlag) {  
    j=0;
    k=0;
    count=0;
    SendReadDataCmd();
           
    delay(25); //try going up
    while(Serial1.available()>0) {
      incomingbyte=Serial1.read();
      k++;
      if((k>5)&&(j<8)&&(!EndFlag)) {
        b[j]=incomingbyte;
        if((b[j-1]==0xFF)&&(b[j]==0xD9))
        EndFlag=1;                           
        j++;
        count++;
      }
    }
            
    for(j=0;j<count;j++) {   
      if(b[j]<0x10)
        Serial.print("0");
      Serial.print(b[j], HEX);
    }
    Serial.println();  
  }
  
  delay(100);
  StopTakePhotoCmd(); //stop this picture so another one can be taken
  EndFlag = 0; //reset flag to allow another picture to be read
  Serial.println("END");
  Serial.println();
}
