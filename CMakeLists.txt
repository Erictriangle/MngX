cmake_minimum_required(VERSION 2.8.12)
enable_testing()

project(MngX)


set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 17)


file(GLOB SOURCES "src/*.cpp")
file(GLOB UNIT_TEST "Testing/*.cpp")


set(CMAKE_CXX_FLAGS_RELEASE "-Wall -Wextra -Werror -O2")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra  -O0")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)

elseif(CMAKE_BUILD_TYPE MATCHES Release)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/")

elseif(CMAKE_BUILD_TYPE MATCHES Debug)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "Debug/")
endif()


#TODO - change boost prefix
set(BOOST_ROOT "/home/eric/d/Library/boost")
#set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREAD ON)
set(Boost_USE_STATIC_RUNETIME OFF)

find_package(Boost 1.67.0 COMPONENTS system filesystem unit_test_framework log REQUIRED)


if(Boost_FOUND)
  ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK) 
  ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)

  include_directories(include)
  include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
  
	add_executable(${PROJECT_NAME} "main.cpp" ${SOURCES})
  target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

  if(CMAKE_BUILD_TYPE MATCHES Debug)
    foreach( unitTest ${UNIT_TEST} )
      get_filename_component(testName ${unitTest} NAME_WE)
      add_executable(${testName} ${unitTest} ${SOURCES})
      target_link_libraries(${testName} ${Boost_LIBRARIES})
    endforeach( unitTest )
  endif() #CMAKE_BUILD_TYPE Debug
endif() #Boost_FOUND
