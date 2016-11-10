cmake_minimum_required(VERSION 3.6)
project(SnakeTerm)

find_package(Curses REQUIRED)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(SOURCE_FILES src/main.c src/snake.h src/snake.c src/game.c src/game.h)
add_executable(SnakeTerm ${SOURCE_FILES})

target_link_libraries(SnakeTerm ${CURSES_LIBRARIES})