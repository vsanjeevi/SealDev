# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT license.

cmake_minimum_required(VERSION 3.12)

project(SEALExamples VERSION 3.6.0 LANGUAGES CXX)

# If not called from root CMakeLists.txt
if(NOT DEFINED SEAL_BUILD_EXAMPLES)
    set(SEAL_BUILD_EXAMPLES ON)

    # Import Microsoft SEAL
    find_package(SEAL 3.6.0 EXACT REQUIRED)

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
endif()

if(SEAL_BUILD_EXAMPLES)
#creating sealkeygen executable
    add_executable(sealkeygen)
    target_sources(sealkeygen
        PRIVATE
            ${CMAKE_CURRENT_LIST_DIR}/sealkeygen.cpp
    )


#creating sealencrypt executable
    add_executable(sealencrypt)
    target_sources(sealencrypt
        PRIVATE
            ${CMAKE_CURRENT_LIST_DIR}/sealencrypt.cpp
    )


#creating sealcompute executable
    add_executable(sealcompute)
    target_sources(sealcompute
        PRIVATE
            ${CMAKE_CURRENT_LIST_DIR}/sealcompute.cpp
    )


#creating sealdecrypt executable
    add_executable(sealdecrypt)
    target_sources(sealdecrypt
        PRIVATE
            ${CMAKE_CURRENT_LIST_DIR}/sealdecrypt.cpp
    )


    if(TARGET SEAL::seal)
        target_link_libraries(sealkeygen PRIVATE SEAL::seal)
        target_link_libraries(sealencrypt PRIVATE SEAL::seal)
        target_link_libraries(sealcompute PRIVATE SEAL::seal)
        target_link_libraries(sealdecrypt PRIVATE SEAL::seal)
    elseif(TARGET SEAL::seal_shared)
        target_link_libraries(sealkeygen PRIVATE SEAL::seal_shared)
        target_link_libraries(sealencrypt PRIVATE SEAL::seal_shared)
        target_link_libraries(sealcompute PRIVATE SEAL::seal_shared)
        target_link_libraries(sealdecrypt PRIVATE SEAL::seal_shared)
    else()
        message(FATAL_ERROR "Cannot find target SEAL::seal or SEAL::seal_shared")
    endif()
endif()
