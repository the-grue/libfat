cmake_minimum_required(VERSION 3.0)

add_library("fat"
	"decode.h"
	"decode.c"
	"disk.c"
	"encode.h"
	"encode.c"
	"string.h"
	"string.c"
	"fatfs.c"
	"ffsystem.c"
	"ffunicode.c")

target_include_directories("fat"
	PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
	       $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>)

if (DEFINED libfat_CFLAGS)
	target_compile_options("fat" PRIVATE ${libfat_CFLAGS})
endif (DEFINED libfat_CFLAGS)
