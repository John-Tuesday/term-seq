add_executable(term_seq_test_manual)
target_sources(term_seq_test_manual
    PRIVATE
        main.cpp
)
target_link_libraries(term_seq_test_manual
    PRIVATE
        TermSeq::TermSeq
)

add_custom_target(term_seq_test_manual_cmd
    COMMAND term_seq_test_manual
)
add_dependencies(term_seq_test_manual_cmd
    term_seq_test_manual
)
