cmake_minimum_required(VERSION 2.8.3)
project(canny_edge_my_face)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
        std_msgs
        message_generation
        roscpp
        cv_bridge
        image_transport
        sensor_msgs	
        #controller_manager
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES canny_edge_my_face
#  CATKIN_DEPENDS other_catkin_pkg
#  DEPENDS system_lib
)

include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(canny_edge_my_face src/canny_filter.cpp)
target_link_libraries(canny_edge_my_face ${catkin_LIBRARIES})
add_dependencies(canny_edge_my_face canny_edge_my_face_generate_messages_cpp)

