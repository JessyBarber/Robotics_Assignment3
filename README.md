# Robotics_Assignment3
This repo holds the code for running and executing the tasks in assignment 3 for this subject. 

# Launching gazebo environment
roslaunch turtlebot3_gazebo turtlebot3_empty_world.launch

# Launching Rviz with gmapping
roslaunch turtlebot3_slam turtlebot3_slam.launch slam_methods:=gmapping

# Running mapper package 
rosrun cpp_map_listener_pkg cpp_map_listener_pkg_node

# Running mover package
rosrun mover move_robot
