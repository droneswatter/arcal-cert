# Compile-only API shape tests — OMSC-SPC-008 RevK C++ CAL Spec.
# Successful compilation IS the test; no DDS, no linker, no runtime required.
# Each file targets one rule family and cites its CERT IDs in a leading comment.

add_library(arcal_cert_compile OBJECT
    conf_base_structure.cpp
    conf_factory_methods.cpp
    conf_required_elements.cpp
    conf_optional_elements.cpp
    conf_bounded_list_elements.cpp
    conf_uuid_elements.cpp
    conf_simple_restriction.cpp
    conf_enum_extended.cpp
    conf_choice_accessor.cpp
    conf_mt_shape.cpp
)

# Inherit include directories from the CAL library target (uci/base/*, uci/type/*).
target_link_libraries(arcal_cert_compile PRIVATE ${ARCAL_CERT_CAL_LIB})

add_custom_target(arcal_cert_compile_all ALL DEPENDS arcal_cert_compile)
add_dependencies(arcal_cert_suite_all arcal_cert_compile)
