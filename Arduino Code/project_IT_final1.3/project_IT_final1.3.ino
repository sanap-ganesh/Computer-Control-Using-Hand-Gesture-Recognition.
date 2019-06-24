#include<Wire.h>
int btnPin1 = 13;
int precBtn1 = HIGH;
const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ; // declare accellerometer and gyro variables
void setup(){
  pinMode(btnPin1, INPUT_PULLUP);
  Wire.begin(); // initiate i2c system
  Wire.beginTransmission(MPU_addr); // be sure we talk to our MPU vs some other device
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true); // done talking over to MPU device, for the moment
  Serial.begin(9600); // initialize serial port to 9600 bps so you can see your debug messages in Arduino IDE via debug channel
}
void loop(){ // main program loop
   int resultBtn1 = digitalRead(btnPin1);
  if (precBtn1 == HIGH && resultBtn1 == LOW)
  {
    startBatch();
  }
  if (resultBtn1==LOW)
  {
    Wire.beginTransmission(MPU_addr); // get ready to talk to MPU again
    Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
    Wire.endTransmission(false); // done talking to MPU for the time being
    Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  // all the fancy <<8| stuff is to bit shift the first 8 bits to
  // the left & combine it with the next 8 bits to form 16 bits
    AcX=Wire.read()<<4|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
    AcY=Wire.read()<<4|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
    AcZ=Wire.read()<<4|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
    Tmp=Wire.read()<<4|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
    GyX=Wire.read()<<4|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
    GyY=Wire.read()<<4|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
    GyZ=Wire.read()<<4|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
 
  // the above lines have gathered Accellerometer values for X, Y, Z
  //  as well as Gyroscope values for X, Y, Z
    Serial.print("START");
    Serial.print(" "); Serial.print(AcX); // share accellerometer values over debug channel 
    Serial.print(" "); Serial.print(AcY);
    Serial.print(" "); Serial.print(AcZ);
   // Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53);  //equation for temperature in degrees C from datasheet
    Serial.print(" "); Serial.print(GyX); // share gyroscope values over debug channel
    Serial.print(" "); Serial.print(GyY);
    Serial.print(" "); Serial.print(GyZ);
    Serial.println(" END");
  }
    // Closes the batch when the button is released
  if (precBtn1 == LOW && resultBtn1 == HIGH)
  {
    closeBatch();
  }
  // Saves the button states
  precBtn1 = resultBtn1;
}

 

// Sends the started batch signal
void startBatch()
{
  Serial.println("STARTING BATCH");
}

// Sends the closed batch signal
void closeBatch()
{
  Serial.println("CLOSING BATCH");
}
