#ifndef MOVE_ROBOT_h
#define MOVE_ROBOT_h

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <mover/Direction.h>
#include <fstream>

class RobotController {
    public:
    ros::NodeHandle nh;
    ros::Publisher pub;
    ros::Subscriber sub;
    geometry_msgs::Twist twist;
    ros::Time startTime;
    ros::Time endTime;

    int tempCounter = -1;
    bool commandsComplete = false;
    bool goalReached = false;
    
    RobotController() {
        pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
        sub = nh.subscribe("/direction_cmd", 10, &RobotController::directionCallback, this);
        initializeFile();
    }

    void initializeFile() {
        std::ofstream outputFile;
        outputFile.open("commands_status.txt");
        if (outputFile.is_open()) {
            outputFile << std::boolalpha << false << "\n";
            outputFile << std::boolalpha << false << "\n";
            outputFile.close();
            ROS_INFO_STREAM("Command status initialized to false in commands_status.txt");
        } else {
            ROS_ERROR_STREAM("Unable to open commands_status.txt for writing");
        }
    }

    void directionCallback(const mover::Direction::ConstPtr& msg) {
        std::vector<std::string> directions = msg->directions;
        int counter = msg->counter;

        ROS_INFO_STREAM("Counter: " << counter);

        if(counter > tempCounter) {
            // Initialize commandsComplete to false when new directions come in
            startTime = ros::Time::now();
            commandsComplete = false;
            goalReached = false;

            for(auto &direction : directions) {
                ROS_INFO_STREAM("Received Direction: " << direction);
                if (direction == "Forward")
                    MoveForward();
                else if (direction == "Right")
                    TurnRight();
                else if (direction == "Left")
                    TurnLeft();
                else
                    ROS_WARN("Received unknown direction command");
            }

            if (!goalReached && directions.size() <= 1) {
                goalReached = true;
                endTime = ros::Time::now();
                ros::Duration elapsedTime = endTime - startTime;
                ROS_INFO_STREAM("Time taken to reach goal: " << elapsedTime.toSec() << " seconds");
            }

            commandsComplete = true;


            
            std::ofstream outputFile;
            outputFile.open("commands_status.txt", std::ios::out);
            if (outputFile.is_open()) {
                outputFile << std::boolalpha << commandsComplete << "\n";
                outputFile << std::boolalpha << goalReached << "\n";
                outputFile.close();
                ROS_INFO_STREAM("Command status set to false for new directions in commands_status.txt");
            } else {
                ROS_ERROR_STREAM("Unable to open commands_status.txt for writing");
            }

            ros::Duration(10.0).sleep();

            tempCounter = counter;
            // commandsComplete = false;

        } else {
            ROS_INFO_STREAM("Message counter has not been incremented, no new command.");
        }
    }
    





            // if (directions.size() <= 2) {
            //     goalReached = true;
            // }

            // commandsComplete = true;

            // if(commandsComplete || goalReached) {
            //     outputFile.open("commands_status.txt", std::ios::out);
            //     if (outputFile.is_open()) {
            //         outputFile << std::boolalpha << commandsComplete << "\n";
            //         outputFile << std::boolalpha << goalReached << "\n";
            //         outputFile.close();
            //         ROS_INFO_STREAM("Command status written to commands_status.txt");
            //     } else {
            //         ROS_ERROR_STREAM("Unable to open commands_status.txt for writing");
            //     }
            // }

            // ros::Duration(5.0).sleep();

            // tempCounter = counter;
            // commandsComplete = false;


    void MoveForward() {
        ros::Rate rate(10);  // 10 Hz

        twist.linear.x = 0.1;  // Move forward at 0.1 m/s
        for (int i = 0; i < 100; ++i) {  // 10*0.1 second = 1 second
            pub.publish(twist);
            rate.sleep();
        }

        // Decelerate over 2 seconds
        for (int i = 0; i < 10; ++i) {
            twist.linear.x -= 0.0125;  // Decrement by 0.0125 each cycle
            twist.angular.z -=0.001;
            pub.publish(twist);
            rate.sleep();
        }     

        StopMoving(20);
    }

    void TurnRight() {
        ros::Rate rate(10);  // 10 Hz

        twist.angular.z = -0.25;
        for (int i = 0; i < 60; ++i) {  // 10*0.1 second = 1 second
            pub.publish(twist);
            rate.sleep();
        }

        StopMoving(20);

        MoveForward();

        StopMoving(20);
    }

    void TurnLeft() {
        ros::Rate rate(10);  // 10 Hz

        twist.angular.z = 0.25;
        for (int i = 0; i < 60; ++i) {  // 10*0.1 second = 1 second
            pub.publish(twist);
            rate.sleep();
        }

        StopMoving(20);

        MoveForward();

        StopMoving(20);
    }

    void TestForward() {
        ros::Rate rate(10);  // 10 Hz

        twist.linear.x = 0.1;  // Move forward at 0.1 m/s
        for (int i = 0; i < 100; ++i) {  // 10*0.1 second = 1 second
            pub.publish(twist);
            rate.sleep();
        }

        // Decelerate over 2 seconds
        for (int i = 0; i < 10; ++i) {
            twist.linear.x -= 0.0125;  // Decrement by 0.0125 each cycle
            twist.angular.z -= 0.001;
            pub.publish(twist);
            rate.sleep();
        }     

        StopMoving(20);
    }

    void MoveForwardDecelerate() {
        ros::Rate rate(10);  // 10 Hz

        twist.linear.x = 0.25;  // Move forward at 0.1 m/s
        twist.angular.z = 0.1;
        for (int i = 0; i < 38; ++i) {  // 10*0.1 second = 4.2 seconds
            pub.publish(twist);
            rate.sleep();
        }

        // Decelerate over 2 seconds
        for (int i = 0; i < 10; ++i) {
            twist.linear.x -= 0.0125;  // Decrement by 0.0125 each cycle
            twist.angular.z -= 0.0125;
            pub.publish(twist);
            rate.sleep();
        }       

        StopMoving(20);
    }

    void StopMoving(int stop_time) {
        ros::Rate rate(10);  // 10 Hz

        // Stop the robot by sending a command with all fields set to 0
        twist.linear.x = 0.0;
        twist.angular.z = 0.0;
        for (int i = 0; i < stop_time; ++i) {  // send the stop command for stop_time/10 seconds
            pub.publish(twist);
            rate.sleep();
        }
    }

};

#endif