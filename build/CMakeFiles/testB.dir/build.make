# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.28.3/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.28.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/build

# Include any dependencies generated for this target.
include CMakeFiles/testB.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/testB.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/testB.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/testB.dir/flags.make

CMakeFiles/testB.dir/_tests/_test_files/testB.cpp.o: CMakeFiles/testB.dir/flags.make
CMakeFiles/testB.dir/_tests/_test_files/testB.cpp.o: /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/_tests/_test_files/testB.cpp
CMakeFiles/testB.dir/_tests/_test_files/testB.cpp.o: CMakeFiles/testB.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/testB.dir/_tests/_test_files/testB.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/testB.dir/_tests/_test_files/testB.cpp.o -MF CMakeFiles/testB.dir/_tests/_test_files/testB.cpp.o.d -o CMakeFiles/testB.dir/_tests/_test_files/testB.cpp.o -c /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/_tests/_test_files/testB.cpp

CMakeFiles/testB.dir/_tests/_test_files/testB.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/testB.dir/_tests/_test_files/testB.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/_tests/_test_files/testB.cpp > CMakeFiles/testB.dir/_tests/_test_files/testB.cpp.i

CMakeFiles/testB.dir/_tests/_test_files/testB.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/testB.dir/_tests/_test_files/testB.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/_tests/_test_files/testB.cpp -o CMakeFiles/testB.dir/_tests/_test_files/testB.cpp.s

CMakeFiles/testB.dir/includes/binary_files/file_record.cpp.o: CMakeFiles/testB.dir/flags.make
CMakeFiles/testB.dir/includes/binary_files/file_record.cpp.o: /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/includes/binary_files/file_record.cpp
CMakeFiles/testB.dir/includes/binary_files/file_record.cpp.o: CMakeFiles/testB.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/testB.dir/includes/binary_files/file_record.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/testB.dir/includes/binary_files/file_record.cpp.o -MF CMakeFiles/testB.dir/includes/binary_files/file_record.cpp.o.d -o CMakeFiles/testB.dir/includes/binary_files/file_record.cpp.o -c /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/includes/binary_files/file_record.cpp

CMakeFiles/testB.dir/includes/binary_files/file_record.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/testB.dir/includes/binary_files/file_record.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/includes/binary_files/file_record.cpp > CMakeFiles/testB.dir/includes/binary_files/file_record.cpp.i

CMakeFiles/testB.dir/includes/binary_files/file_record.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/testB.dir/includes/binary_files/file_record.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/includes/binary_files/file_record.cpp -o CMakeFiles/testB.dir/includes/binary_files/file_record.cpp.s

CMakeFiles/testB.dir/includes/binary_files/utilities.cpp.o: CMakeFiles/testB.dir/flags.make
CMakeFiles/testB.dir/includes/binary_files/utilities.cpp.o: /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/includes/binary_files/utilities.cpp
CMakeFiles/testB.dir/includes/binary_files/utilities.cpp.o: CMakeFiles/testB.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/testB.dir/includes/binary_files/utilities.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/testB.dir/includes/binary_files/utilities.cpp.o -MF CMakeFiles/testB.dir/includes/binary_files/utilities.cpp.o.d -o CMakeFiles/testB.dir/includes/binary_files/utilities.cpp.o -c /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/includes/binary_files/utilities.cpp

CMakeFiles/testB.dir/includes/binary_files/utilities.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/testB.dir/includes/binary_files/utilities.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/includes/binary_files/utilities.cpp > CMakeFiles/testB.dir/includes/binary_files/utilities.cpp.i

CMakeFiles/testB.dir/includes/binary_files/utilities.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/testB.dir/includes/binary_files/utilities.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/includes/binary_files/utilities.cpp -o CMakeFiles/testB.dir/includes/binary_files/utilities.cpp.s

CMakeFiles/testB.dir/includes/parser/parser.cpp.o: CMakeFiles/testB.dir/flags.make
CMakeFiles/testB.dir/includes/parser/parser.cpp.o: /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/includes/parser/parser.cpp
CMakeFiles/testB.dir/includes/parser/parser.cpp.o: CMakeFiles/testB.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/testB.dir/includes/parser/parser.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/testB.dir/includes/parser/parser.cpp.o -MF CMakeFiles/testB.dir/includes/parser/parser.cpp.o.d -o CMakeFiles/testB.dir/includes/parser/parser.cpp.o -c /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/includes/parser/parser.cpp

CMakeFiles/testB.dir/includes/parser/parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/testB.dir/includes/parser/parser.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/includes/parser/parser.cpp > CMakeFiles/testB.dir/includes/parser/parser.cpp.i

CMakeFiles/testB.dir/includes/parser/parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/testB.dir/includes/parser/parser.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/includes/parser/parser.cpp -o CMakeFiles/testB.dir/includes/parser/parser.cpp.s

CMakeFiles/testB.dir/includes/stub/stub.cpp.o: CMakeFiles/testB.dir/flags.make
CMakeFiles/testB.dir/includes/stub/stub.cpp.o: /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/includes/stub/stub.cpp
CMakeFiles/testB.dir/includes/stub/stub.cpp.o: CMakeFiles/testB.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/testB.dir/includes/stub/stub.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/testB.dir/includes/stub/stub.cpp.o -MF CMakeFiles/testB.dir/includes/stub/stub.cpp.o.d -o CMakeFiles/testB.dir/includes/stub/stub.cpp.o -c /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/includes/stub/stub.cpp

CMakeFiles/testB.dir/includes/stub/stub.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/testB.dir/includes/stub/stub.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/includes/stub/stub.cpp > CMakeFiles/testB.dir/includes/stub/stub.cpp.i

CMakeFiles/testB.dir/includes/stub/stub.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/testB.dir/includes/stub/stub.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/includes/stub/stub.cpp -o CMakeFiles/testB.dir/includes/stub/stub.cpp.s

CMakeFiles/testB.dir/includes/table/table.cpp.o: CMakeFiles/testB.dir/flags.make
CMakeFiles/testB.dir/includes/table/table.cpp.o: /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/includes/table/table.cpp
CMakeFiles/testB.dir/includes/table/table.cpp.o: CMakeFiles/testB.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/testB.dir/includes/table/table.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/testB.dir/includes/table/table.cpp.o -MF CMakeFiles/testB.dir/includes/table/table.cpp.o.d -o CMakeFiles/testB.dir/includes/table/table.cpp.o -c /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/includes/table/table.cpp

CMakeFiles/testB.dir/includes/table/table.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/testB.dir/includes/table/table.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/includes/table/table.cpp > CMakeFiles/testB.dir/includes/table/table.cpp.i

CMakeFiles/testB.dir/includes/table/table.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/testB.dir/includes/table/table.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/includes/table/table.cpp -o CMakeFiles/testB.dir/includes/table/table.cpp.s

CMakeFiles/testB.dir/includes/token/token.cpp.o: CMakeFiles/testB.dir/flags.make
CMakeFiles/testB.dir/includes/token/token.cpp.o: /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/includes/token/token.cpp
CMakeFiles/testB.dir/includes/token/token.cpp.o: CMakeFiles/testB.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/testB.dir/includes/token/token.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/testB.dir/includes/token/token.cpp.o -MF CMakeFiles/testB.dir/includes/token/token.cpp.o.d -o CMakeFiles/testB.dir/includes/token/token.cpp.o -c /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/includes/token/token.cpp

CMakeFiles/testB.dir/includes/token/token.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/testB.dir/includes/token/token.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/includes/token/token.cpp > CMakeFiles/testB.dir/includes/token/token.cpp.i

CMakeFiles/testB.dir/includes/token/token.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/testB.dir/includes/token/token.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/includes/token/token.cpp -o CMakeFiles/testB.dir/includes/token/token.cpp.s

CMakeFiles/testB.dir/includes/tokenizer/ftokenize.cpp.o: CMakeFiles/testB.dir/flags.make
CMakeFiles/testB.dir/includes/tokenizer/ftokenize.cpp.o: /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/includes/tokenizer/ftokenize.cpp
CMakeFiles/testB.dir/includes/tokenizer/ftokenize.cpp.o: CMakeFiles/testB.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/testB.dir/includes/tokenizer/ftokenize.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/testB.dir/includes/tokenizer/ftokenize.cpp.o -MF CMakeFiles/testB.dir/includes/tokenizer/ftokenize.cpp.o.d -o CMakeFiles/testB.dir/includes/tokenizer/ftokenize.cpp.o -c /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/includes/tokenizer/ftokenize.cpp

CMakeFiles/testB.dir/includes/tokenizer/ftokenize.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/testB.dir/includes/tokenizer/ftokenize.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/includes/tokenizer/ftokenize.cpp > CMakeFiles/testB.dir/includes/tokenizer/ftokenize.cpp.i

CMakeFiles/testB.dir/includes/tokenizer/ftokenize.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/testB.dir/includes/tokenizer/ftokenize.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/includes/tokenizer/ftokenize.cpp -o CMakeFiles/testB.dir/includes/tokenizer/ftokenize.cpp.s

CMakeFiles/testB.dir/includes/tokenizer/state_machine_functions.cpp.o: CMakeFiles/testB.dir/flags.make
CMakeFiles/testB.dir/includes/tokenizer/state_machine_functions.cpp.o: /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/includes/tokenizer/state_machine_functions.cpp
CMakeFiles/testB.dir/includes/tokenizer/state_machine_functions.cpp.o: CMakeFiles/testB.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/testB.dir/includes/tokenizer/state_machine_functions.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/testB.dir/includes/tokenizer/state_machine_functions.cpp.o -MF CMakeFiles/testB.dir/includes/tokenizer/state_machine_functions.cpp.o.d -o CMakeFiles/testB.dir/includes/tokenizer/state_machine_functions.cpp.o -c /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/includes/tokenizer/state_machine_functions.cpp

CMakeFiles/testB.dir/includes/tokenizer/state_machine_functions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/testB.dir/includes/tokenizer/state_machine_functions.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/includes/tokenizer/state_machine_functions.cpp > CMakeFiles/testB.dir/includes/tokenizer/state_machine_functions.cpp.i

CMakeFiles/testB.dir/includes/tokenizer/state_machine_functions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/testB.dir/includes/tokenizer/state_machine_functions.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/includes/tokenizer/state_machine_functions.cpp -o CMakeFiles/testB.dir/includes/tokenizer/state_machine_functions.cpp.s

CMakeFiles/testB.dir/includes/tokenizer/stokenize.cpp.o: CMakeFiles/testB.dir/flags.make
CMakeFiles/testB.dir/includes/tokenizer/stokenize.cpp.o: /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/includes/tokenizer/stokenize.cpp
CMakeFiles/testB.dir/includes/tokenizer/stokenize.cpp.o: CMakeFiles/testB.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/testB.dir/includes/tokenizer/stokenize.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/testB.dir/includes/tokenizer/stokenize.cpp.o -MF CMakeFiles/testB.dir/includes/tokenizer/stokenize.cpp.o.d -o CMakeFiles/testB.dir/includes/tokenizer/stokenize.cpp.o -c /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/includes/tokenizer/stokenize.cpp

CMakeFiles/testB.dir/includes/tokenizer/stokenize.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/testB.dir/includes/tokenizer/stokenize.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/includes/tokenizer/stokenize.cpp > CMakeFiles/testB.dir/includes/tokenizer/stokenize.cpp.i

CMakeFiles/testB.dir/includes/tokenizer/stokenize.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/testB.dir/includes/tokenizer/stokenize.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/includes/tokenizer/stokenize.cpp -o CMakeFiles/testB.dir/includes/tokenizer/stokenize.cpp.s

CMakeFiles/testB.dir/includes/tokenizer/token.cpp.o: CMakeFiles/testB.dir/flags.make
CMakeFiles/testB.dir/includes/tokenizer/token.cpp.o: /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/includes/tokenizer/token.cpp
CMakeFiles/testB.dir/includes/tokenizer/token.cpp.o: CMakeFiles/testB.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/testB.dir/includes/tokenizer/token.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/testB.dir/includes/tokenizer/token.cpp.o -MF CMakeFiles/testB.dir/includes/tokenizer/token.cpp.o.d -o CMakeFiles/testB.dir/includes/tokenizer/token.cpp.o -c /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/includes/tokenizer/token.cpp

CMakeFiles/testB.dir/includes/tokenizer/token.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/testB.dir/includes/tokenizer/token.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/includes/tokenizer/token.cpp > CMakeFiles/testB.dir/includes/tokenizer/token.cpp.i

CMakeFiles/testB.dir/includes/tokenizer/token.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/testB.dir/includes/tokenizer/token.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/includes/tokenizer/token.cpp -o CMakeFiles/testB.dir/includes/tokenizer/token.cpp.s

# Object files for target testB
testB_OBJECTS = \
"CMakeFiles/testB.dir/_tests/_test_files/testB.cpp.o" \
"CMakeFiles/testB.dir/includes/binary_files/file_record.cpp.o" \
"CMakeFiles/testB.dir/includes/binary_files/utilities.cpp.o" \
"CMakeFiles/testB.dir/includes/parser/parser.cpp.o" \
"CMakeFiles/testB.dir/includes/stub/stub.cpp.o" \
"CMakeFiles/testB.dir/includes/table/table.cpp.o" \
"CMakeFiles/testB.dir/includes/token/token.cpp.o" \
"CMakeFiles/testB.dir/includes/tokenizer/ftokenize.cpp.o" \
"CMakeFiles/testB.dir/includes/tokenizer/state_machine_functions.cpp.o" \
"CMakeFiles/testB.dir/includes/tokenizer/stokenize.cpp.o" \
"CMakeFiles/testB.dir/includes/tokenizer/token.cpp.o"

# External object files for target testB
testB_EXTERNAL_OBJECTS =

bin/testB: CMakeFiles/testB.dir/_tests/_test_files/testB.cpp.o
bin/testB: CMakeFiles/testB.dir/includes/binary_files/file_record.cpp.o
bin/testB: CMakeFiles/testB.dir/includes/binary_files/utilities.cpp.o
bin/testB: CMakeFiles/testB.dir/includes/parser/parser.cpp.o
bin/testB: CMakeFiles/testB.dir/includes/stub/stub.cpp.o
bin/testB: CMakeFiles/testB.dir/includes/table/table.cpp.o
bin/testB: CMakeFiles/testB.dir/includes/token/token.cpp.o
bin/testB: CMakeFiles/testB.dir/includes/tokenizer/ftokenize.cpp.o
bin/testB: CMakeFiles/testB.dir/includes/tokenizer/state_machine_functions.cpp.o
bin/testB: CMakeFiles/testB.dir/includes/tokenizer/stokenize.cpp.o
bin/testB: CMakeFiles/testB.dir/includes/tokenizer/token.cpp.o
bin/testB: CMakeFiles/testB.dir/build.make
bin/testB: lib/libgtestd.a
bin/testB: CMakeFiles/testB.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking CXX executable bin/testB"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testB.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/testB.dir/build: bin/testB
.PHONY : CMakeFiles/testB.dir/build

CMakeFiles/testB.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/testB.dir/cmake_clean.cmake
.PHONY : CMakeFiles/testB.dir/clean

CMakeFiles/testB.dir/depend:
	cd /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5 /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5 /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/build /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/build /Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/build/CMakeFiles/testB.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/testB.dir/depend

