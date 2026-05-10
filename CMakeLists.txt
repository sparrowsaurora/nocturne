cmake_minimum_required(VERSION 3.10)

project(nocturne)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find ncurses
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(nocturne
    src/main.cpp
    src/song.cpp
    src/playlist.cpp
    src/storage.cpp
)

# add include dir
target_include_directories(nocturne PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Link ncurses
target_link_libraries(nocturne ${CURSES_LIBRARIES})