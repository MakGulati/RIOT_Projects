# Install script for directory: /home/mayag88/Documents/Code/Arduino/RIOT_Projects/relic_bench-native/bin/pkg/native/relic

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
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
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/relic" TYPE FILE FILES
    "/home/mayag88/Documents/Code/Arduino/RIOT_Projects/relic_bench-native/bin/pkg/native/relic/include/relic.h"
    "/home/mayag88/Documents/Code/Arduino/RIOT_Projects/relic_bench-native/bin/pkg/native/relic/include/relic_alloc.h"
    "/home/mayag88/Documents/Code/Arduino/RIOT_Projects/relic_bench-native/bin/pkg/native/relic/include/relic_arch.h"
    "/home/mayag88/Documents/Code/Arduino/RIOT_Projects/relic_bench-native/bin/pkg/native/relic/include/relic_bc.h"
    "/home/mayag88/Documents/Code/Arduino/RIOT_Projects/relic_bench-native/bin/pkg/native/relic/include/relic_bench.h"
    "/home/mayag88/Documents/Code/Arduino/RIOT_Projects/relic_bench-native/bin/pkg/native/relic/include/relic_bn.h"
    "/home/mayag88/Documents/Code/Arduino/RIOT_Projects/relic_bench-native/bin/pkg/native/relic/include/relic_conf.h"
    "/home/mayag88/Documents/Code/Arduino/RIOT_Projects/relic_bench-native/bin/pkg/native/relic/include/relic_core.h"
    "/home/mayag88/Documents/Code/Arduino/RIOT_Projects/relic_bench-native/bin/pkg/native/relic/include/relic_cp.h"
    "/home/mayag88/Documents/Code/Arduino/RIOT_Projects/relic_bench-native/bin/pkg/native/relic/include/relic_dv.h"
    "/home/mayag88/Documents/Code/Arduino/RIOT_Projects/relic_bench-native/bin/pkg/native/relic/include/relic_eb.h"
    "/home/mayag88/Documents/Code/Arduino/RIOT_Projects/relic_bench-native/bin/pkg/native/relic/include/relic_ec.h"
    "/home/mayag88/Documents/Code/Arduino/RIOT_Projects/relic_bench-native/bin/pkg/native/relic/include/relic_ed.h"
    "/home/mayag88/Documents/Code/Arduino/RIOT_Projects/relic_bench-native/bin/pkg/native/relic/include/relic_ep.h"
    "/home/mayag88/Documents/Code/Arduino/RIOT_Projects/relic_bench-native/bin/pkg/native/relic/include/relic_epx.h"
    "/home/mayag88/Documents/Code/Arduino/RIOT_Projects/relic_bench-native/bin/pkg/native/relic/include/relic_err.h"
    "/home/mayag88/Documents/Code/Arduino/RIOT_Projects/relic_bench-native/bin/pkg/native/relic/include/relic_fb.h"
    "/home/mayag88/Documents/Code/Arduino/RIOT_Projects/relic_bench-native/bin/pkg/native/relic/include/relic_fbx.h"
    "/home/mayag88/Documents/Code/Arduino/RIOT_Projects/relic_bench-native/bin/pkg/native/relic/include/relic_fp.h"
    "/home/mayag88/Documents/Code/Arduino/RIOT_Projects/relic_bench-native/bin/pkg/native/relic/include/relic_fpx.h"
    "/home/mayag88/Documents/Code/Arduino/RIOT_Projects/relic_bench-native/bin/pkg/native/relic/include/relic_label.h"
    "/home/mayag88/Documents/Code/Arduino/RIOT_Projects/relic_bench-native/bin/pkg/native/relic/include/relic_md.h"
    "/home/mayag88/Documents/Code/Arduino/RIOT_Projects/relic_bench-native/bin/pkg/native/relic/include/relic_pc.h"
    "/home/mayag88/Documents/Code/Arduino/RIOT_Projects/relic_bench-native/bin/pkg/native/relic/include/relic_pp.h"
    "/home/mayag88/Documents/Code/Arduino/RIOT_Projects/relic_bench-native/bin/pkg/native/relic/include/relic_rand.h"
    "/home/mayag88/Documents/Code/Arduino/RIOT_Projects/relic_bench-native/bin/pkg/native/relic/include/relic_test.h"
    "/home/mayag88/Documents/Code/Arduino/RIOT_Projects/relic_bench-native/bin/pkg/native/relic/include/relic_types.h"
    "/home/mayag88/Documents/Code/Arduino/RIOT_Projects/relic_bench-native/bin/pkg/native/relic/include/relic_util.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/relic/low" TYPE FILE FILES
    "/home/mayag88/Documents/Code/Arduino/RIOT_Projects/relic_bench-native/bin/pkg/native/relic/include/low/relic_bn_low.h"
    "/home/mayag88/Documents/Code/Arduino/RIOT_Projects/relic_bench-native/bin/pkg/native/relic/include/low/relic_dv_low.h"
    "/home/mayag88/Documents/Code/Arduino/RIOT_Projects/relic_bench-native/bin/pkg/native/relic/include/low/relic_fb_low.h"
    "/home/mayag88/Documents/Code/Arduino/RIOT_Projects/relic_bench-native/bin/pkg/native/relic/include/low/relic_fp_low.h"
    "/home/mayag88/Documents/Code/Arduino/RIOT_Projects/relic_bench-native/bin/pkg/native/relic/include/low/relic_fpx_low.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/relic" TYPE DIRECTORY FILES "/home/mayag88/Documents/Code/Arduino/RIOT_Projects/relic_bench-native/bin/pkg/native/relic/include/")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake" TYPE FILE FILES "/home/mayag88/Documents/Code/Arduino/RIOT_Projects/relic_bench-native/bin/pkg/native/relic/cmake/relic-config.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/mayag88/Documents/Code/Arduino/RIOT_Projects/relic_bench-native/bin/pkg/native/relic/src/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/mayag88/Documents/Code/Arduino/RIOT_Projects/relic_bench-native/bin/pkg/native/relic/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
