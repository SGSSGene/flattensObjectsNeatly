# SPDX-FileCopyrightText: 2024 Simon Gene Gottlieb
# SPDX-License-Identifier: CC0-1.0
cmake_minimum_required (VERSION 3.31)

add_library(fon INTERFACE)
add_library(fon::fon ALIAS fon)
target_compile_features(fon INTERFACE cxx_std_20)
target_link_libraries(fon
    INTERFACE
    reflect::reflect
    yaml-cpp
    jsoncpp_static
)

target_include_directories(fon
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/..>
    $<INSTALL_INTERFACE:include>
)
