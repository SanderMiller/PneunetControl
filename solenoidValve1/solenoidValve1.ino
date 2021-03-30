#include <DRV8835MotorShield.h>
int solenoidPin = 4;


DRV8835MotorShield motors;
void setup() {
  // put your setup code here, to run once:
  pinMode(solenoidPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
   
digitalWrite(solenoidPin, HIGH);    //Switch Solenoid ON
  motors.setM1Speed(100);
  delay(1100);                      //Wait 1 Second
  motors.setM1Speed(00);
  delay(1000);  digitalWrite(solenoidPin, LOW);     //Switch Solenoid OFF
   motors.setM1Speed(00);
  delay(1000);       
}
