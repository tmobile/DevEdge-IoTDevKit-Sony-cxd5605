# Copyright (c) 2022 T-Mobile USA, Inc.
#
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)
if(DEFINED CONFIG_CXD5605_LIB)
    zephyr_include_directories(include)
    add_library(cxd5605_lib STATIC IMPORTED GLOBAL)
    set_target_properties(cxd5605_lib PROPERTIES IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/lib/cxd5605_lib.a")
    zephyr_interface_library_named(CXD5605_DT_ENT)
    zephyr_library()
    zephyr_library_sources("src/dt_ent.c")
    zephyr_link_libraries(cxd5605_lib)
endif()
