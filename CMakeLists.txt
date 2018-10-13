cmake_minimum_required(VERSION 3.0)

project("libfat" LANGUAGES C)

if ("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
	set (libfat_WITH_CLANG TRUE)
endif ("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")

if (CMAKE_COMPILER_IS_GNUCC)
	set (libfat_WITH_GCC TRUE)
endif (CMAKE_COMPILER_IS_GNUCC)

if (libfat_WITH_GCC OR libfat_WITH_CLANG)
	set (libfat_CFLAGS -Wall -Wextra -Werror -Wfatal-errors)
endif (libfat_WITH_GCC OR libfat_WITH_CLANG)

if (libfat_WITH_CLANG)
	list (APPEND libfat_CFLAGS -Wdocumentation)
endif (libfat_WITH_CLANG)

add_subdirectory("lib")
add_subdirectory("util")
