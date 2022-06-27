#include <HCSR04.h>

UltraSonicDistanceSensor right(13, 10);
UltraSonicDistanceSensor centre(12, 9);
UltraSonicDistanceSensor left(11, 8);
#define dir1 2
#define pwm1 3
#define dir2 4
#define pwm2 5
int c = 2;
void setup () {
  Serial.begin(9600);  // We initialize serial connection so that we could print values from sensor.
  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);
  pinMode(pwm1, OUTPUT);
  pinMode(pwm2, OUTPUT);
}

void loop () {

  float r1 = left.measureDistanceCm();
  float r2 = centre.measureDistanceCm();
  float r3 = right.measureDistanceCm();
  float k = (r1 - r3) / (r1 + r3);
  //  Serial.println("r1:");
  //  Serial.println(r1);
  //  Serial.println("r2");
  //  Serial.println(r2);
  //  Serial.println("r3");
  //  Serial.println(r3);

  if (r1 >= 40 || r1 == -2)
    r1 = 40;
  if (r2 >= 40 || r2 == -1)
    r2 = 40;
  if (r3 >= 40 || r3 == -1)
    r3 = 40;
  if (r2 < 18)
  {
    digitalWrite(dir2, HIGH);
    digitalWrite(dir1, HIGH);
    analogWrite(pwm2, 80);
    analogWrite(pwm1, 80);
    Serial.println("1");
    delay(700);
    if (r1 > r3) {
      digitalWrite(dir2, HIGH);
      digitalWrite(dir1, LOW);
      analogWrite(pwm1, 80);
      analogWrite(pwm2, 80);
      Serial.println("2");
      delay(800);
    }
    else {
      digitalWrite(dir2, LOW);
      digitalWrite(dir1, HIGH);
      analogWrite(pwm1, 80);
      analogWrite(pwm2, 80);
      Serial.println("3");
      delay(500);
    }
  }
  if (r1 >= 35 && r2 >= 35 && r3 >= 35)
  {
    digitalWrite(dir2, LOW);
    digitalWrite(dir1, LOW);
    analogWrite(pwm2, 60);
    analogWrite(pwm1, 60);
    Serial.println("4");
  }
  else if (r1 < 25 && r2 < 18)
  {
    digitalWrite(dir2, LOW);
    digitalWrite(dir1, HIGH);
    analogWrite(pwm2, 80);
    analogWrite(pwm1, 80);
    Serial.println("5");
  }
  else if (r2 < 18 && r3 < 25)
  {
    digitalWrite(dir2, HIGH);
    digitalWrite(dir1, LOW);
    analogWrite(pwm2, 80);
    analogWrite(pwm1, 80);
    Serial.println("6");
  }
  else
  {
    if (k > 0.4 && k <= 1)
    {
      digitalWrite(dir2, LOW);
      digitalWrite(dir1, LOW);
      analogWrite(pwm1, 100 * (k) * c);
      analogWrite(pwm2, 80 * (1 - k) * c);
      Serial.println("7");
    }
    else if (k >= 0 && k <= 0.38)
    {
      if ((r1 + r3) / 1.414 > 55) {
        digitalWrite(dir2, LOW);
        digitalWrite(dir1, LOW);
        analogWrite(pwm1, 80);
        analogWrite(pwm2, 80);
        Serial.println("8");
      }
    }
    else if (k >= -0.4 && k < 0)
    {
      if ((r1 + r3) / 1.414 > 55) {
        digitalWrite(dir2, LOW);
        digitalWrite(dir1, LOW);
        analogWrite(pwm1, 80);
        analogWrite(pwm2, 80);
        Serial.println("10");
      }
      else {
        digitalWrite(dir2, HIGH);
        digitalWrite(dir1, HIGH);
        analogWrite(pwm1, 80 * k * c);
        analogWrite(pwm2, 80 * (1 + k) * c);
        Serial.println("11");
      }
    }
    else if (k >= -1 && k < -0.38)
    {
      digitalWrite(dir2, LOW);
      digitalWrite(dir1, LOW);
      analogWrite(pwm1, 80 * (1 + k) * c);
      analogWrite(pwm2, 80 * (-k) * c);
      Serial.println("12");
    }
  }
}
