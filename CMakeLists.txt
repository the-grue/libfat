cmake_minimum_required(VERSION 3.0)

project("FatFS" LANGUAGES C)

if (CMAKE_COMPILER_IS_GNUCC)
	set (FatFS_CFLAGS -Wall -Wextra -Werror -Wfatal-errors)
endif (CMAKE_COMPILER_IS_GNUCC)

add_subdirectory("lib")
add_subdirectory("util")
