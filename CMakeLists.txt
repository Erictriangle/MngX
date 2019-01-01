cmake_minimum_required(VERSION 2.8.12)
enable_testing()


project(MngX)


set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 17)


file(GLOB SOURCES "src/*.cpp")
file(GLOB UNIT_TEST "ut/*.cpp")
include_directories(include)


set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-Werror -O3")


if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/")
  
elseif(CMAKE_BUILD_TYPE MATCHES Release)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "Release/")
  
elseif(CMAKE_BUILD_TYPE MATCHES Debug)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "Debug/")
endif()


  
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREAD ON)
set(Boost_USE_STATIC_RUNETIME OFF)

find_package(Boost 1.67.0 COMPONENTS system filesystem unit_test_framework REQUIRED)
  

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(${PROJECT_NAME} "main.cpp" ${SOURCES})
    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})


    #UNIT_TEST
    add_executable(ut_control ${UNIT_TEST} ${SOURCES})
    target_link_libraries(ut_control ${Boost_LIBRARIES})
endif()

