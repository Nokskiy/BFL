# BFL : Basic file library

![BFL](https://github.com/Nokskiy/BFL/blob/main/logo.jpg)

![License: MIT](https://img.shields.io/badge/license-MIT-blue.svg)

# About
#### Short description
__BFL__ is a library designed to simplify file system operations in C++. It provides a comprehensive set of functions for handling various file system tasks.📁📁📁

  - The library offers functions for filesystem manipulation using C++'s file system capabilities. 📁📁📁  

  - Functions are in the BFL namespace. 🌌🌌🌌  

  - Thanks to the straightforward use of the standard file system and the code being modularized into multiple functions, we maintain optimal performance. 🚀🚀🚀  


#### About language
The library utilizes the C++17 language standard.

# How to use
- Install the desired release (preferably the latest one).  

- Drag the `.hpp` file into your project directory.  

- Where you need to use the library, add `#include "BFL.hpp"` at the beginning.  

- It is recommended to add `using namespace BFL;` at the beginning.  

You're all set!  

# Issues
If you find any bugs, want to contribute by adding new features, or optimize something, feel free to open an issue.


# Dockumetation
- `pathToString(end path)` - returns the path converted to a string.
- `normalPath(end path)` - returns the normalized path.
- `isFile(file/directory path)` - returns true or false depending on whether the destination path is a file.
- `fileName(end path)` - returns name of end path.
- `connectPaths(path1, path2)` - returns connected paths.
- `everythingInDirectory(directory ,throw error = true/false)` - returns everything in a directory.
- `everythingInDirectoryRecursive(directory, throw error = true/false)` - returns all files and folders in a directory along with the contents of those folders.
- `itemSize(path, throw error = true/false)` - returns a directory/file size.
- `create(path,file/directory name)` - create a file/directory.
- `rem(path, printDelFile = false/true, throwError = true/false)` - remove a file/directory.
- `ren(file/directory path, new name, throwError = true/false)` - rename a file/directory.
- `GetDrives()` - returns a disks list.
- `curPath()` - returns a path to performing file.
- `clearFile(file path)` - clear a file.
- `writeToFile(filePath, text, nLine = true/false)` - write text to a file.
- `readFile(file path)` - read a text of file.
- `find(root path,target)` - returns a full path.
# Contributing
I would be delighted if you would like to contribute to the development of the library and submit your changes.
