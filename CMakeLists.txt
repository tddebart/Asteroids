cmake_minimum_required(VERSION 3.25)
project(shoot_up_2d)

set(CMAKE_CXX_STANDARD 23)

add_executable(shoot_up_2d main.cpp)

find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(shoot_up_2d
        PRIVATE
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
        )
