#include <HCSR04.h>
#define dir1 2
#define pwm1 3
#define dir2 4
#define pwm2 5
UltraSonicDistanceSensor R3(13, 10);
UltraSonicDistanceSensor R2(12, 9);
UltraSonicDistanceSensor R1(11, 8);
int ran1 = 35;
int ran2 = 25;
int temperature = 36;
void setup() {
  // put your setup code here, to run once:
  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);
  pinMode(pwm1, OUTPUT);
  pinMode(pwm2, OUTPUT);
  Serial.begin(9600);
}

void sleft() {
  digitalWrite(dir2, HIGH);
  digitalWrite(dir1, LOW);
  analogWrite(pwm1, 100);
  analogWrite(pwm2, 100);
}

void sright() {
  digitalWrite(dir2, LOW);
  digitalWrite(dir1, HIGH);
  analogWrite(pwm1, 100);
  analogWrite(pwm2, 100);
}

void revleft() {
  digitalWrite(dir1, HIGH);
  analogWrite(pwm1, 100);
  analogWrite(pwm2, 0);
}

void revright() {
  digitalWrite(dir2, HIGH);
  analogWrite(pwm1, 0);
  analogWrite(pwm2, 100);
}

void right() {
  digitalWrite(dir1, LOW);
  analogWrite(pwm1, 100);
  analogWrite(pwm2, 0);
}

void left() {
  digitalWrite(dir2, LOW);
  analogWrite(pwm1, 0);
  analogWrite(pwm2, 100);
}

void forward() {
  digitalWrite(dir2, LOW);
  digitalWrite(dir1, LOW);
  analogWrite(pwm1, 100);
  analogWrite(pwm2, 100);
}

void reverse() {
  digitalWrite(dir2, HIGH);
  digitalWrite(dir1, HIGH);
  analogWrite(pwm1, 100);
  analogWrite(pwm2, 100);
}

void loop() {
  int r1 = R1.measureDistanceCm(temperature);

  int r2 = R2.measureDistanceCm(temperature);

  int r3 = R3.measureDistanceCm(temperature);

  delay(200);
  if (r1 < 0) {
    r1 = 40;
  }
  else if (r2 < 0) {
    r2 = 40;
  }
  else if (r3 < 0) {
    r3 = 40;
  }
  Serial.println("r1");
//  Serial.println(r1);
//  Serial.println("r2");
//  Serial.println(r2);
//  Serial.println("r3");
  Serial.println(r3);
  if ((r1 > ran2) && (r1 < ran1)) {//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    right();
    Serial.println("1");
  }
  else if ((r3>ran2) && (r3 < ran1)) { //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    left();
    Serial.println("2");
  }
  else if (r1 < ran2 && r2 < ran2 && r3 < ran2) {//<<<<<<<<<<<<<<<<<<<<<<<<
    reverse();
    delay(500);
    Serial.println("3");
  }
  else if (r2 < 15){
    reverse();
    delay(500);
    sleft();
    delay(1500);
  }
  else if (r1 < ran2 && r3 < ran2) {//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    reverse();
    delay(500);
    sleft();
    Serial.println("4");
    delay(500);
  }
  else if (r1 < ran2 || r2 < ran2 || r3 < ran2) {//<<<<<<<<<<<<<<<<<<
    if (r1 < ran2) {//xxxxxxxxxxxxxxxxxxxxxx
      sright();
      Serial.println("5");
      delay(400);
    } 
    else if (r3 < ran2) {//xxxxxxxxxxxxxxxxx
      sleft();
      Serial.println("8");
      delay(400);
    }
    else if (r2 < ran2) {//xxxxxxxxxxxxxxxxx
      if (r1 > r3) {//......................
        left();
        Serial.println("6");
      }
      else {//..............................
        right();
        Serial.println("7");
      }
    }
  }
  else { //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    forward();
    Serial.println("9");
  }
}
