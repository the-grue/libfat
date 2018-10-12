cmake_minimum_required(VERSION 3.0)

project("ff" LANGUAGES C)

if (CMAKE_COMPILER_IS_GNUCC)
	set (FatFS_CFLAGS -Wall -Wextra -Werror -Wfatal-errors)
endif (CMAKE_COMPILER_IS_GNUCC)

add_library("ff"
	"source/diskio.c"
	"source/ff.c"
	"source/ffsystem.c"
	"source/ffunicode.c")

target_compile_options("ff" PRIVATE ${FatFS_CFLAGS})

add_executable("ffutil" "util/main.c")

target_link_libraries("ffutil" "ff")

target_compile_options("ffutil" PRIVATE ${FatFS_CFLAGS})
