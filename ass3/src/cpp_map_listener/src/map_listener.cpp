#include <ros/ros.h>
#include <nav_msgs/OccupancyGrid.h>
#include <fstream>
#include <tf/transform_listener.h>

tf::TransformListener* listener = nullptr;

void mapCallback(const nav_msgs::OccupancyGrid::ConstPtr& msg)
{
    ROS_INFO("Received map data");

    // Get the map dimensions
    int width = msg->info.width;
    int height = msg->info.height;

    // int downsample = 5;

    // int newWidth = width / downsample;
    // int newHeight = height / downsample;

    // Convert the map data to a 2D array
    std::vector<std::vector<int>> mapArray(height, std::vector<int>(width, 0));

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            int index = x + y * width;
            int data = msg->data[index];
            if (data == -1) {
                mapArray[y][x] = 0; //Unknown
                // mapArray[y / downsample][x / downsample] = 0;
            }
            else if (data == 0) {
                mapArray[y][x] = 1; //Free
                // mapArray[y / downsample][x / downsample] = 1;
            }
            else if (data == 100) {
                mapArray[y][x] = 2; //Occupied
                // mapArray[y / downsample][x / downsample] = 2;
            }
            // mapArray[y][x] = msg->data[index];
        }
    }
    // Get Robot's position
    tf::StampedTransform transform;
    // double yaw_degrees;
    int cardinal_direction;
    try {
        // Wait for transform to become available
        listener->waitForTransform("/map", "/base_link", ros::Time(0), ros::Duration(10.0));

        // Get the transform
        listener->lookupTransform("/map", "/base_link", ros::Time(0), transform);

        // Convert to map coordinates
        int robotX = (transform.getOrigin().x() - msg->info.origin.position.x) / msg->info.resolution;
        int robotY = (transform.getOrigin().y() - msg->info.origin.position.y) / msg->info.resolution;

        if (robotX >= 0 && robotX < width && robotY >= 0 && robotY < height) {
            mapArray[robotY][robotX] = 3;
        }

        //extract the yaw angle and convert it to degrees 
        double yaw = tf::getYaw(transform.getRotation());

        double yaw_degrees = yaw * 180.0 / M_PI;

        //Normalize yaw_degrees to [0, 360]
        while (yaw_degrees < 0.0) yaw_degrees += 360.0;
        while (yaw_degrees >= 360.0) yaw_degrees -= 360.0;

        //Map degree to nearest cardinal direction
        if ((yaw_degrees >= 0.0 && yaw_degrees < 45.0) || (yaw_degrees >= 315.0 && yaw_degrees < 360.0)){
            cardinal_direction = 90; //NORTH
        }
        else if (yaw_degrees >= 45.0 && yaw_degrees < 135.0){
            cardinal_direction = 180; //East
        }
        else if (yaw_degrees >= 135.0 && yaw_degrees < 225.0){
            cardinal_direction = 270; //South
        }
        else if (yaw_degrees >= 225.0 && yaw_degrees < 315.0){
            cardinal_direction = 0; //West
        }

    } catch (tf::TransformException& ex) {
        ROS_ERROR("%s", ex.what());
    }

    // Save the map array to a text file
    std::ofstream file("Map.txt");
    if (file.is_open())
    {
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                file << mapArray[y][x] << " ";
            }
            file << std::endl;
        }

        //Write the initial Yaw
        file << "Initial yaw (degrees): " << cardinal_direction << std::endl;

        file.close();
        ROS_INFO("Map saved to Map.txt");
    }
    else
    {
        ROS_ERROR("Unable to open file");
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "map_listener");
    ros::NodeHandle n;

    listener = new tf::TransformListener();

    ros::Subscriber sub = n.subscribe("/map", 1000, mapCallback);

    ros::spin();

    delete listener;

    return 0;
}