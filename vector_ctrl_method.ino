#include <HCSR04.h>
#include "Complex.h"
UltraSonicDistanceSensor right(13, 10);
UltraSonicDistanceSensor centre(12, 9);
UltraSonicDistanceSensor left(11, 8);
#define dir1 2
#define pwm1 3
#define dir2 4
#define pwm2 5
float r1, r2, r3 = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  float r1 = left.measureDistanceCm();
  float r2 = centre.measureDistanceCm();
  float r3 = right.measureDistanceCm();
  float c2 = 7; //It will mememic r2 by having a very small
  //value so just to maximize the angle between resultant vectors
  Complex c1(r1 * 0.707, -r1 * 0.707);
  Complex c3(r3 * 0.707, r3 * 0.707);
  Complex c(0, 0);
  float k = ((r1 - r3) / (r1 + r3)) * 16.667; //k useful between range 0 and 0.58 only
  //Serial.println(r1);
  //Serial.println(r3);
  //Serial.println(k);
  //Serial.println(c1);
//  c1 = c1 + c2;
//  c3 = c3 + c2;
  c = c1 + c3 + c2;
  
  float ohm = (atan(c.imag()/c.real()))*114.64968; //285 for range between 0 to 180 degrees
  Serial.println(ohm);
  Serial.println(c) ;
  delay(150);
}
