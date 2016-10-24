#include "ros/ros.h"
#include "geometry_msgs/Pose2D.h"                          // to get desired position command
#include "turtlesim/Pose.h"                                // to read current position
#include "geometry_msgs/Twist.h"                           // to send velocity command

//  TCP connection headers
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <iostream>
#include <string>

#include "/home/bridget/rapidjson-master/include/rapidjson/document.h"
#include "/home/bridget/rapidjson-master/include/rapidjson/writer.h"
#include "/home/bridget/rapidjson-master/include/rapidjson/stringbuffer.h"
#include "/home/bridget/rapidjson-master/include/rapidjson/rapidjson.h"
#include <iostream>

using namespace rapidjson;

// Function declarations
void ComPoseCallback(const geometry_msgs::Pose2D::ConstPtr& msg);
void CurPoseCallback(const turtlesim::Pose::ConstPtr& msg);

//TCP Function declarations
void error(const char *msg)
{
    perror(msg);
    exit(0);
}


// Global variables
bool STOP = true;          
geometry_msgs::Twist CmdVel;                                             // to hold stop flag, wait till first command given
turtlesim::Pose CurPose;                                                // to hold current pose
geometry_msgs::Pose2D DesPose;   

int main(int argc, char **argv)
{

//ROS position commands

    ros::init(argc, argv, "TurtlesimPositionController_pubsub"); // connect to roscore
    ros::NodeHandle n;          

    // register sub to get desired position/pose commands
    ros::Subscriber ComPose_sub = n.subscribe("/turtle1/PositionCommand", 5, ComPoseCallback);
    // register sub to get current position/pose
    ros::Subscriber CurPose_sub = n.subscribe("/turtle1/pose", 5, CurPoseCallback);
    //register sub to get watch values
    ros::Subscriber CurValues_sub = n.subscribe("/home/bridget/Documents/Research/gyroData", 5, CurPoseCallback);
    // register pub to send twist velocity (cmd_vel)
    ros::Publisher Twist_pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 100);

    ros::Rate loop_rate(10);                                            // freq to run loops in (10 Hz)                          // node object


    ROS_INFO("Ready to send position commands");                        // let user know we are ready and good
    while (ros::ok() && n.ok() )                                        // while ros and the node are ok
    {
        ros::spinOnce();
        if (STOP == false)                                              // and no stop command
        {
            printf("Processing...\n");
            Twist_pub.publish(CmdVel);
        }
        else
        {
            printf("Waiting...\n");
        }
        loop_rate.sleep();                                              // sleep to maintain loop rate
    }
    ////////////////////////////
}

// call back to send new desired Pose msgs
void ComPoseCallback(const geometry_msgs::Pose2D::ConstPtr& msg)            
{
    STOP = false;                                                       // start loop
    DesPose.x = msg->x;                                                 // copy msg to varible to use elsewhere
    DesPose.y = msg->y;
    CmdVel.angular.x += 10; //test with 10 
    CmdVel.angular.y += 1;
    CmdVel.angular.z += 1;
    CmdVel.linear.x += 1;
    CmdVel.linear.y += 1;
    CmdVel.linear.z += 1;

    return;
}

// call back to send new current Pose msgs
void CurPoseCallback(const turtlesim::Pose::ConstPtr& msg)          
{
 	CurPose.x = msg->x;
    CurPose.y = msg->y;
    CurPose.theta = msg->theta;                                         // copy msg to varible to use elsewhere
    return;
}