cmake_minimum_required(VERSION 3.22)
project(SDRDecoder)

set(CMAKE_CXX_STANDARD 14)

include_directories(libs includes src/data)

add_executable(SDRDecoder src/main.cpp src/main.h src/USBControl.cpp src/USBControl.h)

target_link_libraries(SDRDecoder ${PROJECT_SOURCE_DIR}/libs/libusb-1.0.a)