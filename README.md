libfat
======

[![Build Status](https://travis-ci.org/ReturnInfinity/libfat.svg?branch=master)](https://travis-ci.org/ReturnInfinity/libfat)

This is a FAT file system library written in C.

It originated from [here](http://elm-chan.org/fsw/ff/00index_e.html), by ChaN.

Here it is being refactored for the following:

 - Removing global states from the library
 - Improving maintainability (smaller files, smaller functions, better variable names)
 - Improving documentation
 - Easing the integration of the library in operating system projects.
 - Easing the integration of the library in hosted environments.

Building
========

Currently, CMake is used to build the project.

On Debian systems, you can install it like this:

```
sudo apt install cmake
```

On Windows and macOS, there are downloads available from [their website](https://cmake.org/download).

Once it's installed, you can build the project like this:

```
mkdir build
cd build
cmake ..
cmake --build .
```

When the dust settles on the refactoring work, more build systems (such as GNU Make) will be added.

Credits
=======

A thanks goes out to ChaN, the library's original author.

In addition, a thanks goes out to [fatcat](https://github.com/Gregwar/fatcat).
The fatcat project is invaluable for debugging this library and FAT file systems in general.

License
=======

The original library is under a BSD-like license.

As per the documentation of the original library, it is now licensed under GPLv3.
