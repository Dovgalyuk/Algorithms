# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.29

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2024.2.2\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2024.2.2\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Katya\CLionProjects\Lab2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Katya\CLionProjects\Lab2\cmake-build-debug

# Include any dependencies generated for this target.
include LibraryCPP/Tests/CMakeFiles/TestStackCPP.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include LibraryCPP/Tests/CMakeFiles/TestStackCPP.dir/compiler_depend.make

# Include the progress variables for this target.
include LibraryCPP/Tests/CMakeFiles/TestStackCPP.dir/progress.make

# Include the compile flags for this target's objects.
include LibraryCPP/Tests/CMakeFiles/TestStackCPP.dir/flags.make

LibraryCPP/Tests/CMakeFiles/TestStackCPP.dir/stack.cpp.obj: LibraryCPP/Tests/CMakeFiles/TestStackCPP.dir/flags.make
LibraryCPP/Tests/CMakeFiles/TestStackCPP.dir/stack.cpp.obj: LibraryCPP/Tests/CMakeFiles/TestStackCPP.dir/includes_CXX.rsp
LibraryCPP/Tests/CMakeFiles/TestStackCPP.dir/stack.cpp.obj: C:/Users/Katya/CLionProjects/Lab2/LibraryCPP/Tests/stack.cpp
LibraryCPP/Tests/CMakeFiles/TestStackCPP.dir/stack.cpp.obj: LibraryCPP/Tests/CMakeFiles/TestStackCPP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\Katya\CLionProjects\Lab2\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object LibraryCPP/Tests/CMakeFiles/TestStackCPP.dir/stack.cpp.obj"
	cd /d C:\Users\Katya\CLionProjects\Lab2\cmake-build-debug\LibraryCPP\Tests && C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT LibraryCPP/Tests/CMakeFiles/TestStackCPP.dir/stack.cpp.obj -MF CMakeFiles\TestStackCPP.dir\stack.cpp.obj.d -o CMakeFiles\TestStackCPP.dir\stack.cpp.obj -c C:\Users\Katya\CLionProjects\Lab2\LibraryCPP\Tests\stack.cpp

LibraryCPP/Tests/CMakeFiles/TestStackCPP.dir/stack.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/TestStackCPP.dir/stack.cpp.i"
	cd /d C:\Users\Katya\CLionProjects\Lab2\cmake-build-debug\LibraryCPP\Tests && C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Katya\CLionProjects\Lab2\LibraryCPP\Tests\stack.cpp > CMakeFiles\TestStackCPP.dir\stack.cpp.i

LibraryCPP/Tests/CMakeFiles/TestStackCPP.dir/stack.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/TestStackCPP.dir/stack.cpp.s"
	cd /d C:\Users\Katya\CLionProjects\Lab2\cmake-build-debug\LibraryCPP\Tests && C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Katya\CLionProjects\Lab2\LibraryCPP\Tests\stack.cpp -o CMakeFiles\TestStackCPP.dir\stack.cpp.s

# Object files for target TestStackCPP
TestStackCPP_OBJECTS = \
"CMakeFiles/TestStackCPP.dir/stack.cpp.obj"

# External object files for target TestStackCPP
TestStackCPP_EXTERNAL_OBJECTS =

LibraryCPP/Tests/TestStackCPP.exe: LibraryCPP/Tests/CMakeFiles/TestStackCPP.dir/stack.cpp.obj
LibraryCPP/Tests/TestStackCPP.exe: LibraryCPP/Tests/CMakeFiles/TestStackCPP.dir/build.make
LibraryCPP/Tests/TestStackCPP.exe: LibraryCPP/libLibraryCPP.a
LibraryCPP/Tests/TestStackCPP.exe: LibraryCPP/Tests/CMakeFiles/TestStackCPP.dir/linkLibs.rsp
LibraryCPP/Tests/TestStackCPP.exe: LibraryCPP/Tests/CMakeFiles/TestStackCPP.dir/objects1.rsp
LibraryCPP/Tests/TestStackCPP.exe: LibraryCPP/Tests/CMakeFiles/TestStackCPP.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\Katya\CLionProjects\Lab2\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable TestStackCPP.exe"
	cd /d C:\Users\Katya\CLionProjects\Lab2\cmake-build-debug\LibraryCPP\Tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\TestStackCPP.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
LibraryCPP/Tests/CMakeFiles/TestStackCPP.dir/build: LibraryCPP/Tests/TestStackCPP.exe
.PHONY : LibraryCPP/Tests/CMakeFiles/TestStackCPP.dir/build

LibraryCPP/Tests/CMakeFiles/TestStackCPP.dir/clean:
	cd /d C:\Users\Katya\CLionProjects\Lab2\cmake-build-debug\LibraryCPP\Tests && $(CMAKE_COMMAND) -P CMakeFiles\TestStackCPP.dir\cmake_clean.cmake
.PHONY : LibraryCPP/Tests/CMakeFiles/TestStackCPP.dir/clean

LibraryCPP/Tests/CMakeFiles/TestStackCPP.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Katya\CLionProjects\Lab2 C:\Users\Katya\CLionProjects\Lab2\LibraryCPP\Tests C:\Users\Katya\CLionProjects\Lab2\cmake-build-debug C:\Users\Katya\CLionProjects\Lab2\cmake-build-debug\LibraryCPP\Tests C:\Users\Katya\CLionProjects\Lab2\cmake-build-debug\LibraryCPP\Tests\CMakeFiles\TestStackCPP.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : LibraryCPP/Tests/CMakeFiles/TestStackCPP.dir/depend

