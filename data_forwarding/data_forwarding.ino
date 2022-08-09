#include <ros.h>
#include <std_msgs/Float32.h>

#define Trig 2
#define Echo 3
#define ANGLE A5

float cm;
float temp;
float angle;

ros::NodeHandle nh;
std_msgs::Float32 Distance;
std_msgs::Float32 Angle;

ros::Publisher pub1("ROSTopic/distance", &Distance);
ros::Publisher pub2("ROSTopic/angle", &Angle);

void setup() {
  Serial.begin(9600);
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  nh.initNode();
  nh.advertise(pub1);
  nh.advertise(pub2);
}


void loop() {
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(2);
  digitalWrite(Trig, LOW);

  temp = float(pulseIn(Echo, HIGH));

  cm = (temp * 17) / 1000;

  angle = analogRead(ANGLE) * 0.36;

  Distance.data = (cm - 6) / 100;

  //Angle.data = angle;

  Angle.data = (0 - (angle - 104.04) * 3.14 / 180);

  pub1.publish(&Distance);

  pub2.publish(&Angle);

  nh.spinOnce();
  delay(10);
}
