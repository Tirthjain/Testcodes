#include <HCSR04.h>

UltraSonicDistanceSensor right(13, 10);
UltraSonicDistanceSensor centre(12, 9);
UltraSonicDistanceSensor left(11, 8);
#define dir1 2
#define pwm1 3
#define dir2 4
#define pwm2 5
void setup() {
  Serial.begin(9600);

}
//k useful between range 0 and 0.58 only
void loop() {
  // put your main code here, to run repeatedly:
  float r1 = left.measureDistanceCm();
  float r2 = centre.measureDistanceCm();
  float r3 = right.measureDistanceCm();
  //Serial.println(r1);
  //Serial.println(r3);
  float k = ((r1 - r3) / (r1 + r3))*16.667;//k useful between range 0 and 0.58 only before multiplication 
  Serial.println(k); //k useful between range 0 and 0.58 only
  delay(150);
}
