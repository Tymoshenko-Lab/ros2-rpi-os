cmake_minimum_required(VERSION 3.10)
project(counter_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(std_srvs REQUIRED)

add_executable(counter_publisher src/counter_publisher.cpp)
target_link_libraries(counter_publisher PUBLIC
  rclcpp::rclcpp ${std_msgs_TARGETS} ${std_srvs_TARGETS})

add_executable(counter_subscriber src/counter_subscriber.cpp)
target_link_libraries(counter_subscriber PUBLIC
  rclcpp::rclcpp ${std_msgs_TARGETS})

add_executable(counter_control src/counter_control.cpp)
target_link_libraries(counter_control PUBLIC
  rclcpp::rclcpp ${std_srvs_TARGETS})

install(TARGETS counter_publisher counter_subscriber counter_control
  DESTINATION lib/${PROJECT_NAME})

ament_package()
