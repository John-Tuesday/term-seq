add_executable(term_color_test_manual)
target_sources(term_color_test_manual
    PRIVATE
        main.cpp
)
target_link_libraries(term_color_test_manual
    PRIVATE
        TermColor::TermColor
)

add_custom_target(term_color_test_manual_cmd
    COMMAND term_color_test_manual
)
add_dependencies(term_color_test_manual_cmd
    term_color_test_manual
)
