# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/build/_deps/googletest-src"
  "/Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/build/_deps/googletest-build"
  "/Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/build/_deps/googletest-subbuild/googletest-populate-prefix"
  "/Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/build/_deps/googletest-subbuild/googletest-populate-prefix/tmp"
  "/Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
  "/Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/build/_deps/googletest-subbuild/googletest-populate-prefix/src"
  "/Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/michaelmansour/Documents/CS008_PCC/Final_Project/99_99_final_project-Michael-Mansour5/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
