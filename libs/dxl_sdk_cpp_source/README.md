### Dynamixel SDK source
This folder contains DynamixelSDK source code (available at https://github.com/ROBOTIS-GIT/DynamixelSDK/).

For a new configuration, here is what you need to do on the raspberry pi
* Sync the folders (for example you can map the project to `/tmp/your_name`)
* Install cmake : `sudo apt install cmake`
* Build the library : 
```
cd PATH/TO/PROJECT/dxl_sdk_cpp_source/build
sudo make install
```

The library is now built at 2 locations : 
`/tmp/alex/dxl_sdk_cpp_source/build/linux_sbc` and `/usr/local/lib`.

* You now have to configure the `CMakeLists.txt` file so that dynamixel_sdk library is located

```
set(PROJECT_LINK_LIBS libdxl_sbc_cpp.so)
link_directories(/usr/local/lib)
include_directories(dxl_sdk_cpp_source/include/dynamixel_sdk)

add_executable(test_clion ax12_test_simple.cpp ax12_test_simple.h)
target_link_libraries(test_clion ${PROJECT_LINK_LIBS})
```