# SPDX-FileCopyrightText: 2024 Simon Gene Gottlieb
# SPDX-License-Identifier: CC0-1.0
cmake_minimum_required (VERSION 3.31)

project(test_testYAMLFon)

add_executable(${PROJECT_NAME}
    main.cpp
    testBool.cpp
    testClasses.cpp
    testContainer.cpp
    testEnum.cpp
    testFloats.cpp
    testInts.cpp
    testPointers.cpp
)
target_link_libraries(${PROJECT_NAME}
    Catch2::Catch2WithMain
    fon::fon
)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
