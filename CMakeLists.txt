cmake_minimum_required(VERSION 4.0.0-rc4 FATAL_ERROR)

project(BFL)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(BFL src/BFL.cpp)

#for build use it from build dir

#cmake ..
#cmake --build . --config Release

#or if you are using Windows you can run build.bat