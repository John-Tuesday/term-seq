cmake_minimum_required(VERSION 3.30)
project(term_seq
    VERSION 0.1.3
    LANGUAGES CXX
)

option(term_seq_enable_tests "Enable tests" "${PROJECT_IS_TOP_LEVEL}")
if("${term_seq_enable_tests}")
  include(CTest)
endif()

add_library(term_seq_interface_base INTERFACE)
add_library(TermSeq::InterfaceBase ALIAS term_seq_interface_base)
target_compile_features(term_seq_interface_base
    INTERFACE
        cxx_std_23
)

add_subdirectory(src)

if("${term_seq_enable_tests}")
  add_subdirectory(tests)
endif()
