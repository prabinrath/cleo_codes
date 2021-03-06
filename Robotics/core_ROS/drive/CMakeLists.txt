cmake_minimum_required(VERSION 2.8.3)
project(drive)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs genmsg cv_bridge dynamic_reconfigure)

find_package(Qt4 REQUIRED COMPONENTS QtCore QtGui)
include(${QT_USE_FILE})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

## Find files
file(GLOB QT_FORMS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ui/*.ui)
set(QT_MOC include/mainwindow.h)
SET(QT_SOURCES src/mainwindow.cpp)

## Setup QT
QT4_WRAP_UI(QT_FORMS_HPP ${QT_FORMS})
QT4_WRAP_CPP(QT_MOC_HPP ${QT_MOC}) 

## Declare ROS messages and services
add_message_files(FILES drivedata.msg)

##configuration files
generate_dynamic_reconfigure_options(cfg/default.cfg)

##add_service_files(FILES AddTwoInts.srv)

## Generate added messages and services
generate_messages(DEPENDENCIES std_msgs)

## Declare a catkin package
catkin_package(CATKIN_DEPENDS message_runtime dynamic_reconfigure)


## Build nodes
include_directories(include ${catkin_INCLUDE_DIRS}${QT_INCLUDE_DIRS})

add_executable(drive_pub src/drive_pub.cpp)
target_link_libraries(drive_pub ${catkin_LIBRARIES}${OpenCV_LIBS})
add_dependencies(drive_pub drive_generate_messages_cpp)

add_executable(checkdata src/checkdata.cpp)
target_link_libraries(checkdata ${catkin_LIBRARIES})
add_dependencies(checkdata drive_generate_messages_cpp)

add_library(appoLib ${QT_SOURCES} ${QT_FORMS_HPP} ${QT_MOC_HPP})
target_link_libraries(appoLib ${QT_LIBRARIES} ${catkin_LIBRARIES})

add_executable(open_exe src/main.cpp)
target_link_libraries(open_exe appoLib)
add_dependencies(checkdata drive_generate_messages_cpp)
