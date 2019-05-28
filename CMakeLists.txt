cmake_minimum_required(VERSION 3.7)
project(mecatro_P17)

set(CMAKE_CXX_STANDARD 14)

# Add libraries to the list
# - libdxl_sbc_cpp.so for dynamixelSDK (after installation, the binary should be in /usr/local/lib)
# - libbehaviortree_cpp_v3.so for behaviortree C++ library
# - wiringPi for regular wiringPi utilities
# - wiringPiDev for drivers such as lcd.h
set(
        PROJECT_LINK_LIBS
        libdxl_sbc_cpp.so
        libbehaviortree_cpp_v3.so
        wiringPi
        wiringPiDev

        # for loguru
        pthread
        dl
)
link_directories(/usr/local/lib) # location of the binaries (.so)
include_directories(
        libs/dxl_sdk_cpp_source/include/dynamixel_sdk   # location of dynamixelSDK headers
        libs/BehaviorTree.CPP-master/include/           # location of BehaviorTree headers
        libs/loguru                                     # lightweight logging library
)

# Do not forget to add source files to this list
set(SOURCE_FILES
        libs/loguru/loguru.cpp

        src/main_small_robot.cpp

        src/components/AX12.cpp
        src/components/Kangaroo.cpp
        src/components/LCD.cpp
        src/components/UltrasonicSensor.cpp
        src/components/SerialPort.cpp
        src/components/Jack.cpp
        src/components/RelayModule.cpp

        src/strategy/Nodes.cpp
        src/components/Encoder.cpp)

# Link everything to the project
add_executable(mecatro_P17 ${SOURCE_FILES})
target_link_libraries(mecatro_P17 ${PROJECT_LINK_LIBS})
