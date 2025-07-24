add_subdirectory(manual)

add_executable(term_color_detection_unit_test)
target_sources(term_color_detection_unit_test
    PRIVATE
        detection_unit_test.cpp
)
target_link_libraries(term_color_detection_unit_test
    PRIVATE
        TermColor::TermColor
)
set_target_properties(term_color_detection_unit_test PROPERTIES
    TRANSITIVE_COMPILE_PROPERTIES TermColor_enable_posix_term_detection
    TermColor_enable_posix_term_detection 0
)
add_test(NAME term_color_detection_unit_test_test
    COMMAND term_color_detection_unit_test
)


add_executable(term_color_sgr_color_unit_test)
target_sources(term_color_sgr_color_unit_test
    PRIVATE
        SgrColorUnitTest.cpp
)
target_link_libraries(term_color_sgr_color_unit_test
    PRIVATE
        TermColor::TermColor
)
add_custom_target(term_color_sgr_color_unit_test_cmd
    COMMAND term_color_sgr_color_unit_test
    VERBATIM
)
add_dependencies(term_color_sgr_color_unit_test_cmd term_color_sgr_color_unit_test)
