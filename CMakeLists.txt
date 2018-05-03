cmake_minimum_required(VERSION 3.5.1 FATAL_ERROR)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

project (collision_p)

set (CMAKE_CXX_STANDARD 11)

add_executable(collision main.cpp Circle.cpp Physics.cpp constants.cpp)

#armadillo library
find_package(Armadillo REQUIRED)
include_directories(${ARMADILLO_INCLUDE_DIRS})

#include the necessary libraries
find_package(SFML 2 REQUIRED system window graphics network audio)
find_package(TGUI 0.7 REQUIRED)

if(NOT SFML_FOUND)
    message(FATAL_ERROR "Could not find SFML")
endif()

if(NOT TGUI_FOUND)
    message(FATAL_ERROR "Could not find TGUI")
endif()

include_directories(${SFML_INCLUDE_DIR})

target_link_libraries(collision ${SFML_LIBRARIES} ${TGUI_LIBRARY} ${ARMADILLO_LIBRARIES})
