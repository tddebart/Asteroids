cmake_minimum_required(VERSION 3.25)
project(shoot_up_2d)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 23)

add_executable(shoot_up_2d main.cpp Entities/Entity.cpp Draw.cpp Entities/Projectile.cpp Entities/OffScreenEntity.cpp)

find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(shoot_up_2d
        PRIVATE
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
        )

find_package(SDL2_image CONFIG REQUIRED)
target_link_libraries(shoot_up_2d PRIVATE $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>)
