add_subdirectory(manual)

add_executable(term_seq_detection_unit_test)
target_sources(term_seq_detection_unit_test
    PRIVATE
        detection_unit_test.cpp
)
target_link_libraries(term_seq_detection_unit_test
    PRIVATE
        TermSeq::TermSeq
)
set_target_properties(term_seq_detection_unit_test PROPERTIES
    TRANSITIVE_COMPILE_PROPERTIES TermSeq_enable_posix_term_detection
    TermSeq_enable_posix_term_detection 0
)
add_test(NAME term_seq_detection_unit_test_test
    COMMAND term_seq_detection_unit_test
)


add_executable(term_seq_sgr_color_unit_test)
target_sources(term_seq_sgr_color_unit_test
    PRIVATE
        SgrColorUnitTest.cpp
)
target_link_libraries(term_seq_sgr_color_unit_test
    PRIVATE
        TermSeq::TermSeq
)
add_custom_target(term_seq_sgr_color_unit_test_cmd
    COMMAND term_seq_sgr_color_unit_test
    VERBATIM
)
add_dependencies(term_seq_sgr_color_unit_test_cmd term_seq_sgr_color_unit_test)

add_executable(term_seq_scoped_unit_test)
target_sources(term_seq_scoped_unit_test
  PRIVATE
    scoped_unit_test.cpp
)
target_link_libraries(term_seq_scoped_unit_test
    PRIVATE
        TermSeq::TermSeq
)
