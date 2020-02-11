#include <Arduino.h>
#include <Servo.h>
#include <robot_6.h>

#define L1 10.5
#define L2 4.0
#define L3 11.5
#define L4 13.5
#define L5 11.5
#define S1 11.5
#define S2 3.1
#define S3 11.5
#define S4 3.8
#define X_LOWER_LIMIT -15
#define X_UPPER_LIMIT 15
#define Y_LOWER_LIMIT 12
#define Y_UPPER_LIMIT 25
#define Z_LOWER_LIMIT 0
#define Z_UPPER_LIMIT 10

#define INIT_X 0
#define INIT_Y 16
#define INIT_Z 3
#define speed_devisor 15

robot_6 robot(L1, L2, L3, L4, L5, S1, S2, S3, S4, X_LOWER_LIMIT, X_UPPER_LIMIT, Y_LOWER_LIMIT, Y_UPPER_LIMIT, Z_LOWER_LIMIT, Z_UPPER_LIMIT);

Servo servo[6]; //without servo[0]
int servo_pin[6] = {0, 2, 3, 4, 6, 7};
int default_degree[6] = {0, 95, 45, 90, 95, 90};

void move(float tar_x,float tar_y,float tar_z);

void change_to(float t1,float t2,float t3,float t4);

void setup()
{
  Serial.begin(9600);
  Serial.println("Begin Serial");
  for (int i = 1; i <= 5; i++)
    servo[i].attach(servo_pin[i]);
  for (int i = 1; i <= 5; i++)
    servo[i].write(default_degree[i]);
}

String str = "";
int iter=0;
float tar_x=0;
float tar_y=0;
float tar_z=0;

void loop()
{
  while(Serial.available()){
    iter=0;
    String x_part="",y_part="",z_part="";
    str=Serial.readString();
    if(str[iter++]=='#'){
      while(str[iter++]!='@') x_part+=str[iter-1];
      tar_x=atoi(x_part.c_str());

      while(str[iter++]!='@') y_part+=str[iter-1];
      tar_y=atoi(y_part.c_str());

      while(str[iter++]!='@') z_part+=str[iter-1];
      tar_z=atoi(z_part.c_str());

      // Serial.print("X:");
      // Serial.println(tar_x);
      // Serial.print("Y:");
      // Serial.println(tar_y);
      // Serial.print("Z:");
      // Serial.println(tar_z);

      move(tar_x,tar_y,tar_z);

    }
  }
}

void move(float tar_x,float tar_y,float tar_z){
  float t1=0,t2=0,t3=0,t4=0;
  static float pre_x=INIT_X,pre_y=INIT_Y,pre_z=INIT_Z;
  Serial.print("Processing  X:");Serial.print(pre_x);Serial.print(" to ");Serial.println(tar_x);
  Serial.print("Processing Y:");Serial.print(pre_y);Serial.print(" to ");Serial.println(tar_y);
  Serial.print("Processing Z:");Serial.print(pre_z);Serial.print(" to ");Serial.println(tar_z);
  robot.get_rotate_degree(pre_x,pre_y,pre_z,t1,t2,t3,t4);
  change_to(t1,t2,t3,t4);

  delay(200);
  for(int i=1;i<=speed_devisor;i++){
    Serial.print("X:");Serial.print(pre_x + (tar_x-pre_x)/speed_devisor*i);Serial.print("   ");
    Serial.print("Y:");Serial.print(pre_y + (tar_y-pre_y)/speed_devisor*i);Serial.print("   ");
    Serial.print("Z:");Serial.print(pre_z + (tar_z-pre_z)/speed_devisor*i);Serial.println("   ");
    robot.get_rotate_degree(pre_x + (tar_x-pre_x)/speed_devisor*i,pre_y + (tar_y-pre_y)/speed_devisor*i,pre_z + (tar_z-pre_z)/speed_devisor*i,t1,t2,t3,t4);
    change_to(t1,t2,t3,t4);

    delay(30);
  }

  pre_x=tar_x;
  pre_y=tar_y;
  pre_z=tar_z;
}

void change_to(float t1,float t2,float t3,float t4){
  Serial.print("t1:");Serial.print(t1);Serial.print("t2:");Serial.print(t2);Serial.print("t3:");Serial.print(t3);Serial.print("t4:");Serial.println(t4);
  servo[2].write(t1);
  servo[3].write(t2);
  servo[4].write(t3);
  servo[1].write(t4);
}