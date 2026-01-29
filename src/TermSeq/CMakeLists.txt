add_library(term_seq_core INTERFACE)
add_library("TermSeq::Core" ALIAS term_seq_core)
target_link_libraries(term_seq_core
    INTERFACE
        TermSeq::InterfaceBase
)
target_sources(term_seq_core
    PUBLIC FILE_SET HEADERS
    BASE_DIRS
        "${term_seq_SOURCE_DIR}/src"
    FILES
        ControlSequence.hpp
        ScopedOutput.hpp
        StaticString.hpp
        detection.hpp
        private/detection_posix.hpp
)
set_target_properties(term_seq_core PROPERTIES
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
    target_compile_definitions(term_seq_core
        INTERFACE
            "$<$<NOT:${prop_unset}>:TERMSEQ_ENABLE_POSIX_TERM_DETECTION=${posix_term_detect}>"
    )
endblock()


