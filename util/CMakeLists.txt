cmake_minimum_required(VERSION 3.0)

add_executable("ffutil"
	"arg-iterator.h"
	"arg-iterator.c"
	"fdisk.h"
	"fdisk.c"
	"main.c"
	"mkfs.h"
	"mkfs.c"
	"mkdir.h"
	"mkdir.c"
	"time.c")

target_link_libraries("ffutil" "fatfs")

set_target_properties("ffutil"
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")

if (DEFINED FatFS_CFLAGS)
	target_compile_options("ffutil" PRIVATE ${FatFS_CFLAGS})
endif (DEFINED FatFS_CFLAGS)
