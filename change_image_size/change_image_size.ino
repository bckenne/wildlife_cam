byte incomingbyte;
void setup()
{
  // put your setup code here, to run once:
  delay(500);
  Serial.begin(38400);
  Serial1.begin(38400);
  Serial.println("reset");
  delay(500);
  SendResetCmd();
  delay(3000);
  Serial.println();
  while(Serial1.available()>0){
       incomingbyte=Serial1.read();
           if(incomingbyte<0x10) Serial.print("0");
           Serial.print(incomingbyte,HEX);
           Serial.print(" ");
     }
  Serial.println();
  Serial.println("change size");
  ChangeSizeSmall();
  delay(200);
  while(Serial1.available()>0){
       incomingbyte=Serial1.read();
           if(incomingbyte<0x10) Serial.print("0");
           Serial.print(incomingbyte,HEX);
           Serial.print(" ");
     }  
}

void loop()
{
  // put your main code here, to run repeatedly:
  
}
void SendResetCmd() {
  Serial1.write((byte)0x56);
  Serial1.write((byte)0x00);
  Serial1.write((byte)0x26);
  Serial1.write((byte)0x00);   
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
