cmake_minimum_required(VERSION 3.20)

project(QuartzProtocol LANGUAGES CXX)

add_library(QuartzProtocol INTERFACE)
file(GLOB_RECURSE INCLUDES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp"
)

target_sources(QuartzProtocol INTERFACE
        FILE_SET HEADERS
        BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
        FILES
        ${INCLUDES}
)

target_compile_features(QuartzProtocol INTERFACE cxx_std_20)