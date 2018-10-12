cmake_minimum_required(VERSION 3.0)

project("FatFS" LANGUAGES C)

if (CMAKE_COMPILER_IS_GNUCC)
	set (FatFS_CFLAGS -Wall -Wextra -Werror -Wfatal-errors)
endif (CMAKE_COMPILER_IS_GNUCC)

add_library("fatfs"
	"source/diskio.c"
	"source/fatfs.c"
	"source/ffsystem.c"
	"source/ffunicode.c")

target_include_directories("fatfs"
	PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
	       $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>)

target_compile_options("fatfs" PRIVATE ${FatFS_CFLAGS})


add_executable("ffutil" "util/main.c")

target_link_libraries("ffutil" "fatfs")

target_compile_options("ffutil" PRIVATE ${FatFS_CFLAGS})
