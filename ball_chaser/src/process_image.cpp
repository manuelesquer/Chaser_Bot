#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    ball_chaser::DriveToTarget srv;
    srv.request.linear_x=lin_x;
    srv.request.angular_z=ang_z;
    
    // Call the safe_move service and pass the requested joint angles
    if (!client.call(srv))
        ROS_ERROR("Failed to call service command_robot");
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{
    int white_pixel = 255;
    float boundaries = img.step/3;
    bool finded=false;
    for(int i = 0; i<img.height*img.step;i++){
	if (img.data[i]==white_pixel && img.data[i+1]==white_pixel && img.data[i+2]==white_pixel){
	    finded = true;
	    float pixel_positionx=i%img.step;
	    if (pixel_positionx/boundaries<1.0){
		drive_robot(0.0,0.4);
	    }
	    else if ((pixel_positionx/boundaries>1.0) && (pixel_positionx/boundaries<2.0)){
		drive_robot(0.4,0.0);
		}
	    else if ((pixel_positionx/boundaries>2.0) && (pixel_positionx/boundaries<3.0)){
		drive_robot(0.0,-0.4);
		}
	    else{
		//ERROR
		ROS_ERROR("Error in the calculation of the position of the ball");
	    }
	    break;
	}
	   
   }
   if (finded == false){
   ROS_INFO("Ball not found. Vehicule stopped");
   drive_robot(0.0,0.0);
   } 
}


int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}
