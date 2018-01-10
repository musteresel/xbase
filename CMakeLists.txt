cmake_minimum_required(VERSION 3.9.5)
project(xbase64)

set(XBASE_PACKAGE "xbase64")
set(XBASE_VERSION "3.3.2")
set(XBASE_BUGREPO "wolf+xbase@wolfsden.cz")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_BUILD_WITH_INSTALL_RPATH ON)

if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -ggdb")
endif()

add_subdirectory(3rd_party/googletest)

add_subdirectory(xbase64)
add_subdirectory(examples)
add_subdirectory(bin)
add_subdirectory(test)

add_subdirectory(docs)
