add_subdirectory(TermSeq)

cmake_path(RELATIVE_PATH CMAKE_CURRENT_BINARY_DIR
  BASE_DIRECTORY "${CMAKE_BINARY_DIR}"
  OUTPUT_VARIABLE current_generated_dir
)
cmake_path(APPEND CMAKE_BINARY_DIR generated OUTPUT_VARIABLE generated_dir)
cmake_path(APPEND generated_dir "${current_generated_dir}"
  OUTPUT_VARIABLE current_generated_dir
)

set(term_seq_amalg_path "${current_generated_dir}/TermSeq")

file(GENERATE OUTPUT "${term_seq_amalg_path}"
    CONTENT [==[
#pragma once

#ifndef TERMSEQ_TERMSEQ_HPP
#define TERMSEQ_TERMSEQ_HPP


$<JOIN:$<LIST:FILTER,$<LIST:TRANSFORM,$<PATH:RELATIVE_PATH,$<PATH:CMAKE_PATH,NORMALIZE,$<TARGET_PROPERTY:HEADER_SET>>,$<PATH:CMAKE_PATH,NORMALIZE,$<TARGET_PROPERTY:HEADER_DIRS>>>,REPLACE,(^.+$),#include <\1$<ANGLE-R>\n>,EXCLUDE,private/.*>,>

#endif
]==]
    TARGET term_seq_core
)
set_source_files_properties("${term_seq_amalg_path}" PROPERTIES
    GENERATED ON
)
add_custom_target(term_seq_gen_amalgation DEPENDS "${term_seq_amalg_path}")

add_library(term_seq_amalg INTERFACE)
add_library("TermSeq::TermSeq" ALIAS term_seq_amalg)
target_link_libraries(term_seq_amalg
  INTERFACE
    TermSeq::Core
)
target_sources(term_seq_amalg
  PUBLIC FILE_SET HEADERS
  BASE_DIRS
    "${current_generated_dir}"
  FILES
    "${term_seq_amalg_path}"
)

