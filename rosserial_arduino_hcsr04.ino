#include <HCSR04.h>
#include <ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Float64.h>
UltraSonicDistanceSensor distanceSensor(7, 6);

ros::NodeHandle  nh;

std_msgs::Float32 flo_msg;
float distances;
ros::Publisher chatter("chatter", &flo_msg);

void setup() {
  nh.initNode();
  nh.advertise(chatter);
}

void loop() {
  // put your main code here, to run repeatedly:

  distances = distanceSensor.measureDistanceCm();
  flo_msg.data = distances;
  chatter.publish( &flo_msg );
  nh.spinOnce();
  delay(100);
}
