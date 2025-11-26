# MIT License
# Copyright (c) 2024 Salem B.
#
# This project is licensed under the MIT License.
# For details, see the LICENSE.md file in the root of this repository.

# ----------------------------------------------------------------------------
# List of test sources
# ----------------------------------------------------------------------------
set(TEST_TARGETS_SOURCES
        ../src/PurgeDuplicates.cpp
)

set(UNIT_TEST_SOURCES
        tests_unit.cpp
)

set(INTEGRATION_TEST_SOURCES
        tests_integration.cpp
)

# ----------------------------------------------------------------------------
# Common function to create test targets with different architecture flags
# ----------------------------------------------------------------------------
function(add_architecture_test_targets test_name sources test_sources)
    # Native architecture test target
    add_executable(${test_name} ${test_sources} ${sources})
    target_include_directories(${test_name} PUBLIC ../src)
    find_package(OpenSSL REQUIRED)
    target_link_libraries(${test_name} PRIVATE OpenSSL::SSL OpenSSL::Crypto)
    add_test(NAME ${test_name} COMMAND ${test_name})

    # 32-bit simulated test target
    add_executable(${test_name}_32bit ${test_sources} ${sources})
    target_include_directories(${test_name}_32bit PUBLIC ../src)
    target_compile_definitions(${test_name}_32bit PRIVATE PDCPP_FORCE_32BIT_PATH)
    target_link_libraries(${test_name}_32bit PRIVATE OpenSSL::SSL OpenSSL::Crypto)
    add_test(NAME ${test_name}_32bit COMMAND ${test_name}_32bit)
endfunction()

# ----------------------------------------------------------------------------
# Create test targets for both 64-bit and 32-bit paths
# ----------------------------------------------------------------------------
add_architecture_test_targets(tests_unit "${TEST_TARGETS_SOURCES}" "${UNIT_TEST_SOURCES}")
add_architecture_test_targets(tests_integration "${TEST_TARGETS_SOURCES}" "${INTEGRATION_TEST_SOURCES}")

# ----------------------------------------------------------------------------
# Debugging Information
# ----------------------------------------------------------------------------
message(STATUS "=====================================================")
message(STATUS "Configuring tests...")
message(STATUS "  Unit Test Sources        : ${UNIT_TEST_SOURCES}")
message(STATUS "  Integration Test Sources : ${INTEGRATION_TEST_SOURCES}")
message(STATUS "  Testing both native and simulated 32-bit paths")
message(STATUS "=====================================================")