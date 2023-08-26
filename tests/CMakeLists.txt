add_executable(test_rational)
target_sources(test_rational PRIVATE test_rational.cc)
set_target_properties(test_rational PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY  "${PROJECT_BINARY_DIR}/tests"
)
target_link_libraries(test_rational PRIVATE Seirina)

add_test(NAME test_rational-1-1 COMMAND test_rational 1 1)

add_test(NAME test_rational-1-2 COMMAND test_rational 1 2)
add_test(NAME test_rational-2-2 COMMAND test_rational 2 2)

add_test(NAME test_rational-1-3 COMMAND test_rational 1 3)
add_test(NAME test_rational-2-3 COMMAND test_rational 2 3)
add_test(NAME test_rational-3-3 COMMAND test_rational 3 3)

add_test(NAME test_rational-1-4 COMMAND test_rational 1 4)
add_test(NAME test_rational-2-4 COMMAND test_rational 2 4)
add_test(NAME test_rational-3-4 COMMAND test_rational 3 4)
add_test(NAME test_rational-4-4 COMMAND test_rational 4 4)
