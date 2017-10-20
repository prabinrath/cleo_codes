#include "ros/ros.h"
#include <drive/drivedata.h>

void chatterCallback(const drive::drivedata::ConstPtr& msg)
{
  ROS_INFO("%d %d %c", msg->num1,msg->num2,msg->drive);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "check");

  
  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("check", 1000, chatterCallback);

  ros::spin();

  return 0;
}
