cmake_minimum_required(VERSION 4.3)
project(QuartzProtocol)
file(GLOB_RECURSE INCLUDES CONFIGURE_DEPENDS
        include/*.hpp
)
add_library(QuartzProtocol INTERFACE ${INCLUDES})
target_include_directories(QuartzProtocol INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(QuartzProtocol INTERFACE cxx_std_20)