cmake_minimum_required(VERSION 3.5.0)
project(matplotpluspluscanvas VERSION 0.1.0 LANGUAGES C CXX)

add_executable(matplotpluspluscanvas main.cpp)

add_subdirectory(vendor/matplotplusplus)
target_link_libraries(matplotpluspluscanvas PUBLIC matplot)
