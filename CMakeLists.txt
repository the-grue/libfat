cmake_minimum_required(VERSION 3.0)

project("ff" LANGUAGES C)

add_library("ff"
	"source/diskio.c"
	"source/ff.c"
	"source/ffsystem.c"
	"source/ffunicode.c")

add_executable("ffutil" "util/main.c")

target_link_libraries("ffutil" "ff")
