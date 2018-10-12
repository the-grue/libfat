FatFS
=====

This is a FAT file system library written in C.

It originated from [here](http://elm-chan.org/fsw/ff/00index_e.html), originated by ChaN.

Here it is being refactored for the following:

 - Removing global states from the library
 - Improving maintainability (smaller files, smaller functions, better variable names)
 - Improving documentation
 - Easing the integration of the library in operating system projects.