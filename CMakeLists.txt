cmake_minimum_required(VERSION 2.8)

project(VTK-TUTORIALS CXX)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})





add_executable(ImageData src/example_imagedata.cpp)
target_link_libraries(ImageData ${VTK_LIBRARIES})