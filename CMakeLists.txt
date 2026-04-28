cmake_minimum_required(VERSION 3.21)
project(arcal-cert LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---------------------------------------------------------------------------
# Required: CMake target for the CAL library under test.
# Must expose uci/base/* and uci/type/* via its INTERFACE_INCLUDE_DIRECTORIES
# and provide uci_getAbstractServiceBusConnection.
set(ARCAL_CERT_CAL_LIB "" CACHE STRING
    "CMake target for the CAL library (required)")

# Optional: semicolon-separated list of VAR=VALUE strings forwarded verbatim
# to every test's ENVIRONMENT property. The parent project injects
# transport-specific variables here (e.g. CYCLONEDDS_URI=...).
set(ARCAL_CERT_TEST_ENV "" CACHE STRING
    "Extra environment variables for tests, e.g. 'CYCLONEDDS_URI=...'")

option(ARCAL_CERT_BUILD_CERT    "Build CERT conformance tests"      ON)
option(ARCAL_CERT_BUILD_E2E     "Build E2E smoke tests"             ON)
option(ARCAL_CERT_BUILD_COMPILE "Build compile-only API shape tests" ON)
# ---------------------------------------------------------------------------

if(NOT ARCAL_CERT_CAL_LIB)
    message(FATAL_ERROR
        "ARCAL_CERT_CAL_LIB must name the CMake target for your CAL implementation.")
endif()
if(NOT TARGET ${ARCAL_CERT_CAL_LIB})
    message(FATAL_ERROR
        "'${ARCAL_CERT_CAL_LIB}' is not a defined CMake target. "
        "Add it before add_subdirectory(arcal-cert).")
endif()
enable_testing()
add_custom_target(arcal_cert_suite_all)
if(TARGET arcal_test_suite_all)
    add_dependencies(arcal_test_suite_all arcal_cert_suite_all)
endif()
if(ARCAL_CERT_BUILD_COMPILE)
    add_subdirectory(compile)
endif()
if(ARCAL_CERT_BUILD_CERT)
    add_subdirectory(cert)
endif()
if(ARCAL_CERT_BUILD_E2E)
    add_subdirectory(e2e)
endif()
