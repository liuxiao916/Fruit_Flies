# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /home/jf/CLion-2019.2.5/clion-2019.2.5/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/jf/CLion-2019.2.5/clion-2019.2.5/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jf/Fruit/Fruit_Flies/fly_state_new

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jf/Fruit/Fruit_Flies/fly_state_new/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/fly_state_new.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/fly_state_new.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/fly_state_new.dir/flags.make

CMakeFiles/fly_state_new.dir/main.cpp.o: CMakeFiles/fly_state_new.dir/flags.make
CMakeFiles/fly_state_new.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jf/Fruit/Fruit_Flies/fly_state_new/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/fly_state_new.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fly_state_new.dir/main.cpp.o -c /home/jf/Fruit/Fruit_Flies/fly_state_new/main.cpp

CMakeFiles/fly_state_new.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fly_state_new.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jf/Fruit/Fruit_Flies/fly_state_new/main.cpp > CMakeFiles/fly_state_new.dir/main.cpp.i

CMakeFiles/fly_state_new.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fly_state_new.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jf/Fruit/Fruit_Flies/fly_state_new/main.cpp -o CMakeFiles/fly_state_new.dir/main.cpp.s

CMakeFiles/fly_state_new.dir/state.cpp.o: CMakeFiles/fly_state_new.dir/flags.make
CMakeFiles/fly_state_new.dir/state.cpp.o: ../state.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jf/Fruit/Fruit_Flies/fly_state_new/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/fly_state_new.dir/state.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fly_state_new.dir/state.cpp.o -c /home/jf/Fruit/Fruit_Flies/fly_state_new/state.cpp

CMakeFiles/fly_state_new.dir/state.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fly_state_new.dir/state.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jf/Fruit/Fruit_Flies/fly_state_new/state.cpp > CMakeFiles/fly_state_new.dir/state.cpp.i

CMakeFiles/fly_state_new.dir/state.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fly_state_new.dir/state.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jf/Fruit/Fruit_Flies/fly_state_new/state.cpp -o CMakeFiles/fly_state_new.dir/state.cpp.s

CMakeFiles/fly_state_new.dir/board.cpp.o: CMakeFiles/fly_state_new.dir/flags.make
CMakeFiles/fly_state_new.dir/board.cpp.o: ../board.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jf/Fruit/Fruit_Flies/fly_state_new/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/fly_state_new.dir/board.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fly_state_new.dir/board.cpp.o -c /home/jf/Fruit/Fruit_Flies/fly_state_new/board.cpp

CMakeFiles/fly_state_new.dir/board.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fly_state_new.dir/board.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jf/Fruit/Fruit_Flies/fly_state_new/board.cpp > CMakeFiles/fly_state_new.dir/board.cpp.i

CMakeFiles/fly_state_new.dir/board.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fly_state_new.dir/board.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jf/Fruit/Fruit_Flies/fly_state_new/board.cpp -o CMakeFiles/fly_state_new.dir/board.cpp.s

# Object files for target fly_state_new
fly_state_new_OBJECTS = \
"CMakeFiles/fly_state_new.dir/main.cpp.o" \
"CMakeFiles/fly_state_new.dir/state.cpp.o" \
"CMakeFiles/fly_state_new.dir/board.cpp.o"

# External object files for target fly_state_new
fly_state_new_EXTERNAL_OBJECTS =

fly_state_new: CMakeFiles/fly_state_new.dir/main.cpp.o
fly_state_new: CMakeFiles/fly_state_new.dir/state.cpp.o
fly_state_new: CMakeFiles/fly_state_new.dir/board.cpp.o
fly_state_new: CMakeFiles/fly_state_new.dir/build.make
fly_state_new: /usr/local/lib/libopencv_stitching.so.3.4.13
fly_state_new: /usr/local/lib/libopencv_superres.so.3.4.13
fly_state_new: /usr/local/lib/libopencv_videostab.so.3.4.13
fly_state_new: /usr/local/lib/libopencv_aruco.so.3.4.13
fly_state_new: /usr/local/lib/libopencv_bgsegm.so.3.4.13
fly_state_new: /usr/local/lib/libopencv_bioinspired.so.3.4.13
fly_state_new: /usr/local/lib/libopencv_ccalib.so.3.4.13
fly_state_new: /usr/local/lib/libopencv_dnn_objdetect.so.3.4.13
fly_state_new: /usr/local/lib/libopencv_dpm.so.3.4.13
fly_state_new: /usr/local/lib/libopencv_face.so.3.4.13
fly_state_new: /usr/local/lib/libopencv_freetype.so.3.4.13
fly_state_new: /usr/local/lib/libopencv_fuzzy.so.3.4.13
fly_state_new: /usr/local/lib/libopencv_hdf.so.3.4.13
fly_state_new: /usr/local/lib/libopencv_hfs.so.3.4.13
fly_state_new: /usr/local/lib/libopencv_img_hash.so.3.4.13
fly_state_new: /usr/local/lib/libopencv_line_descriptor.so.3.4.13
fly_state_new: /usr/local/lib/libopencv_optflow.so.3.4.13
fly_state_new: /usr/local/lib/libopencv_reg.so.3.4.13
fly_state_new: /usr/local/lib/libopencv_rgbd.so.3.4.13
fly_state_new: /usr/local/lib/libopencv_saliency.so.3.4.13
fly_state_new: /usr/local/lib/libopencv_stereo.so.3.4.13
fly_state_new: /usr/local/lib/libopencv_structured_light.so.3.4.13
fly_state_new: /usr/local/lib/libopencv_surface_matching.so.3.4.13
fly_state_new: /usr/local/lib/libopencv_tracking.so.3.4.13
fly_state_new: /usr/local/lib/libopencv_xfeatures2d.so.3.4.13
fly_state_new: /usr/local/lib/libopencv_ximgproc.so.3.4.13
fly_state_new: /usr/local/lib/libopencv_xobjdetect.so.3.4.13
fly_state_new: /usr/local/lib/libopencv_xphoto.so.3.4.13
fly_state_new: /usr/local/lib/libopencv_shape.so.3.4.13
fly_state_new: /usr/local/lib/libopencv_highgui.so.3.4.13
fly_state_new: /usr/local/lib/libopencv_videoio.so.3.4.13
fly_state_new: /usr/local/lib/libopencv_viz.so.3.4.13
fly_state_new: /usr/local/lib/libopencv_phase_unwrapping.so.3.4.13
fly_state_new: /usr/local/lib/libopencv_video.so.3.4.13
fly_state_new: /usr/local/lib/libopencv_datasets.so.3.4.13
fly_state_new: /usr/local/lib/libopencv_plot.so.3.4.13
fly_state_new: /usr/local/lib/libopencv_text.so.3.4.13
fly_state_new: /usr/local/lib/libopencv_dnn.so.3.4.13
fly_state_new: /usr/local/lib/libopencv_ml.so.3.4.13
fly_state_new: /usr/local/lib/libopencv_imgcodecs.so.3.4.13
fly_state_new: /usr/local/lib/libopencv_objdetect.so.3.4.13
fly_state_new: /usr/local/lib/libopencv_calib3d.so.3.4.13
fly_state_new: /usr/local/lib/libopencv_features2d.so.3.4.13
fly_state_new: /usr/local/lib/libopencv_flann.so.3.4.13
fly_state_new: /usr/local/lib/libopencv_photo.so.3.4.13
fly_state_new: /usr/local/lib/libopencv_imgproc.so.3.4.13
fly_state_new: /usr/local/lib/libopencv_core.so.3.4.13
fly_state_new: CMakeFiles/fly_state_new.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jf/Fruit/Fruit_Flies/fly_state_new/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable fly_state_new"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/fly_state_new.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/fly_state_new.dir/build: fly_state_new

.PHONY : CMakeFiles/fly_state_new.dir/build

CMakeFiles/fly_state_new.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/fly_state_new.dir/cmake_clean.cmake
.PHONY : CMakeFiles/fly_state_new.dir/clean

CMakeFiles/fly_state_new.dir/depend:
	cd /home/jf/Fruit/Fruit_Flies/fly_state_new/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jf/Fruit/Fruit_Flies/fly_state_new /home/jf/Fruit/Fruit_Flies/fly_state_new /home/jf/Fruit/Fruit_Flies/fly_state_new/cmake-build-debug /home/jf/Fruit/Fruit_Flies/fly_state_new/cmake-build-debug /home/jf/Fruit/Fruit_Flies/fly_state_new/cmake-build-debug/CMakeFiles/fly_state_new.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/fly_state_new.dir/depend

