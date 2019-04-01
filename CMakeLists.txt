cmake_minimum_required(VERSION 3.7)
project(mecatro_P17)

set(CMAKE_CXX_STANDARD 14)

# Add libraries to the list
# - libdxl_sbc_cpp.so for dynamixelSDK (after installation, the binary should be in /usr/local/lib)
# - wiringPi for regular wiringPi utilities
# - wiringPiDev for drivers such as lcd.h
set(PROJECT_LINK_LIBS libdxl_sbc_cpp.so wiringPi wiringPiDev)
link_directories(/usr/local/lib) # location of dynamixelSDK binary
include_directories(libs/dxl_sdk_cpp_source/include/dynamixel_sdk) # location of dynamixelSDK headers

# Do not forget to add source files to this list
set(SOURCE_FILES
        src/main.cpp
        src/components/AX12.cpp
        src/components/Kangaroo.cpp
        src/components/LCD.cpp
        src/components/serialport.cpp
        src/components/US_sensor.cpp
        src/robot/Robot.cpp src/robot/Robot.h
        )

# Link everything to the project
add_executable(mecatro_P17 ${SOURCE_FILES})
target_link_libraries(mecatro_P17 ${PROJECT_LINK_LIBS})
