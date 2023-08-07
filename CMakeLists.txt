cmake_minimum_required(VERSION 3.26)
project(space_shooter)

set(CMAKE_CXX_STANDARD 14)

link_directories(includes/freeglut/lib/x64)

link_directories(includes/irrKlang/lib/Winx64-visualStudio)


add_executable(space_shooter main.cpp
        classes/GameObject.cpp
        classes/Star.cpp
        classes/MyShip.cpp
        classes/Bullet.cpp
        classes/Enemy.cpp
        classes/EnemyV2.cpp
        classes/Life.cpp
        classes/Points.cpp
)

target_link_libraries(space_shooter PRIVATE irrKlang)
target_link_libraries(space_shooter PRIVATE freeglut)
add_custom_command(TARGET space_shooter PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/includes/files/ ${CMAKE_BINARY_DIR}/)
