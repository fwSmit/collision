cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
set (CMAKE_CXX_STANDARD 14)
# assuming gcc
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra")

project (collision_project CXX)

#file globing
file(GLOB_RECURSE sources src/*.cpp src/*.h)
file(GLOB_RECURSE data resources/*)

add_executable(collision ${sources} ${data})

#copy resources to build directory
file(COPY ${data} DESTINATION resources)

#armadillo library
find_package(Armadillo REQUIRED)

#include the necessary libraries
find_package(SFML 2 REQUIRED system window graphics)
find_package(TGUI REQUIRED)

if(NOT SFML_FOUND)
	message(FATAL_ERROR "Could not find SFML")
endif()

if(NOT TGUI_FOUND)
	message(FATAL_ERROR "Could not find TGUI")
endif()

if(NOT ARMADILLO_FOUND)
	message(FATAL_ERROR "Could not find armadillo")
endif()

include_directories(${SFML_INCLUDE_DIR})
include_directories(${TGUI_INCLUDE_DIR})
include_directories(${ARMADILLO_INCLUDE_DIRS})

target_link_libraries(collision ${SFML_LIBRARIES} ${TGUI_LIBRARY} ${ARMADILLO_LIBRARIES})
# cmake_minimum_required(VERSION 3.5.1 FATAL_ERROR)
# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
# set (CMAKE_CXX_STANDARD 14)

# project (collision_p)

# option(IS_LIBRARY "Should collision be compiled as library?")

# set (collision_src Circle.cpp Physics.cpp constants.cpp)

# if(IS_LIBRARY)
	# message("setting up as library")
	# add_library(collision SHARED ${collision_src})
# else()
	# message("setting up as executable")
	# add_executable(collision main.cpp ${collision_src})
# endif()

# #armadillo library
# find_package(Armadillo REQUIRED)
# include_directories(${ARMADILLO_INCLUDE_DIRS})

# #include the necessary libraries
# find_package(SFML 2 REQUIRED system window graphics)
# find_package(TGUI REQUIRED)

# if(NOT SFML_FOUND)
    # message(FATAL_ERROR "Could not find SFML")
# endif()

# if(NOT TGUI_FOUND)
    # message(FATAL_ERROR "Could not find TGUI")
# endif()

# include_directories(${SFML_INCLUDE_DIR})

# target_link_libraries(collision ${SFML_LIBRARIES} ${TGUI_LIBRARY} ${ARMADILLO_LIBRARIES})
