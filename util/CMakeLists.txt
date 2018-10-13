cmake_minimum_required(VERSION 3.0)

add_executable("ffutil"
	"main.c"
	"time.c")

target_link_libraries("ffutil" "fatfs")

if (DEFINED FatFS_CFLAGS)
	target_compile_options("ffutil" PRIVATE ${FatFS_CFLAGS})
endif (DEFINED FatFS_CFLAGS)
