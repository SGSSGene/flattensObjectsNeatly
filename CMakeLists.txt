# SPDX-FileCopyrightText: 2024 Simon Gene Gottlieb
# SPDX-License-Identifier: CC0-1.0
cmake_minimum_required (VERSION 3.31)

project(fon LANGUAGES CXX
            DESCRIPTION "fon -- flattens objects neatly")

if (PROJECT_IS_TOP_LEVEL)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        set(CMAKE_CXX_FLAGS /EHsc)
    endif()
endif()

include(cmake/CPM.cmake)
CPMAddPackage("gh:SGSSGene/cpm.dependencies@1.0.0")
CPMLoadDependenciesFile("${CMAKE_CURRENT_SOURCE_DIR}/cpm.dependencies")

add_subdirectory(src/fon)

if (PROJECT_IS_TOP_LEVEL)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        target_compile_options(fon INTERFACE /bigobj /EHsc -DNOMINMAX)
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "IntelLLVM")
        target_compile_options(fon INTERFACE -Wall -Werror -Wpedantic -Wextra -fPIC -fp-model=strict)
    else()
        target_compile_options(fon INTERFACE -Wall -Werror -Wpedantic -Wextra -fPIC)
    endif()

    enable_testing()
    add_subdirectory(src/exampleFon)
    add_subdirectory(src/testBinaryFon)
    add_subdirectory(src/testJSONFon)
    add_subdirectory(src/testYAMLFon)
endif()
