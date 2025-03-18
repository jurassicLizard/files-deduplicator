# MIT License
# Copyright (c) 2024 Salem Bouraoui
#
# This project is licensed under the MIT License.
# For details, see the LICENSE.md file in the root of this repository.



# ----------------------------------------------------------------------------
# Specify sources and headers
# ----------------------------------------------------------------------------
set(SOURCES
        main.cpp
        PurgeDuplicates.cpp
)

set(HEADERS
        PurgeDuplicates.hpp
)

# ----------------------------------------------------------------------------
# Add the main executable
# ----------------------------------------------------------------------------
add_executable(${EXECUTABLE_NAME} ${SOURCES})

# Link OpenSSL to the main executable
target_link_libraries(${EXECUTABLE_NAME} PRIVATE OpenSSL::SSL OpenSSL::Crypto)

# Include current directory for headers
target_include_directories(${EXECUTABLE_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# ----------------------------------------------------------------------------
# Debugging Information
# ----------------------------------------------------------------------------
message(STATUS "=====================================================")
message(STATUS "Building ${EXECUTABLE_NAME} executable...")
message(STATUS "  Source Files       : ${SOURCES}")
message(STATUS "  Header Files       : ${HEADERS}")
message(STATUS "=====================================================")