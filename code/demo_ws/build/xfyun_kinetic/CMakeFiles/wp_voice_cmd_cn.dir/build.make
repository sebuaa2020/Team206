# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_SOURCE_DIR = /home/leopord/demo_ws/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/leopord/demo_ws/build

# Include any dependencies generated for this target.
include xfyun_kinetic/CMakeFiles/wp_voice_cmd_cn.dir/depend.make

# Include the progress variables for this target.
include xfyun_kinetic/CMakeFiles/wp_voice_cmd_cn.dir/progress.make

# Include the compile flags for this target's objects.
include xfyun_kinetic/CMakeFiles/wp_voice_cmd_cn.dir/flags.make

xfyun_kinetic/CMakeFiles/wp_voice_cmd_cn.dir/src/wp_voice_cmd_cn.cpp.o: xfyun_kinetic/CMakeFiles/wp_voice_cmd_cn.dir/flags.make
xfyun_kinetic/CMakeFiles/wp_voice_cmd_cn.dir/src/wp_voice_cmd_cn.cpp.o: /home/leopord/demo_ws/src/xfyun_kinetic/src/wp_voice_cmd_cn.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/leopord/demo_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object xfyun_kinetic/CMakeFiles/wp_voice_cmd_cn.dir/src/wp_voice_cmd_cn.cpp.o"
	cd /home/leopord/demo_ws/build/xfyun_kinetic && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/wp_voice_cmd_cn.dir/src/wp_voice_cmd_cn.cpp.o -c /home/leopord/demo_ws/src/xfyun_kinetic/src/wp_voice_cmd_cn.cpp

xfyun_kinetic/CMakeFiles/wp_voice_cmd_cn.dir/src/wp_voice_cmd_cn.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wp_voice_cmd_cn.dir/src/wp_voice_cmd_cn.cpp.i"
	cd /home/leopord/demo_ws/build/xfyun_kinetic && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/leopord/demo_ws/src/xfyun_kinetic/src/wp_voice_cmd_cn.cpp > CMakeFiles/wp_voice_cmd_cn.dir/src/wp_voice_cmd_cn.cpp.i

xfyun_kinetic/CMakeFiles/wp_voice_cmd_cn.dir/src/wp_voice_cmd_cn.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wp_voice_cmd_cn.dir/src/wp_voice_cmd_cn.cpp.s"
	cd /home/leopord/demo_ws/build/xfyun_kinetic && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/leopord/demo_ws/src/xfyun_kinetic/src/wp_voice_cmd_cn.cpp -o CMakeFiles/wp_voice_cmd_cn.dir/src/wp_voice_cmd_cn.cpp.s

xfyun_kinetic/CMakeFiles/wp_voice_cmd_cn.dir/src/wp_voice_cmd_cn.cpp.o.requires:

.PHONY : xfyun_kinetic/CMakeFiles/wp_voice_cmd_cn.dir/src/wp_voice_cmd_cn.cpp.o.requires

xfyun_kinetic/CMakeFiles/wp_voice_cmd_cn.dir/src/wp_voice_cmd_cn.cpp.o.provides: xfyun_kinetic/CMakeFiles/wp_voice_cmd_cn.dir/src/wp_voice_cmd_cn.cpp.o.requires
	$(MAKE) -f xfyun_kinetic/CMakeFiles/wp_voice_cmd_cn.dir/build.make xfyun_kinetic/CMakeFiles/wp_voice_cmd_cn.dir/src/wp_voice_cmd_cn.cpp.o.provides.build
.PHONY : xfyun_kinetic/CMakeFiles/wp_voice_cmd_cn.dir/src/wp_voice_cmd_cn.cpp.o.provides

xfyun_kinetic/CMakeFiles/wp_voice_cmd_cn.dir/src/wp_voice_cmd_cn.cpp.o.provides.build: xfyun_kinetic/CMakeFiles/wp_voice_cmd_cn.dir/src/wp_voice_cmd_cn.cpp.o


# Object files for target wp_voice_cmd_cn
wp_voice_cmd_cn_OBJECTS = \
"CMakeFiles/wp_voice_cmd_cn.dir/src/wp_voice_cmd_cn.cpp.o"

# External object files for target wp_voice_cmd_cn
wp_voice_cmd_cn_EXTERNAL_OBJECTS =

/home/leopord/demo_ws/devel/lib/xfyun_waterplus/wp_voice_cmd_cn: xfyun_kinetic/CMakeFiles/wp_voice_cmd_cn.dir/src/wp_voice_cmd_cn.cpp.o
/home/leopord/demo_ws/devel/lib/xfyun_waterplus/wp_voice_cmd_cn: xfyun_kinetic/CMakeFiles/wp_voice_cmd_cn.dir/build.make
/home/leopord/demo_ws/devel/lib/xfyun_waterplus/wp_voice_cmd_cn: /opt/ros/kinetic/lib/libroscpp.so
/home/leopord/demo_ws/devel/lib/xfyun_waterplus/wp_voice_cmd_cn: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
/home/leopord/demo_ws/devel/lib/xfyun_waterplus/wp_voice_cmd_cn: /usr/lib/x86_64-linux-gnu/libboost_signals.so
/home/leopord/demo_ws/devel/lib/xfyun_waterplus/wp_voice_cmd_cn: /opt/ros/kinetic/lib/librosconsole.so
/home/leopord/demo_ws/devel/lib/xfyun_waterplus/wp_voice_cmd_cn: /opt/ros/kinetic/lib/librosconsole_log4cxx.so
/home/leopord/demo_ws/devel/lib/xfyun_waterplus/wp_voice_cmd_cn: /opt/ros/kinetic/lib/librosconsole_backend_interface.so
/home/leopord/demo_ws/devel/lib/xfyun_waterplus/wp_voice_cmd_cn: /usr/lib/x86_64-linux-gnu/liblog4cxx.so
/home/leopord/demo_ws/devel/lib/xfyun_waterplus/wp_voice_cmd_cn: /usr/lib/x86_64-linux-gnu/libboost_regex.so
/home/leopord/demo_ws/devel/lib/xfyun_waterplus/wp_voice_cmd_cn: /opt/ros/kinetic/lib/libxmlrpcpp.so
/home/leopord/demo_ws/devel/lib/xfyun_waterplus/wp_voice_cmd_cn: /opt/ros/kinetic/lib/libroscpp_serialization.so
/home/leopord/demo_ws/devel/lib/xfyun_waterplus/wp_voice_cmd_cn: /opt/ros/kinetic/lib/librostime.so
/home/leopord/demo_ws/devel/lib/xfyun_waterplus/wp_voice_cmd_cn: /opt/ros/kinetic/lib/libcpp_common.so
/home/leopord/demo_ws/devel/lib/xfyun_waterplus/wp_voice_cmd_cn: /usr/lib/x86_64-linux-gnu/libboost_system.so
/home/leopord/demo_ws/devel/lib/xfyun_waterplus/wp_voice_cmd_cn: /usr/lib/x86_64-linux-gnu/libboost_thread.so
/home/leopord/demo_ws/devel/lib/xfyun_waterplus/wp_voice_cmd_cn: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
/home/leopord/demo_ws/devel/lib/xfyun_waterplus/wp_voice_cmd_cn: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
/home/leopord/demo_ws/devel/lib/xfyun_waterplus/wp_voice_cmd_cn: /usr/lib/x86_64-linux-gnu/libboost_atomic.so
/home/leopord/demo_ws/devel/lib/xfyun_waterplus/wp_voice_cmd_cn: /usr/lib/x86_64-linux-gnu/libpthread.so
/home/leopord/demo_ws/devel/lib/xfyun_waterplus/wp_voice_cmd_cn: /usr/lib/x86_64-linux-gnu/libconsole_bridge.so
/home/leopord/demo_ws/devel/lib/xfyun_waterplus/wp_voice_cmd_cn: xfyun_kinetic/CMakeFiles/wp_voice_cmd_cn.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/leopord/demo_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /home/leopord/demo_ws/devel/lib/xfyun_waterplus/wp_voice_cmd_cn"
	cd /home/leopord/demo_ws/build/xfyun_kinetic && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/wp_voice_cmd_cn.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
xfyun_kinetic/CMakeFiles/wp_voice_cmd_cn.dir/build: /home/leopord/demo_ws/devel/lib/xfyun_waterplus/wp_voice_cmd_cn

.PHONY : xfyun_kinetic/CMakeFiles/wp_voice_cmd_cn.dir/build

xfyun_kinetic/CMakeFiles/wp_voice_cmd_cn.dir/requires: xfyun_kinetic/CMakeFiles/wp_voice_cmd_cn.dir/src/wp_voice_cmd_cn.cpp.o.requires

.PHONY : xfyun_kinetic/CMakeFiles/wp_voice_cmd_cn.dir/requires

xfyun_kinetic/CMakeFiles/wp_voice_cmd_cn.dir/clean:
	cd /home/leopord/demo_ws/build/xfyun_kinetic && $(CMAKE_COMMAND) -P CMakeFiles/wp_voice_cmd_cn.dir/cmake_clean.cmake
.PHONY : xfyun_kinetic/CMakeFiles/wp_voice_cmd_cn.dir/clean

xfyun_kinetic/CMakeFiles/wp_voice_cmd_cn.dir/depend:
	cd /home/leopord/demo_ws/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/leopord/demo_ws/src /home/leopord/demo_ws/src/xfyun_kinetic /home/leopord/demo_ws/build /home/leopord/demo_ws/build/xfyun_kinetic /home/leopord/demo_ws/build/xfyun_kinetic/CMakeFiles/wp_voice_cmd_cn.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : xfyun_kinetic/CMakeFiles/wp_voice_cmd_cn.dir/depend

