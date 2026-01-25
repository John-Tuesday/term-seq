cmake_minimum_required(VERSION 3.30)
project(term_seq
    VERSION 0.1.2
    LANGUAGES CXX
)
include(CTest)

add_library(term_seq_interface_base INTERFACE)
add_library(TermSeq::InterfaceBase ALIAS term_seq_interface_base)
target_compile_features(term_seq_interface_base
    INTERFACE
        cxx_std_23
)

add_subdirectory(src)

add_subdirectory(tests)
