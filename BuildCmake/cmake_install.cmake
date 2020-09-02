# Install script for directory: E:/Users/Dan/Downloads/Git/Algorithms

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "E:/Program Files (x86)/Algorithms")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("E:/Users/Dan/Downloads/Git/Algorithms/BuildCmake/LibraryC/cmake_install.cmake")
  include("E:/Users/Dan/Downloads/Git/Algorithms/BuildCmake/LibraryCPP/cmake_install.cmake")
  include("E:/Users/Dan/Downloads/Git/Algorithms/BuildCmake/TestArrayC/cmake_install.cmake")
  include("E:/Users/Dan/Downloads/Git/Algorithms/BuildCmake/TestListC/cmake_install.cmake")
  include("E:/Users/Dan/Downloads/Git/Algorithms/BuildCmake/TestQueueC/cmake_install.cmake")
  include("E:/Users/Dan/Downloads/Git/Algorithms/BuildCmake/TestStackC/cmake_install.cmake")
  include("E:/Users/Dan/Downloads/Git/Algorithms/BuildCmake/TestVectorC/cmake_install.cmake")
  include("E:/Users/Dan/Downloads/Git/Algorithms/BuildCmake/TestArrayCPP/cmake_install.cmake")
  include("E:/Users/Dan/Downloads/Git/Algorithms/BuildCmake/TestArrayCPPTemplate/cmake_install.cmake")
  include("E:/Users/Dan/Downloads/Git/Algorithms/BuildCmake/NewMainFolder/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "E:/Users/Dan/Downloads/Git/Algorithms/BuildCmake/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
