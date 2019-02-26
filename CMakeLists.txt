cmake_minimum_required(VERSION 3.7)
project(test_clion)

set(CMAKE_CXX_STANDARD 14)

# Link libraries to the project (dynamixelSDK and wiringPi)
set(PROJECT_LINK_LIBS libdxl_sbc_cpp.so wiringPi)
link_directories(/usr/local/lib) # location of dynamixelSDK binary
include_directories(libs/dxl_sdk_cpp_source/include/dynamixel_sdk) # location of dynamixelSDK headers

# Do not forget to add source files to this list
set(SOURCE_FILES src/main.cpp src/AX12.cpp src/kangaroo.cpp src/LCD.cpp src/serialport.cpp )
add_executable(test_clion ${SOURCE_FILES})
target_link_libraries(test_clion ${PROJECT_LINK_LIBS})
