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

# Utility rule file for wp_nav_odom_report_automoc.

# Include the progress variables for this target.
include waterplus_map_tools/CMakeFiles/wp_nav_odom_report_automoc.dir/progress.make

waterplus_map_tools/CMakeFiles/wp_nav_odom_report_automoc:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/leopord/demo_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic moc for target wp_nav_odom_report"
	cd /home/leopord/demo_ws/build/waterplus_map_tools && /usr/bin/cmake -E cmake_autogen /home/leopord/demo_ws/build/waterplus_map_tools/CMakeFiles/wp_nav_odom_report_automoc.dir/ ""

wp_nav_odom_report_automoc: waterplus_map_tools/CMakeFiles/wp_nav_odom_report_automoc
wp_nav_odom_report_automoc: waterplus_map_tools/CMakeFiles/wp_nav_odom_report_automoc.dir/build.make

.PHONY : wp_nav_odom_report_automoc

# Rule to build all files generated by this target.
waterplus_map_tools/CMakeFiles/wp_nav_odom_report_automoc.dir/build: wp_nav_odom_report_automoc

.PHONY : waterplus_map_tools/CMakeFiles/wp_nav_odom_report_automoc.dir/build

waterplus_map_tools/CMakeFiles/wp_nav_odom_report_automoc.dir/clean:
	cd /home/leopord/demo_ws/build/waterplus_map_tools && $(CMAKE_COMMAND) -P CMakeFiles/wp_nav_odom_report_automoc.dir/cmake_clean.cmake
.PHONY : waterplus_map_tools/CMakeFiles/wp_nav_odom_report_automoc.dir/clean

waterplus_map_tools/CMakeFiles/wp_nav_odom_report_automoc.dir/depend:
	cd /home/leopord/demo_ws/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/leopord/demo_ws/src /home/leopord/demo_ws/src/waterplus_map_tools /home/leopord/demo_ws/build /home/leopord/demo_ws/build/waterplus_map_tools /home/leopord/demo_ws/build/waterplus_map_tools/CMakeFiles/wp_nav_odom_report_automoc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : waterplus_map_tools/CMakeFiles/wp_nav_odom_report_automoc.dir/depend

