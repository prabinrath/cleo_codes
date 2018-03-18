#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include "myfirstros_node/Num.h"
#include <sstream>

int32_t ans=0;
bool cnt=false;

void chatterCallback(const myfirstros_node::Num::ConstPtr& msg)
{
  if(msg->ch=='+')
	ans=msg->num1+msg->num2;
  else if(msg->ch=='-')
	ans=msg->num1-msg->num2;
  else if(msg->ch=='*')
	ans=msg->num1*msg->num2;
  else if(msg->ch=='/')
	ans=msg->num1/msg->num2;
  cnt=true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "bcast");

  ros::NodeHandle n;
  
  ros::Subscriber sub = n.subscribe("question", 1000, chatterCallback);
 

  ros::Publisher chatter_pub = n.advertise<std_msgs::Int32>("answer", 1000);
  ros::Rate loop_rate(5);
  while(ros::ok())
   {
    std_msgs::Int32 msg1;

    msg1.data =ans;
    if(cnt==true)
    {chatter_pub.publish(msg1);cnt=false;}
    loop_rate.sleep();
    ros::spinOnce();
   }

  return 0;
}
