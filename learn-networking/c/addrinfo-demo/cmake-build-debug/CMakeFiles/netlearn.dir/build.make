# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/avilay/.local/share/JetBrains/Toolbox/apps/clion/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /home/avilay/.local/share/JetBrains/Toolbox/apps/clion/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/avilay/projects/bitbucket/learn/learn-cs/learn-networking/c/addrinfo-demo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/avilay/projects/bitbucket/learn/learn-cs/learn-networking/c/addrinfo-demo/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/netlearn.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/netlearn.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/netlearn.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/netlearn.dir/flags.make

CMakeFiles/netlearn.dir/main.c.o: CMakeFiles/netlearn.dir/flags.make
CMakeFiles/netlearn.dir/main.c.o: /home/avilay/projects/bitbucket/learn/learn-cs/learn-networking/c/addrinfo-demo/main.c
CMakeFiles/netlearn.dir/main.c.o: CMakeFiles/netlearn.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/avilay/projects/bitbucket/learn/learn-cs/learn-networking/c/addrinfo-demo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/netlearn.dir/main.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/netlearn.dir/main.c.o -MF CMakeFiles/netlearn.dir/main.c.o.d -o CMakeFiles/netlearn.dir/main.c.o -c /home/avilay/projects/bitbucket/learn/learn-cs/learn-networking/c/addrinfo-demo/main.c

CMakeFiles/netlearn.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/netlearn.dir/main.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/avilay/projects/bitbucket/learn/learn-cs/learn-networking/c/addrinfo-demo/main.c > CMakeFiles/netlearn.dir/main.c.i

CMakeFiles/netlearn.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/netlearn.dir/main.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/avilay/projects/bitbucket/learn/learn-cs/learn-networking/c/addrinfo-demo/main.c -o CMakeFiles/netlearn.dir/main.c.s

CMakeFiles/netlearn.dir/netutils.c.o: CMakeFiles/netlearn.dir/flags.make
CMakeFiles/netlearn.dir/netutils.c.o: /home/avilay/projects/bitbucket/learn/learn-cs/learn-networking/c/addrinfo-demo/netutils.c
CMakeFiles/netlearn.dir/netutils.c.o: CMakeFiles/netlearn.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/avilay/projects/bitbucket/learn/learn-cs/learn-networking/c/addrinfo-demo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/netlearn.dir/netutils.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/netlearn.dir/netutils.c.o -MF CMakeFiles/netlearn.dir/netutils.c.o.d -o CMakeFiles/netlearn.dir/netutils.c.o -c /home/avilay/projects/bitbucket/learn/learn-cs/learn-networking/c/addrinfo-demo/netutils.c

CMakeFiles/netlearn.dir/netutils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/netlearn.dir/netutils.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/avilay/projects/bitbucket/learn/learn-cs/learn-networking/c/addrinfo-demo/netutils.c > CMakeFiles/netlearn.dir/netutils.c.i

CMakeFiles/netlearn.dir/netutils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/netlearn.dir/netutils.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/avilay/projects/bitbucket/learn/learn-cs/learn-networking/c/addrinfo-demo/netutils.c -o CMakeFiles/netlearn.dir/netutils.c.s

CMakeFiles/netlearn.dir/stringutils.c.o: CMakeFiles/netlearn.dir/flags.make
CMakeFiles/netlearn.dir/stringutils.c.o: /home/avilay/projects/bitbucket/learn/learn-cs/learn-networking/c/addrinfo-demo/stringutils.c
CMakeFiles/netlearn.dir/stringutils.c.o: CMakeFiles/netlearn.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/avilay/projects/bitbucket/learn/learn-cs/learn-networking/c/addrinfo-demo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/netlearn.dir/stringutils.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/netlearn.dir/stringutils.c.o -MF CMakeFiles/netlearn.dir/stringutils.c.o.d -o CMakeFiles/netlearn.dir/stringutils.c.o -c /home/avilay/projects/bitbucket/learn/learn-cs/learn-networking/c/addrinfo-demo/stringutils.c

CMakeFiles/netlearn.dir/stringutils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/netlearn.dir/stringutils.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/avilay/projects/bitbucket/learn/learn-cs/learn-networking/c/addrinfo-demo/stringutils.c > CMakeFiles/netlearn.dir/stringutils.c.i

CMakeFiles/netlearn.dir/stringutils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/netlearn.dir/stringutils.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/avilay/projects/bitbucket/learn/learn-cs/learn-networking/c/addrinfo-demo/stringutils.c -o CMakeFiles/netlearn.dir/stringutils.c.s

# Object files for target netlearn
netlearn_OBJECTS = \
"CMakeFiles/netlearn.dir/main.c.o" \
"CMakeFiles/netlearn.dir/netutils.c.o" \
"CMakeFiles/netlearn.dir/stringutils.c.o"

# External object files for target netlearn
netlearn_EXTERNAL_OBJECTS =

netlearn: CMakeFiles/netlearn.dir/main.c.o
netlearn: CMakeFiles/netlearn.dir/netutils.c.o
netlearn: CMakeFiles/netlearn.dir/stringutils.c.o
netlearn: CMakeFiles/netlearn.dir/build.make
netlearn: CMakeFiles/netlearn.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/avilay/projects/bitbucket/learn/learn-cs/learn-networking/c/addrinfo-demo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable netlearn"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/netlearn.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/netlearn.dir/build: netlearn
.PHONY : CMakeFiles/netlearn.dir/build

CMakeFiles/netlearn.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/netlearn.dir/cmake_clean.cmake
.PHONY : CMakeFiles/netlearn.dir/clean

CMakeFiles/netlearn.dir/depend:
	cd /home/avilay/projects/bitbucket/learn/learn-cs/learn-networking/c/addrinfo-demo/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/avilay/projects/bitbucket/learn/learn-cs/learn-networking/c/addrinfo-demo /home/avilay/projects/bitbucket/learn/learn-cs/learn-networking/c/addrinfo-demo /home/avilay/projects/bitbucket/learn/learn-cs/learn-networking/c/addrinfo-demo/cmake-build-debug /home/avilay/projects/bitbucket/learn/learn-cs/learn-networking/c/addrinfo-demo/cmake-build-debug /home/avilay/projects/bitbucket/learn/learn-cs/learn-networking/c/addrinfo-demo/cmake-build-debug/CMakeFiles/netlearn.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/netlearn.dir/depend

