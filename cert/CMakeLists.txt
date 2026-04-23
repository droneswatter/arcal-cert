function(_arcal_cert_test cert_id)
    add_executable(cert_${cert_id} ${cert_id}.cpp)
    target_link_libraries(cert_${cert_id} PRIVATE ${ARCAL_CERT_CAL_LIB})
    add_test(NAME CERT-${cert_id} COMMAND cert_${cert_id})
    set_tests_properties(CERT-${cert_id} PROPERTIES
        TIMEOUT     8
        ENVIRONMENT "${ARCAL_CERT_TEST_ENV}"
        LABELS      "cert;runtime")
endfunction()

# CERT CAL-016015: Multiple CAL Clients in single address space get distinct UUIDs
_arcal_cert_test(CAL-016015)

# CERT CAL-016366: Status listener is called immediately on registration with current state
_arcal_cert_test(CAL-016366)

# CERT CAL-005201: Mechanism to obtain an initialized CAL instance
_arcal_cert_test(CAL-005201)

# CERT CAL-005202: Single CAL instance per unique Service + ASB Identifier combination
_arcal_cert_test(CAL-005202)

# CERT CAL-005203: Mechanism to retrieve System/Service/Subsystem/Component/Capability UUIDs
_arcal_cert_test(CAL-005203)

# CERT CAL-005204: Error reported to CAL Client when initialization fails
_arcal_cert_test(CAL-005204)

# CERT CAL-005208: Topic associated with one and only one CAL Message type
_arcal_cert_test(CAL-005208)

# CERT CAL-005209: Client Topics mapped to applicable CAL Topics
_arcal_cert_test(CAL-005209)

# CERT CAL-005210: Independent QoS settings per Client Topic
_arcal_cert_test(CAL-005210)
