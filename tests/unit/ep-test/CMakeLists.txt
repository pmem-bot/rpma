#
# SPDX-License-Identifier: BSD-3-Clause
# Copyright 2020, Intel Corporation
#

include(../../cmake/ctest_helpers.cmake)

build_test_src(UNIT NAME ep-test SRCS
	ep-test.c
	${LIBRPMA_SOURCE_DIR}/rpma_err.c
	${LIBRPMA_SOURCE_DIR}/ep.c)

target_compile_definitions(ep-test PRIVATE TEST_MOCK_ALLOC)

set_target_properties(ep-test
	PROPERTIES
	LINK_FLAGS "-Wl,--wrap=_test_malloc")

add_test_generic(NAME ep-test TRACERS none)
