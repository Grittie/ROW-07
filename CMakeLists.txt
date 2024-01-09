cmake_minimum_required(VERSION 3.0)
project(main)

add_executable(${PROJECT_NAME} src/main.cpp src/waterpump/waterpump.cpp src/servo/servo.cpp src/motorController/wheels.cpp src/mqtt/sub.cpp)

# Link the WiringPi library
target_link_libraries(main wiringPi)
target_link_libraries(main mosquitto)
target_link_libraries(main pthread)
