cmake_minimum_required(VERSION 3.5)
project(Panorama)

set(CMAKE_CXX_STANDARD 14)

add_executable(Panorama main.cpp panorama_check.cpp panorama_check.h original_pano.cpp original_pano.h)
find_package(OpenCV REQUIRED)

target_link_libraries(Panorama ${OpenCV_LIBS})