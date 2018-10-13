cmake_minimum_required(VERSION 3.0)

project("FatFS" LANGUAGES C)

if ("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
	set (FatFS_WITH_CLANG TRUE)
endif ("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")

if (CMAKE_COMPILER_IS_GNUCC)
	set (FatFS_WITH_GCC TRUE)
endif (CMAKE_COMPILER_IS_GNUCC)

if (FatFS_WITH_GCC OR FatFS_WITH_CLANG)
	set (FatFS_CFLAGS -Wall -Wextra -Werror -Wfatal-errors)
endif (FatFS_WITH_GCC OR FatFS_WITH_CLANG)

if (FatFS_WITH_CLANG)
	list (APPEND FatFS_CFLAGS -Wdocumentation)
endif (FatFS_WITH_CLANG)

add_subdirectory("lib")
add_subdirectory("util")
