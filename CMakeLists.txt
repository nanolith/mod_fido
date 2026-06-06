cmake_minimum_required(VERSION 3.22)
cmake_policy(SET CMP0048 NEW)
PROJECT(mod_fido VERSION 0.0.1 LANGUAGES C CXX)

INCLUDE(CheckSymbolExists)

option(MODEL_CHECKING_ENABLED "Enable Model Checking")

#pkgconfig
find_package(PkgConfig REQUIRED)

#chooser helpers
SET(COMPILER_CHOOSER ${CMAKE_SOURCE_DIR}/scripts/compiler-chooser.sh)
SET(LINKER_CHOOSER ${CMAKE_SOURCE_DIR}/scripts/linker-chooser.sh)

include_directories(include)
include_directories(${CMAKE_BINARY_DIR}/include)

ADD_SUBDIRECTORY(src)

#model checks
if (MODEL_CHECKING_ENABLED)
    ADD_SUBDIRECTORY(models)
endif ()
