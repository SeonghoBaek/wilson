# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

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

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running interactive CMake command-line interface..."
	/usr/bin/cmake -i .
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target install
install: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	/usr/bin/cmake -P cmake_install.cmake
.PHONY : install

# Special rule for the target install
install/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	/usr/bin/cmake -P cmake_install.cmake
.PHONY : install/fast

# Special rule for the target install/local
install/local: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing only the local directory..."
	/usr/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local

# Special rule for the target install/local
install/local/fast: install/local
.PHONY : install/local/fast

# Special rule for the target install/strip
install/strip: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing the project stripped..."
	/usr/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip

# Special rule for the target install/strip
install/strip/fast: install/strip
.PHONY : install/strip/fast

# Special rule for the target list_install_components
list_install_components:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Available install components are: \"Unspecified\""
.PHONY : list_install_components

# Special rule for the target list_install_components
list_install_components/fast: list_install_components
.PHONY : list_install_components/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/major/workspace/wilson/CMakeFiles /home/major/workspace/wilson/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/major/workspace/wilson/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named jsoncpp_lib_static

# Build rule for target.
jsoncpp_lib_static: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 jsoncpp_lib_static
.PHONY : jsoncpp_lib_static

# fast build rule for target.
jsoncpp_lib_static/fast:
	$(MAKE) -f external/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/build.make external/jsoncpp/src/lib_json/CMakeFiles/jsoncpp_lib_static.dir/build
.PHONY : jsoncpp_lib_static/fast

#=============================================================================
# Target rules for targets named jsoncpp_check

# Build rule for target.
jsoncpp_check: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 jsoncpp_check
.PHONY : jsoncpp_check

# fast build rule for target.
jsoncpp_check/fast:
	$(MAKE) -f external/jsoncpp/src/jsontestrunner/CMakeFiles/jsoncpp_check.dir/build.make external/jsoncpp/src/jsontestrunner/CMakeFiles/jsoncpp_check.dir/build
.PHONY : jsoncpp_check/fast

#=============================================================================
# Target rules for targets named jsoncpp_readerwriter_tests

# Build rule for target.
jsoncpp_readerwriter_tests: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 jsoncpp_readerwriter_tests
.PHONY : jsoncpp_readerwriter_tests

# fast build rule for target.
jsoncpp_readerwriter_tests/fast:
	$(MAKE) -f external/jsoncpp/src/jsontestrunner/CMakeFiles/jsoncpp_readerwriter_tests.dir/build.make external/jsoncpp/src/jsontestrunner/CMakeFiles/jsoncpp_readerwriter_tests.dir/build
.PHONY : jsoncpp_readerwriter_tests/fast

#=============================================================================
# Target rules for targets named jsontestrunner_exe

# Build rule for target.
jsontestrunner_exe: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 jsontestrunner_exe
.PHONY : jsontestrunner_exe

# fast build rule for target.
jsontestrunner_exe/fast:
	$(MAKE) -f external/jsoncpp/src/jsontestrunner/CMakeFiles/jsontestrunner_exe.dir/build.make external/jsoncpp/src/jsontestrunner/CMakeFiles/jsontestrunner_exe.dir/build
.PHONY : jsontestrunner_exe/fast

#=============================================================================
# Target rules for targets named jsoncpp_test

# Build rule for target.
jsoncpp_test: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 jsoncpp_test
.PHONY : jsoncpp_test

# fast build rule for target.
jsoncpp_test/fast:
	$(MAKE) -f external/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/build.make external/jsoncpp/src/test_lib_json/CMakeFiles/jsoncpp_test.dir/build
.PHONY : jsoncpp_test/fast

#=============================================================================
# Target rules for targets named nb

# Build rule for target.
nb: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 nb
.PHONY : nb

# fast build rule for target.
nb/fast:
	$(MAKE) -f bus/CMakeFiles/nb.dir/build.make bus/CMakeFiles/nb.dir/build
.PHONY : nb/fast

#=============================================================================
# Target rules for targets named nodebus

# Build rule for target.
nodebus: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 nodebus
.PHONY : nodebus

# fast build rule for target.
nodebus/fast:
	$(MAKE) -f bus/CMakeFiles/nodebus.dir/build.make bus/CMakeFiles/nodebus.dir/build
.PHONY : nodebus/fast

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... install"
	@echo "... install/local"
	@echo "... install/strip"
	@echo "... list_install_components"
	@echo "... rebuild_cache"
	@echo "... jsoncpp_lib_static"
	@echo "... jsoncpp_check"
	@echo "... jsoncpp_readerwriter_tests"
	@echo "... jsontestrunner_exe"
	@echo "... jsoncpp_test"
	@echo "... nb"
	@echo "... nodebus"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

