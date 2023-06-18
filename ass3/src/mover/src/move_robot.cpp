#include "move_robot.h"
#include <string>
int main(int argc, char** argv) {
    // Initialize ROS
    ros::init(argc, argv, "move_robot");

    std::string Direction;

    RobotController robot;

    ros::spin();
    
    return 0;
}