cmake_minimum_required(VERSION 3.0)

add_library("fatfs"
	"disk.c"
	"fatfs.c"
	"ffsystem.c"
	"ffunicode.c")

target_include_directories("fatfs"
	PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
	       $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>)

if (DEFINED FatFS_CFLAGS)
	target_compile_options("fatfs" PRIVATE ${FatFS_CFLAGS})
endif (DEFINED FatFS_CFLAGS)
