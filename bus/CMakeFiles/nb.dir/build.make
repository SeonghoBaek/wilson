# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/major/workspace/wilson

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/major/workspace/wilson

# Include any dependencies generated for this target.
include bus/CMakeFiles/nb.dir/depend.make

# Include the progress variables for this target.
include bus/CMakeFiles/nb.dir/progress.make

# Include the compile flags for this target's objects.
include bus/CMakeFiles/nb.dir/flags.make

bus/CMakeFiles/nb.dir/src/BigNode.cpp.o: bus/CMakeFiles/nb.dir/flags.make
bus/CMakeFiles/nb.dir/src/BigNode.cpp.o: bus/src/BigNode.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/major/workspace/wilson/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object bus/CMakeFiles/nb.dir/src/BigNode.cpp.o"
	cd /home/major/workspace/wilson/bus && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/nb.dir/src/BigNode.cpp.o -c /home/major/workspace/wilson/bus/src/BigNode.cpp

bus/CMakeFiles/nb.dir/src/BigNode.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nb.dir/src/BigNode.cpp.i"
	cd /home/major/workspace/wilson/bus && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/major/workspace/wilson/bus/src/BigNode.cpp > CMakeFiles/nb.dir/src/BigNode.cpp.i

bus/CMakeFiles/nb.dir/src/BigNode.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nb.dir/src/BigNode.cpp.s"
	cd /home/major/workspace/wilson/bus && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/major/workspace/wilson/bus/src/BigNode.cpp -o CMakeFiles/nb.dir/src/BigNode.cpp.s

bus/CMakeFiles/nb.dir/src/BigNode.cpp.o.requires:
.PHONY : bus/CMakeFiles/nb.dir/src/BigNode.cpp.o.requires

bus/CMakeFiles/nb.dir/src/BigNode.cpp.o.provides: bus/CMakeFiles/nb.dir/src/BigNode.cpp.o.requires
	$(MAKE) -f bus/CMakeFiles/nb.dir/build.make bus/CMakeFiles/nb.dir/src/BigNode.cpp.o.provides.build
.PHONY : bus/CMakeFiles/nb.dir/src/BigNode.cpp.o.provides

bus/CMakeFiles/nb.dir/src/BigNode.cpp.o.provides.build: bus/CMakeFiles/nb.dir/src/BigNode.cpp.o

bus/CMakeFiles/nb.dir/src/Bridge.cpp.o: bus/CMakeFiles/nb.dir/flags.make
bus/CMakeFiles/nb.dir/src/Bridge.cpp.o: bus/src/Bridge.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/major/workspace/wilson/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object bus/CMakeFiles/nb.dir/src/Bridge.cpp.o"
	cd /home/major/workspace/wilson/bus && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/nb.dir/src/Bridge.cpp.o -c /home/major/workspace/wilson/bus/src/Bridge.cpp

bus/CMakeFiles/nb.dir/src/Bridge.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nb.dir/src/Bridge.cpp.i"
	cd /home/major/workspace/wilson/bus && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/major/workspace/wilson/bus/src/Bridge.cpp > CMakeFiles/nb.dir/src/Bridge.cpp.i

bus/CMakeFiles/nb.dir/src/Bridge.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nb.dir/src/Bridge.cpp.s"
	cd /home/major/workspace/wilson/bus && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/major/workspace/wilson/bus/src/Bridge.cpp -o CMakeFiles/nb.dir/src/Bridge.cpp.s

bus/CMakeFiles/nb.dir/src/Bridge.cpp.o.requires:
.PHONY : bus/CMakeFiles/nb.dir/src/Bridge.cpp.o.requires

bus/CMakeFiles/nb.dir/src/Bridge.cpp.o.provides: bus/CMakeFiles/nb.dir/src/Bridge.cpp.o.requires
	$(MAKE) -f bus/CMakeFiles/nb.dir/build.make bus/CMakeFiles/nb.dir/src/Bridge.cpp.o.provides.build
.PHONY : bus/CMakeFiles/nb.dir/src/Bridge.cpp.o.provides

bus/CMakeFiles/nb.dir/src/Bridge.cpp.o.provides.build: bus/CMakeFiles/nb.dir/src/Bridge.cpp.o

bus/CMakeFiles/nb.dir/src/ClientNode.cpp.o: bus/CMakeFiles/nb.dir/flags.make
bus/CMakeFiles/nb.dir/src/ClientNode.cpp.o: bus/src/ClientNode.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/major/workspace/wilson/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object bus/CMakeFiles/nb.dir/src/ClientNode.cpp.o"
	cd /home/major/workspace/wilson/bus && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/nb.dir/src/ClientNode.cpp.o -c /home/major/workspace/wilson/bus/src/ClientNode.cpp

bus/CMakeFiles/nb.dir/src/ClientNode.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nb.dir/src/ClientNode.cpp.i"
	cd /home/major/workspace/wilson/bus && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/major/workspace/wilson/bus/src/ClientNode.cpp > CMakeFiles/nb.dir/src/ClientNode.cpp.i

bus/CMakeFiles/nb.dir/src/ClientNode.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nb.dir/src/ClientNode.cpp.s"
	cd /home/major/workspace/wilson/bus && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/major/workspace/wilson/bus/src/ClientNode.cpp -o CMakeFiles/nb.dir/src/ClientNode.cpp.s

bus/CMakeFiles/nb.dir/src/ClientNode.cpp.o.requires:
.PHONY : bus/CMakeFiles/nb.dir/src/ClientNode.cpp.o.requires

bus/CMakeFiles/nb.dir/src/ClientNode.cpp.o.provides: bus/CMakeFiles/nb.dir/src/ClientNode.cpp.o.requires
	$(MAKE) -f bus/CMakeFiles/nb.dir/build.make bus/CMakeFiles/nb.dir/src/ClientNode.cpp.o.provides.build
.PHONY : bus/CMakeFiles/nb.dir/src/ClientNode.cpp.o.provides

bus/CMakeFiles/nb.dir/src/ClientNode.cpp.o.provides.build: bus/CMakeFiles/nb.dir/src/ClientNode.cpp.o

bus/CMakeFiles/nb.dir/src/DefaultGlobalService.cpp.o: bus/CMakeFiles/nb.dir/flags.make
bus/CMakeFiles/nb.dir/src/DefaultGlobalService.cpp.o: bus/src/DefaultGlobalService.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/major/workspace/wilson/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object bus/CMakeFiles/nb.dir/src/DefaultGlobalService.cpp.o"
	cd /home/major/workspace/wilson/bus && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/nb.dir/src/DefaultGlobalService.cpp.o -c /home/major/workspace/wilson/bus/src/DefaultGlobalService.cpp

bus/CMakeFiles/nb.dir/src/DefaultGlobalService.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nb.dir/src/DefaultGlobalService.cpp.i"
	cd /home/major/workspace/wilson/bus && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/major/workspace/wilson/bus/src/DefaultGlobalService.cpp > CMakeFiles/nb.dir/src/DefaultGlobalService.cpp.i

bus/CMakeFiles/nb.dir/src/DefaultGlobalService.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nb.dir/src/DefaultGlobalService.cpp.s"
	cd /home/major/workspace/wilson/bus && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/major/workspace/wilson/bus/src/DefaultGlobalService.cpp -o CMakeFiles/nb.dir/src/DefaultGlobalService.cpp.s

bus/CMakeFiles/nb.dir/src/DefaultGlobalService.cpp.o.requires:
.PHONY : bus/CMakeFiles/nb.dir/src/DefaultGlobalService.cpp.o.requires

bus/CMakeFiles/nb.dir/src/DefaultGlobalService.cpp.o.provides: bus/CMakeFiles/nb.dir/src/DefaultGlobalService.cpp.o.requires
	$(MAKE) -f bus/CMakeFiles/nb.dir/build.make bus/CMakeFiles/nb.dir/src/DefaultGlobalService.cpp.o.provides.build
.PHONY : bus/CMakeFiles/nb.dir/src/DefaultGlobalService.cpp.o.provides

bus/CMakeFiles/nb.dir/src/DefaultGlobalService.cpp.o.provides.build: bus/CMakeFiles/nb.dir/src/DefaultGlobalService.cpp.o

bus/CMakeFiles/nb.dir/src/DefaultService.cpp.o: bus/CMakeFiles/nb.dir/flags.make
bus/CMakeFiles/nb.dir/src/DefaultService.cpp.o: bus/src/DefaultService.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/major/workspace/wilson/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object bus/CMakeFiles/nb.dir/src/DefaultService.cpp.o"
	cd /home/major/workspace/wilson/bus && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/nb.dir/src/DefaultService.cpp.o -c /home/major/workspace/wilson/bus/src/DefaultService.cpp

bus/CMakeFiles/nb.dir/src/DefaultService.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nb.dir/src/DefaultService.cpp.i"
	cd /home/major/workspace/wilson/bus && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/major/workspace/wilson/bus/src/DefaultService.cpp > CMakeFiles/nb.dir/src/DefaultService.cpp.i

bus/CMakeFiles/nb.dir/src/DefaultService.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nb.dir/src/DefaultService.cpp.s"
	cd /home/major/workspace/wilson/bus && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/major/workspace/wilson/bus/src/DefaultService.cpp -o CMakeFiles/nb.dir/src/DefaultService.cpp.s

bus/CMakeFiles/nb.dir/src/DefaultService.cpp.o.requires:
.PHONY : bus/CMakeFiles/nb.dir/src/DefaultService.cpp.o.requires

bus/CMakeFiles/nb.dir/src/DefaultService.cpp.o.provides: bus/CMakeFiles/nb.dir/src/DefaultService.cpp.o.requires
	$(MAKE) -f bus/CMakeFiles/nb.dir/build.make bus/CMakeFiles/nb.dir/src/DefaultService.cpp.o.provides.build
.PHONY : bus/CMakeFiles/nb.dir/src/DefaultService.cpp.o.provides

bus/CMakeFiles/nb.dir/src/DefaultService.cpp.o.provides.build: bus/CMakeFiles/nb.dir/src/DefaultService.cpp.o

bus/CMakeFiles/nb.dir/src/GlobalBusInit.cpp.o: bus/CMakeFiles/nb.dir/flags.make
bus/CMakeFiles/nb.dir/src/GlobalBusInit.cpp.o: bus/src/GlobalBusInit.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/major/workspace/wilson/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object bus/CMakeFiles/nb.dir/src/GlobalBusInit.cpp.o"
	cd /home/major/workspace/wilson/bus && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/nb.dir/src/GlobalBusInit.cpp.o -c /home/major/workspace/wilson/bus/src/GlobalBusInit.cpp

bus/CMakeFiles/nb.dir/src/GlobalBusInit.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nb.dir/src/GlobalBusInit.cpp.i"
	cd /home/major/workspace/wilson/bus && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/major/workspace/wilson/bus/src/GlobalBusInit.cpp > CMakeFiles/nb.dir/src/GlobalBusInit.cpp.i

bus/CMakeFiles/nb.dir/src/GlobalBusInit.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nb.dir/src/GlobalBusInit.cpp.s"
	cd /home/major/workspace/wilson/bus && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/major/workspace/wilson/bus/src/GlobalBusInit.cpp -o CMakeFiles/nb.dir/src/GlobalBusInit.cpp.s

bus/CMakeFiles/nb.dir/src/GlobalBusInit.cpp.o.requires:
.PHONY : bus/CMakeFiles/nb.dir/src/GlobalBusInit.cpp.o.requires

bus/CMakeFiles/nb.dir/src/GlobalBusInit.cpp.o.provides: bus/CMakeFiles/nb.dir/src/GlobalBusInit.cpp.o.requires
	$(MAKE) -f bus/CMakeFiles/nb.dir/build.make bus/CMakeFiles/nb.dir/src/GlobalBusInit.cpp.o.provides.build
.PHONY : bus/CMakeFiles/nb.dir/src/GlobalBusInit.cpp.o.provides

bus/CMakeFiles/nb.dir/src/GlobalBusInit.cpp.o.provides.build: bus/CMakeFiles/nb.dir/src/GlobalBusInit.cpp.o

bus/CMakeFiles/nb.dir/src/INodeBusService.cpp.o: bus/CMakeFiles/nb.dir/flags.make
bus/CMakeFiles/nb.dir/src/INodeBusService.cpp.o: bus/src/INodeBusService.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/major/workspace/wilson/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object bus/CMakeFiles/nb.dir/src/INodeBusService.cpp.o"
	cd /home/major/workspace/wilson/bus && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/nb.dir/src/INodeBusService.cpp.o -c /home/major/workspace/wilson/bus/src/INodeBusService.cpp

bus/CMakeFiles/nb.dir/src/INodeBusService.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nb.dir/src/INodeBusService.cpp.i"
	cd /home/major/workspace/wilson/bus && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/major/workspace/wilson/bus/src/INodeBusService.cpp > CMakeFiles/nb.dir/src/INodeBusService.cpp.i

bus/CMakeFiles/nb.dir/src/INodeBusService.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nb.dir/src/INodeBusService.cpp.s"
	cd /home/major/workspace/wilson/bus && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/major/workspace/wilson/bus/src/INodeBusService.cpp -o CMakeFiles/nb.dir/src/INodeBusService.cpp.s

bus/CMakeFiles/nb.dir/src/INodeBusService.cpp.o.requires:
.PHONY : bus/CMakeFiles/nb.dir/src/INodeBusService.cpp.o.requires

bus/CMakeFiles/nb.dir/src/INodeBusService.cpp.o.provides: bus/CMakeFiles/nb.dir/src/INodeBusService.cpp.o.requires
	$(MAKE) -f bus/CMakeFiles/nb.dir/build.make bus/CMakeFiles/nb.dir/src/INodeBusService.cpp.o.provides.build
.PHONY : bus/CMakeFiles/nb.dir/src/INodeBusService.cpp.o.provides

bus/CMakeFiles/nb.dir/src/INodeBusService.cpp.o.provides.build: bus/CMakeFiles/nb.dir/src/INodeBusService.cpp.o

bus/CMakeFiles/nb.dir/src/Lock.cpp.o: bus/CMakeFiles/nb.dir/flags.make
bus/CMakeFiles/nb.dir/src/Lock.cpp.o: bus/src/Lock.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/major/workspace/wilson/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object bus/CMakeFiles/nb.dir/src/Lock.cpp.o"
	cd /home/major/workspace/wilson/bus && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/nb.dir/src/Lock.cpp.o -c /home/major/workspace/wilson/bus/src/Lock.cpp

bus/CMakeFiles/nb.dir/src/Lock.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nb.dir/src/Lock.cpp.i"
	cd /home/major/workspace/wilson/bus && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/major/workspace/wilson/bus/src/Lock.cpp > CMakeFiles/nb.dir/src/Lock.cpp.i

bus/CMakeFiles/nb.dir/src/Lock.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nb.dir/src/Lock.cpp.s"
	cd /home/major/workspace/wilson/bus && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/major/workspace/wilson/bus/src/Lock.cpp -o CMakeFiles/nb.dir/src/Lock.cpp.s

bus/CMakeFiles/nb.dir/src/Lock.cpp.o.requires:
.PHONY : bus/CMakeFiles/nb.dir/src/Lock.cpp.o.requires

bus/CMakeFiles/nb.dir/src/Lock.cpp.o.provides: bus/CMakeFiles/nb.dir/src/Lock.cpp.o.requires
	$(MAKE) -f bus/CMakeFiles/nb.dir/build.make bus/CMakeFiles/nb.dir/src/Lock.cpp.o.provides.build
.PHONY : bus/CMakeFiles/nb.dir/src/Lock.cpp.o.provides

bus/CMakeFiles/nb.dir/src/Lock.cpp.o.provides.build: bus/CMakeFiles/nb.dir/src/Lock.cpp.o

bus/CMakeFiles/nb.dir/src/Log.cpp.o: bus/CMakeFiles/nb.dir/flags.make
bus/CMakeFiles/nb.dir/src/Log.cpp.o: bus/src/Log.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/major/workspace/wilson/CMakeFiles $(CMAKE_PROGRESS_9)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object bus/CMakeFiles/nb.dir/src/Log.cpp.o"
	cd /home/major/workspace/wilson/bus && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/nb.dir/src/Log.cpp.o -c /home/major/workspace/wilson/bus/src/Log.cpp

bus/CMakeFiles/nb.dir/src/Log.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nb.dir/src/Log.cpp.i"
	cd /home/major/workspace/wilson/bus && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/major/workspace/wilson/bus/src/Log.cpp > CMakeFiles/nb.dir/src/Log.cpp.i

bus/CMakeFiles/nb.dir/src/Log.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nb.dir/src/Log.cpp.s"
	cd /home/major/workspace/wilson/bus && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/major/workspace/wilson/bus/src/Log.cpp -o CMakeFiles/nb.dir/src/Log.cpp.s

bus/CMakeFiles/nb.dir/src/Log.cpp.o.requires:
.PHONY : bus/CMakeFiles/nb.dir/src/Log.cpp.o.requires

bus/CMakeFiles/nb.dir/src/Log.cpp.o.provides: bus/CMakeFiles/nb.dir/src/Log.cpp.o.requires
	$(MAKE) -f bus/CMakeFiles/nb.dir/build.make bus/CMakeFiles/nb.dir/src/Log.cpp.o.provides.build
.PHONY : bus/CMakeFiles/nb.dir/src/Log.cpp.o.provides

bus/CMakeFiles/nb.dir/src/Log.cpp.o.provides.build: bus/CMakeFiles/nb.dir/src/Log.cpp.o

bus/CMakeFiles/nb.dir/src/NodeLooper.cpp.o: bus/CMakeFiles/nb.dir/flags.make
bus/CMakeFiles/nb.dir/src/NodeLooper.cpp.o: bus/src/NodeLooper.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/major/workspace/wilson/CMakeFiles $(CMAKE_PROGRESS_10)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object bus/CMakeFiles/nb.dir/src/NodeLooper.cpp.o"
	cd /home/major/workspace/wilson/bus && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/nb.dir/src/NodeLooper.cpp.o -c /home/major/workspace/wilson/bus/src/NodeLooper.cpp

bus/CMakeFiles/nb.dir/src/NodeLooper.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nb.dir/src/NodeLooper.cpp.i"
	cd /home/major/workspace/wilson/bus && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/major/workspace/wilson/bus/src/NodeLooper.cpp > CMakeFiles/nb.dir/src/NodeLooper.cpp.i

bus/CMakeFiles/nb.dir/src/NodeLooper.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nb.dir/src/NodeLooper.cpp.s"
	cd /home/major/workspace/wilson/bus && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/major/workspace/wilson/bus/src/NodeLooper.cpp -o CMakeFiles/nb.dir/src/NodeLooper.cpp.s

bus/CMakeFiles/nb.dir/src/NodeLooper.cpp.o.requires:
.PHONY : bus/CMakeFiles/nb.dir/src/NodeLooper.cpp.o.requires

bus/CMakeFiles/nb.dir/src/NodeLooper.cpp.o.provides: bus/CMakeFiles/nb.dir/src/NodeLooper.cpp.o.requires
	$(MAKE) -f bus/CMakeFiles/nb.dir/build.make bus/CMakeFiles/nb.dir/src/NodeLooper.cpp.o.provides.build
.PHONY : bus/CMakeFiles/nb.dir/src/NodeLooper.cpp.o.provides

bus/CMakeFiles/nb.dir/src/NodeLooper.cpp.o.provides.build: bus/CMakeFiles/nb.dir/src/NodeLooper.cpp.o

bus/CMakeFiles/nb.dir/src/NodeNetwork.cpp.o: bus/CMakeFiles/nb.dir/flags.make
bus/CMakeFiles/nb.dir/src/NodeNetwork.cpp.o: bus/src/NodeNetwork.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/major/workspace/wilson/CMakeFiles $(CMAKE_PROGRESS_11)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object bus/CMakeFiles/nb.dir/src/NodeNetwork.cpp.o"
	cd /home/major/workspace/wilson/bus && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/nb.dir/src/NodeNetwork.cpp.o -c /home/major/workspace/wilson/bus/src/NodeNetwork.cpp

bus/CMakeFiles/nb.dir/src/NodeNetwork.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nb.dir/src/NodeNetwork.cpp.i"
	cd /home/major/workspace/wilson/bus && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/major/workspace/wilson/bus/src/NodeNetwork.cpp > CMakeFiles/nb.dir/src/NodeNetwork.cpp.i

bus/CMakeFiles/nb.dir/src/NodeNetwork.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nb.dir/src/NodeNetwork.cpp.s"
	cd /home/major/workspace/wilson/bus && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/major/workspace/wilson/bus/src/NodeNetwork.cpp -o CMakeFiles/nb.dir/src/NodeNetwork.cpp.s

bus/CMakeFiles/nb.dir/src/NodeNetwork.cpp.o.requires:
.PHONY : bus/CMakeFiles/nb.dir/src/NodeNetwork.cpp.o.requires

bus/CMakeFiles/nb.dir/src/NodeNetwork.cpp.o.provides: bus/CMakeFiles/nb.dir/src/NodeNetwork.cpp.o.requires
	$(MAKE) -f bus/CMakeFiles/nb.dir/build.make bus/CMakeFiles/nb.dir/src/NodeNetwork.cpp.o.provides.build
.PHONY : bus/CMakeFiles/nb.dir/src/NodeNetwork.cpp.o.provides

bus/CMakeFiles/nb.dir/src/NodeNetwork.cpp.o.provides.build: bus/CMakeFiles/nb.dir/src/NodeNetwork.cpp.o

bus/CMakeFiles/nb.dir/src/NodePort.cpp.o: bus/CMakeFiles/nb.dir/flags.make
bus/CMakeFiles/nb.dir/src/NodePort.cpp.o: bus/src/NodePort.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/major/workspace/wilson/CMakeFiles $(CMAKE_PROGRESS_12)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object bus/CMakeFiles/nb.dir/src/NodePort.cpp.o"
	cd /home/major/workspace/wilson/bus && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/nb.dir/src/NodePort.cpp.o -c /home/major/workspace/wilson/bus/src/NodePort.cpp

bus/CMakeFiles/nb.dir/src/NodePort.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nb.dir/src/NodePort.cpp.i"
	cd /home/major/workspace/wilson/bus && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/major/workspace/wilson/bus/src/NodePort.cpp > CMakeFiles/nb.dir/src/NodePort.cpp.i

bus/CMakeFiles/nb.dir/src/NodePort.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nb.dir/src/NodePort.cpp.s"
	cd /home/major/workspace/wilson/bus && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/major/workspace/wilson/bus/src/NodePort.cpp -o CMakeFiles/nb.dir/src/NodePort.cpp.s

bus/CMakeFiles/nb.dir/src/NodePort.cpp.o.requires:
.PHONY : bus/CMakeFiles/nb.dir/src/NodePort.cpp.o.requires

bus/CMakeFiles/nb.dir/src/NodePort.cpp.o.provides: bus/CMakeFiles/nb.dir/src/NodePort.cpp.o.requires
	$(MAKE) -f bus/CMakeFiles/nb.dir/build.make bus/CMakeFiles/nb.dir/src/NodePort.cpp.o.provides.build
.PHONY : bus/CMakeFiles/nb.dir/src/NodePort.cpp.o.provides

bus/CMakeFiles/nb.dir/src/NodePort.cpp.o.provides.build: bus/CMakeFiles/nb.dir/src/NodePort.cpp.o

bus/CMakeFiles/nb.dir/src/Normalizer.cpp.o: bus/CMakeFiles/nb.dir/flags.make
bus/CMakeFiles/nb.dir/src/Normalizer.cpp.o: bus/src/Normalizer.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/major/workspace/wilson/CMakeFiles $(CMAKE_PROGRESS_13)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object bus/CMakeFiles/nb.dir/src/Normalizer.cpp.o"
	cd /home/major/workspace/wilson/bus && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/nb.dir/src/Normalizer.cpp.o -c /home/major/workspace/wilson/bus/src/Normalizer.cpp

bus/CMakeFiles/nb.dir/src/Normalizer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nb.dir/src/Normalizer.cpp.i"
	cd /home/major/workspace/wilson/bus && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/major/workspace/wilson/bus/src/Normalizer.cpp > CMakeFiles/nb.dir/src/Normalizer.cpp.i

bus/CMakeFiles/nb.dir/src/Normalizer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nb.dir/src/Normalizer.cpp.s"
	cd /home/major/workspace/wilson/bus && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/major/workspace/wilson/bus/src/Normalizer.cpp -o CMakeFiles/nb.dir/src/Normalizer.cpp.s

bus/CMakeFiles/nb.dir/src/Normalizer.cpp.o.requires:
.PHONY : bus/CMakeFiles/nb.dir/src/Normalizer.cpp.o.requires

bus/CMakeFiles/nb.dir/src/Normalizer.cpp.o.provides: bus/CMakeFiles/nb.dir/src/Normalizer.cpp.o.requires
	$(MAKE) -f bus/CMakeFiles/nb.dir/build.make bus/CMakeFiles/nb.dir/src/Normalizer.cpp.o.provides.build
.PHONY : bus/CMakeFiles/nb.dir/src/Normalizer.cpp.o.provides

bus/CMakeFiles/nb.dir/src/Normalizer.cpp.o.provides.build: bus/CMakeFiles/nb.dir/src/Normalizer.cpp.o

bus/CMakeFiles/nb.dir/src/Packet.cpp.o: bus/CMakeFiles/nb.dir/flags.make
bus/CMakeFiles/nb.dir/src/Packet.cpp.o: bus/src/Packet.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/major/workspace/wilson/CMakeFiles $(CMAKE_PROGRESS_14)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object bus/CMakeFiles/nb.dir/src/Packet.cpp.o"
	cd /home/major/workspace/wilson/bus && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/nb.dir/src/Packet.cpp.o -c /home/major/workspace/wilson/bus/src/Packet.cpp

bus/CMakeFiles/nb.dir/src/Packet.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nb.dir/src/Packet.cpp.i"
	cd /home/major/workspace/wilson/bus && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/major/workspace/wilson/bus/src/Packet.cpp > CMakeFiles/nb.dir/src/Packet.cpp.i

bus/CMakeFiles/nb.dir/src/Packet.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nb.dir/src/Packet.cpp.s"
	cd /home/major/workspace/wilson/bus && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/major/workspace/wilson/bus/src/Packet.cpp -o CMakeFiles/nb.dir/src/Packet.cpp.s

bus/CMakeFiles/nb.dir/src/Packet.cpp.o.requires:
.PHONY : bus/CMakeFiles/nb.dir/src/Packet.cpp.o.requires

bus/CMakeFiles/nb.dir/src/Packet.cpp.o.provides: bus/CMakeFiles/nb.dir/src/Packet.cpp.o.requires
	$(MAKE) -f bus/CMakeFiles/nb.dir/build.make bus/CMakeFiles/nb.dir/src/Packet.cpp.o.provides.build
.PHONY : bus/CMakeFiles/nb.dir/src/Packet.cpp.o.provides

bus/CMakeFiles/nb.dir/src/Packet.cpp.o.provides.build: bus/CMakeFiles/nb.dir/src/Packet.cpp.o

bus/CMakeFiles/nb.dir/src/Queue.cpp.o: bus/CMakeFiles/nb.dir/flags.make
bus/CMakeFiles/nb.dir/src/Queue.cpp.o: bus/src/Queue.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/major/workspace/wilson/CMakeFiles $(CMAKE_PROGRESS_15)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object bus/CMakeFiles/nb.dir/src/Queue.cpp.o"
	cd /home/major/workspace/wilson/bus && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/nb.dir/src/Queue.cpp.o -c /home/major/workspace/wilson/bus/src/Queue.cpp

bus/CMakeFiles/nb.dir/src/Queue.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nb.dir/src/Queue.cpp.i"
	cd /home/major/workspace/wilson/bus && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/major/workspace/wilson/bus/src/Queue.cpp > CMakeFiles/nb.dir/src/Queue.cpp.i

bus/CMakeFiles/nb.dir/src/Queue.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nb.dir/src/Queue.cpp.s"
	cd /home/major/workspace/wilson/bus && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/major/workspace/wilson/bus/src/Queue.cpp -o CMakeFiles/nb.dir/src/Queue.cpp.s

bus/CMakeFiles/nb.dir/src/Queue.cpp.o.requires:
.PHONY : bus/CMakeFiles/nb.dir/src/Queue.cpp.o.requires

bus/CMakeFiles/nb.dir/src/Queue.cpp.o.provides: bus/CMakeFiles/nb.dir/src/Queue.cpp.o.requires
	$(MAKE) -f bus/CMakeFiles/nb.dir/build.make bus/CMakeFiles/nb.dir/src/Queue.cpp.o.provides.build
.PHONY : bus/CMakeFiles/nb.dir/src/Queue.cpp.o.provides

bus/CMakeFiles/nb.dir/src/Queue.cpp.o.provides.build: bus/CMakeFiles/nb.dir/src/Queue.cpp.o

bus/CMakeFiles/nb.dir/src/XMLParser.cpp.o: bus/CMakeFiles/nb.dir/flags.make
bus/CMakeFiles/nb.dir/src/XMLParser.cpp.o: bus/src/XMLParser.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/major/workspace/wilson/CMakeFiles $(CMAKE_PROGRESS_16)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object bus/CMakeFiles/nb.dir/src/XMLParser.cpp.o"
	cd /home/major/workspace/wilson/bus && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/nb.dir/src/XMLParser.cpp.o -c /home/major/workspace/wilson/bus/src/XMLParser.cpp

bus/CMakeFiles/nb.dir/src/XMLParser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nb.dir/src/XMLParser.cpp.i"
	cd /home/major/workspace/wilson/bus && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/major/workspace/wilson/bus/src/XMLParser.cpp > CMakeFiles/nb.dir/src/XMLParser.cpp.i

bus/CMakeFiles/nb.dir/src/XMLParser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nb.dir/src/XMLParser.cpp.s"
	cd /home/major/workspace/wilson/bus && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/major/workspace/wilson/bus/src/XMLParser.cpp -o CMakeFiles/nb.dir/src/XMLParser.cpp.s

bus/CMakeFiles/nb.dir/src/XMLParser.cpp.o.requires:
.PHONY : bus/CMakeFiles/nb.dir/src/XMLParser.cpp.o.requires

bus/CMakeFiles/nb.dir/src/XMLParser.cpp.o.provides: bus/CMakeFiles/nb.dir/src/XMLParser.cpp.o.requires
	$(MAKE) -f bus/CMakeFiles/nb.dir/build.make bus/CMakeFiles/nb.dir/src/XMLParser.cpp.o.provides.build
.PHONY : bus/CMakeFiles/nb.dir/src/XMLParser.cpp.o.provides

bus/CMakeFiles/nb.dir/src/XMLParser.cpp.o.provides.build: bus/CMakeFiles/nb.dir/src/XMLParser.cpp.o

# Object files for target nb
nb_OBJECTS = \
"CMakeFiles/nb.dir/src/BigNode.cpp.o" \
"CMakeFiles/nb.dir/src/Bridge.cpp.o" \
"CMakeFiles/nb.dir/src/ClientNode.cpp.o" \
"CMakeFiles/nb.dir/src/DefaultGlobalService.cpp.o" \
"CMakeFiles/nb.dir/src/DefaultService.cpp.o" \
"CMakeFiles/nb.dir/src/GlobalBusInit.cpp.o" \
"CMakeFiles/nb.dir/src/INodeBusService.cpp.o" \
"CMakeFiles/nb.dir/src/Lock.cpp.o" \
"CMakeFiles/nb.dir/src/Log.cpp.o" \
"CMakeFiles/nb.dir/src/NodeLooper.cpp.o" \
"CMakeFiles/nb.dir/src/NodeNetwork.cpp.o" \
"CMakeFiles/nb.dir/src/NodePort.cpp.o" \
"CMakeFiles/nb.dir/src/Normalizer.cpp.o" \
"CMakeFiles/nb.dir/src/Packet.cpp.o" \
"CMakeFiles/nb.dir/src/Queue.cpp.o" \
"CMakeFiles/nb.dir/src/XMLParser.cpp.o"

# External object files for target nb
nb_EXTERNAL_OBJECTS =

bus/libnb.so: bus/CMakeFiles/nb.dir/src/BigNode.cpp.o
bus/libnb.so: bus/CMakeFiles/nb.dir/src/Bridge.cpp.o
bus/libnb.so: bus/CMakeFiles/nb.dir/src/ClientNode.cpp.o
bus/libnb.so: bus/CMakeFiles/nb.dir/src/DefaultGlobalService.cpp.o
bus/libnb.so: bus/CMakeFiles/nb.dir/src/DefaultService.cpp.o
bus/libnb.so: bus/CMakeFiles/nb.dir/src/GlobalBusInit.cpp.o
bus/libnb.so: bus/CMakeFiles/nb.dir/src/INodeBusService.cpp.o
bus/libnb.so: bus/CMakeFiles/nb.dir/src/Lock.cpp.o
bus/libnb.so: bus/CMakeFiles/nb.dir/src/Log.cpp.o
bus/libnb.so: bus/CMakeFiles/nb.dir/src/NodeLooper.cpp.o
bus/libnb.so: bus/CMakeFiles/nb.dir/src/NodeNetwork.cpp.o
bus/libnb.so: bus/CMakeFiles/nb.dir/src/NodePort.cpp.o
bus/libnb.so: bus/CMakeFiles/nb.dir/src/Normalizer.cpp.o
bus/libnb.so: bus/CMakeFiles/nb.dir/src/Packet.cpp.o
bus/libnb.so: bus/CMakeFiles/nb.dir/src/Queue.cpp.o
bus/libnb.so: bus/CMakeFiles/nb.dir/src/XMLParser.cpp.o
bus/libnb.so: bus/CMakeFiles/nb.dir/build.make
bus/libnb.so: bus/CMakeFiles/nb.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library libnb.so"
	cd /home/major/workspace/wilson/bus && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/nb.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
bus/CMakeFiles/nb.dir/build: bus/libnb.so
.PHONY : bus/CMakeFiles/nb.dir/build

bus/CMakeFiles/nb.dir/requires: bus/CMakeFiles/nb.dir/src/BigNode.cpp.o.requires
bus/CMakeFiles/nb.dir/requires: bus/CMakeFiles/nb.dir/src/Bridge.cpp.o.requires
bus/CMakeFiles/nb.dir/requires: bus/CMakeFiles/nb.dir/src/ClientNode.cpp.o.requires
bus/CMakeFiles/nb.dir/requires: bus/CMakeFiles/nb.dir/src/DefaultGlobalService.cpp.o.requires
bus/CMakeFiles/nb.dir/requires: bus/CMakeFiles/nb.dir/src/DefaultService.cpp.o.requires
bus/CMakeFiles/nb.dir/requires: bus/CMakeFiles/nb.dir/src/GlobalBusInit.cpp.o.requires
bus/CMakeFiles/nb.dir/requires: bus/CMakeFiles/nb.dir/src/INodeBusService.cpp.o.requires
bus/CMakeFiles/nb.dir/requires: bus/CMakeFiles/nb.dir/src/Lock.cpp.o.requires
bus/CMakeFiles/nb.dir/requires: bus/CMakeFiles/nb.dir/src/Log.cpp.o.requires
bus/CMakeFiles/nb.dir/requires: bus/CMakeFiles/nb.dir/src/NodeLooper.cpp.o.requires
bus/CMakeFiles/nb.dir/requires: bus/CMakeFiles/nb.dir/src/NodeNetwork.cpp.o.requires
bus/CMakeFiles/nb.dir/requires: bus/CMakeFiles/nb.dir/src/NodePort.cpp.o.requires
bus/CMakeFiles/nb.dir/requires: bus/CMakeFiles/nb.dir/src/Normalizer.cpp.o.requires
bus/CMakeFiles/nb.dir/requires: bus/CMakeFiles/nb.dir/src/Packet.cpp.o.requires
bus/CMakeFiles/nb.dir/requires: bus/CMakeFiles/nb.dir/src/Queue.cpp.o.requires
bus/CMakeFiles/nb.dir/requires: bus/CMakeFiles/nb.dir/src/XMLParser.cpp.o.requires
.PHONY : bus/CMakeFiles/nb.dir/requires

bus/CMakeFiles/nb.dir/clean:
	cd /home/major/workspace/wilson/bus && $(CMAKE_COMMAND) -P CMakeFiles/nb.dir/cmake_clean.cmake
.PHONY : bus/CMakeFiles/nb.dir/clean

bus/CMakeFiles/nb.dir/depend:
	cd /home/major/workspace/wilson && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/major/workspace/wilson /home/major/workspace/wilson/bus /home/major/workspace/wilson /home/major/workspace/wilson/bus /home/major/workspace/wilson/bus/CMakeFiles/nb.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : bus/CMakeFiles/nb.dir/depend

