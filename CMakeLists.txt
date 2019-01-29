cmake_minimum_required(VERSION 3.7)
project(test_clion)

set(CMAKE_CXX_STANDARD 14)

# Link libraries to the project (dynamixelSDK and wiringPi)
set(PROJECT_LINK_LIBS libdxl_sbc_cpp.so wiringPi)
link_directories(/usr/local/lib) # location of dynamixelSDK binary
include_directories(libs/dxl_sdk_cpp_source/include/dynamixel_sdk) # location of dynamixelSDK headers

add_executable(test_clion src/main.cpp)
target_link_libraries(test_clion ${PROJECT_LINK_LIBS})
