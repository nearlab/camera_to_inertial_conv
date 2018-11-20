//TODO: tAKE IN NAME OF TOPICS TO CONVERT FROM, TO, AND USE AS CAMERA INFO
#include <ros/ros.h>
#include <time.h>
#include <geometry_msgs/Vector3.h>
#include <Eigen/Dense> 

#include "pv_estimator/Meas.h"

#include <string>
#include <cstring>
#include <array>



ros::Publisher pub;
ros::Subscriber sub;

void pvCallback(pv_estimator::State msg){
  geometry_msgs::Vector3 vec;
  vec.x = msg.r[0]*.01/640/.005;
  vec.y = msg.r[1]*.01/480/.005;
  vec.z = 1;
  pub.publish(vec);
}

int main(int argc, char** argv){
  ros::init(argc,argv,"camera_to_inertial");//This should change based on which nodes you're converting, how many of this type are already running
  ros::NodeHandle nh;

  pub = nh.advertise<geometry_msgs::Vector3>(std::string("/tracker/inertial"),1000);
  sub = nh.subscribe(std::string("/tracker/meas"),1000,pvCallback);
  ros::spin();
}






