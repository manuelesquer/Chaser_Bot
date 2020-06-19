# Chaser_Bot
This is a simple bot simulation of a 2 wheels robot with a LIDAR and a camera that chase a white ball in a scenario. This example consists in the basic function of image collection and processing and then move the robot properly. This simulation is implemented in Gazebo with ROS connectivity and in C++.

## Install

For the installation you would need:
* ROS kinetic version or further. 
* Gazebo application.

To get this program ready you have to clone this repository in your src folder, *catkin_make* and then execute these launch files:

Firstly, the launch file to execute the scenario in Gazebo:
'roslaunch my_robot world.launch'

Secondly, you have to launch the functionalities of the robot:
'roslaunch ball_chaser ball_chaser.launch'

## Quick Note

The ball that the robot will chase is outside the building to let the user select the position of the ball before the robot start working.