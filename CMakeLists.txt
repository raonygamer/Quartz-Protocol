add_library(QuartzProtocol INTERFACE)

target_include_directories(QuartzProtocol INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(QuartzProtocol INTERFACE cxx_std_20)