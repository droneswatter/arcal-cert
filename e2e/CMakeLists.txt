# ---------------------------------------------------------------------------
# ActionCommand pub/sub (two-process shell test)
# ---------------------------------------------------------------------------

add_executable(e2e_pub pub_action_command.cpp)
target_link_libraries(e2e_pub PRIVATE ${ARCAL_CERT_CAL_LIB})
add_dependencies(arcal_cert_suite_all e2e_pub)

add_executable(e2e_sub sub_action_command.cpp)
target_link_libraries(e2e_sub PRIVATE ${ARCAL_CERT_CAL_LIB})
add_dependencies(arcal_cert_suite_all e2e_sub)

configure_file(run_e2e_action_command.sh.in run_e2e_action_command.sh @ONLY)
file(CHMOD ${CMAKE_CURRENT_BINARY_DIR}/run_e2e_action_command.sh
    PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
                GROUP_READ GROUP_EXECUTE
                WORLD_READ WORLD_EXECUTE)

add_test(
    NAME    E2E-ActionCommand-PubSub
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/run_e2e_action_command.sh)
set_tests_properties(E2E-ActionCommand-PubSub PROPERTIES
    TIMEOUT     8
    ENVIRONMENT "${ARCAL_CERT_TEST_ENV}"
    LABELS      "e2e;runtime")

# ---------------------------------------------------------------------------
# Topic isolation (two-process shell test)
# ---------------------------------------------------------------------------

add_executable(e2e_topic_isolation topic_isolation.cpp)
target_link_libraries(e2e_topic_isolation PRIVATE ${ARCAL_CERT_CAL_LIB})
add_dependencies(arcal_cert_suite_all e2e_topic_isolation)

configure_file(run_e2e_topic_isolation.sh.in run_e2e_topic_isolation.sh @ONLY)
file(CHMOD ${CMAKE_CURRENT_BINARY_DIR}/run_e2e_topic_isolation.sh
    PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
                GROUP_READ GROUP_EXECUTE
                WORLD_READ WORLD_EXECUTE)

add_test(
    NAME    E2E-TopicIsolation
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/run_e2e_topic_isolation.sh)
set_tests_properties(E2E-TopicIsolation PROPERTIES
    TIMEOUT     8
    ENVIRONMENT "${ARCAL_CERT_TEST_ENV}"
    LABELS      "e2e;runtime")

# ---------------------------------------------------------------------------
# Single-process E2E tests
# ---------------------------------------------------------------------------

foreach(_test IN ITEMS
    content_fidelity
    multi_message
    listener_lifecycle
    two_writers_one_reader
    two_readers_one_writer
    readnowait_empty
    read_timeout
    reader_writer_close)

    add_executable(e2e_${_test} ${_test}.cpp)
    target_link_libraries(e2e_${_test} PRIVATE ${ARCAL_CERT_CAL_LIB})
    add_dependencies(arcal_cert_suite_all e2e_${_test})

    string(REPLACE "_" "-" _test_name "${_test}")
    add_test(NAME E2E-${_test_name} COMMAND e2e_${_test})
    set_tests_properties(E2E-${_test_name} PROPERTIES
        TIMEOUT     8
        ENVIRONMENT "${ARCAL_CERT_TEST_ENV}"
        LABELS      "e2e;runtime")
endforeach()
