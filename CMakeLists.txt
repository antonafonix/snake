cmake_minimum_required(VERSION 3.10)
project(SnakeGame C)

set(CMAKE_C_STANDARD 99)

find_package(Curses REQUIRED)

add_executable(snake src/main.c src/menu.c src/game.c)

target_include_directories(snake PRIVATE ${CURSES_INCLUDE_DIRS})
target_link_libraries(snake PRIVATE ${CURSES_LIBRARIES})