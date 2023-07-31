cmake_minimum_required(VERSION 3.26)
project(space_shooter)

set(CMAKE_CXX_STANDARD 14)

link_directories(includes/freeglut/lib/x64)

link_directories(includes/irrKlang/lib/Winx64-visualStudio)


add_executable(space_shooter main.cpp
        classes/star.cpp)

target_link_libraries(space_shooter PRIVATE irrKlang)
target_link_libraries(space_shooter PRIVATE freeglut)