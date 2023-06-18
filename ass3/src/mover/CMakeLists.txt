cmake_minimum_required(VERSION 3.0.2)
project(mover)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  geometry_msgs
  message_generation
  message_runtime
)

add_message_files(
  FILES
  Direction.msg
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS roscpp std_msgs geometry_msgs message_runtime
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(move_robot src/move_robot.cpp)

target_link_libraries(move_robot ${catkin_LIBRARIES})