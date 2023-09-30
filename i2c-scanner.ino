#include<Wire.h>
void setup(){
  Wire.begin();
  Serial.begin(9600);
  Serial.println("I2C scanner is ready.");
  Serial.println();
}
void loop() {
  scanI2C(100000);
  scanI2C(400000);
  scanI2C(1000000); // uncomment if the microcontroller supports this speed
  scanI2C(3400000); // uncomment if the microcontroller supports this speed
  scanI2C(5000000); // uncomment if the microcontroller supports this speed
  
  Serial.println("****************************");
  Serial.println();
  delay(6000);
}
void scanI2C(long frequency){
  String normal = "standard mode (100 kHz):";
  String fast = "fast mode (400 kHz):";
  String fastPlus = "fast mode plus (1 MHz):";
  String highSpeed = "high speed mode (3.4 MHz):";
  String ultraSpeed = "ultra fast mode (5.0 MHz):";
  String defaultStr = " !!!!! This speed is not supported !!!!!";
  bool error = true;
  bool addressFound = false;
  Serial.print("Scanning in ");
  switch(frequency){
    case 100000:
      Serial.println(normal);
      break;
    case 400000:
      Serial.println(fast);
      break;
    case 1000000:
      Serial.println(fastPlus);
      break;
    case 3400000:
      Serial.println(highSpeed);
      break;
    case 5000000:
      Serial.println(ultraSpeed);
      break;
    default:
      Serial.println(defaultStr);
      break;
  }
  
  Wire.setClock(frequency);
  for(int i=1; i<128; i++){
    Wire.beginTransmission(i);
    error = Wire.endTransmission();
    if(error == 0){
      addressFound = true;
      Serial.print("0x");
      Serial.println(i,HEX);
    }
  }
  if(!addressFound){
    Serial.println("No I2C device found");
  }
  Serial.println();
}
