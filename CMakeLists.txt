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

# Optional: CDR externalizer target. Required for E2E tests and CERT
# CAL-005208/209/210. If unset, those tests are skipped.
set(ARCAL_CERT_EXTERNALIZER_LIB "" CACHE STRING
    "CMake target for the CDR externalizer (optional)")

# Optional: semicolon-separated list of VAR=VALUE strings forwarded verbatim
# to every test's ENVIRONMENT property. The parent project injects
# transport-specific variables here (e.g. CYCLONEDDS_URI=...).
set(ARCAL_CERT_TEST_ENV "" CACHE STRING
    "Extra environment variables for tests, e.g. 'CYCLONEDDS_URI=...'")

option(ARCAL_CERT_BUILD_CERT "Build CERT conformance tests" ON)
option(ARCAL_CERT_BUILD_E2E  "Build E2E smoke tests"        ON)
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
if(ARCAL_CERT_EXTERNALIZER_LIB AND NOT TARGET ${ARCAL_CERT_EXTERNALIZER_LIB})
    message(FATAL_ERROR
        "'${ARCAL_CERT_EXTERNALIZER_LIB}' is not a defined CMake target.")
endif()

enable_testing()
if(ARCAL_CERT_BUILD_CERT) add_subdirectory(cert) endif()
if(ARCAL_CERT_BUILD_E2E)  add_subdirectory(e2e)  endif()
