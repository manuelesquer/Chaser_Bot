#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "ball_chaser/DriveToTarget.h"
#include <string>
#include <sstream>


// ROS::Publisher motor commands;
ros::Publisher motor_command_publisher;


bool handle_drive_request (ball_chaser::DriveToTarget::Request& req, ball_chaser::DriveToTarget::Response& res){

        ROS_INFO("DriveToTargetRequest received - linearx:%1.2f, angular_z:%1.2f", (float)req.linear_x, (float)req.angular_z);

	float linearx = req.linear_x;
	float angularz = req.angular_z;

	// Create a motor_command object of type geometry_msgs::Twist
        geometry_msgs::Twist motor_command;
        motor_command.linear.x = linearx;
        motor_command.angular.z = angularz;
        // Publish angles to drive the robot
        motor_command_publisher.publish(motor_command);
	
	// Convert float to string due to problems with std::to_string()
	std::ostringstream linx; 
	std::ostringstream angz; 
	linx << linearx;
	angz << angularz;

	// Return a response message
	res.msg_feedback = "Velocities set - linear_x: " + linx.str() + " , angular_z: " + angz.str();
	ROS_INFO_STREAM(res.msg_feedback);

	return true;

}
int main(int argc, char** argv)
{
    // Initialize a ROS node
    ros::init(argc, argv, "drive_bot");

    // Create a ROS NodeHandle object
    ros::NodeHandle n;

    // Inform ROS master that we will be publishing a message of type geometry_msgs::Twist on the robot actuation topic with a publishing queue size of 10
    motor_command_publisher = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

    ros::ServiceServer service = n.advertiseService("/ball_chaser/command_robot",handle_drive_request);
    ROS_INFO("Ready to send car's instructions");

    ros::spin();

    return 0;
}

