add_library(term_seq_sgr INTERFACE)
add_library("TermSeq::TermSeq" ALIAS term_seq_sgr)
target_link_libraries(term_seq_sgr
    INTERFACE
        TermSeq::InterfaceBase
)
target_sources(term_seq_sgr
    PUBLIC FILE_SET HEADERS
    FILES
        TermSeq/Sgr.hpp
        TermSeq/SgrColor.hpp
        TermSeq/constants.hpp
        TermSeq/ControlSequence.hpp
        TermSeq/StaticString.hpp
        TermSeq/detection.hpp
        TermSeq/private/detection_posix.hpp
    PUBLIC FILE_SET amalag_header TYPE HEADERS
    BASE_DIRS "${CMAKE_CURRENT_BINARY_DIR}/generated"
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/generated/TermSeq"
)
set_target_properties(term_seq_sgr PROPERTIES
        TRANSITIVE_COMPILE_PROPERTIES "TermSeq_enable_posix_term_detection"
        TRANSITIVE_LINK_PROPERTIES "TermSeq_enable_posix_term_detection"
)

block(SCOPE_FOR VARIABLES)
    set(posix_term_detect
        "$<TARGET_PROPERTY:TermSeq_enable_posix_term_detection>"
    )
    set(prop_unset
        "$<STREQUAL:,${posix_term_detect}>"
    )
    set(posix_term_detect
        "$<GENEX_EVAL:${posix_term_detect}>"
    )
    set(posix_term_detect
        "$<BOOL:${posix_term_detect}>"
    )
    target_compile_definitions(term_seq_sgr
        INTERFACE
            "$<$<NOT:${prop_unset}>:TERMSEQ_ENABLE_POSIX_TERM_DETECTION=${posix_term_detect}>"
    )
endblock()

file(GENERATE OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/generated/TermSeq"
    CONTENT [==[
#pragma once

#ifndef TERMSEQ_TERMSEQ_HPP
#define TERMSEQ_TERMSEQ_HPP


$<JOIN:$<LIST:FILTER,$<LIST:TRANSFORM,$<PATH:RELATIVE_PATH,$<PATH:CMAKE_PATH,NORMALIZE,$<TARGET_PROPERTY:HEADER_SET>>,$<PATH:CMAKE_PATH,NORMALIZE,$<TARGET_PROPERTY:HEADER_DIRS>>>,REPLACE,(^.+$),#include <\1$<ANGLE-R>\n>,EXCLUDE,private/.*>,>

#endif
]==]
    TARGET term_seq_sgr
)
set_source_files_properties("${CMAKE_CURRENT_BINARY_DIR}/generated/TermSeq" PROPERTIES
    GENERATED ON
)
add_custom_target(term_seq_gen_amalgation DEPENDS generated/TermSeq)
add_dependencies(term_seq_sgr term_seq_gen_amalgation)

