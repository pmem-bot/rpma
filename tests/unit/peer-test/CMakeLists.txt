#
# SPDX-License-Identifier: BSD-3-Clause
# Copyright 2020, Intel Corporation
#

include(../../cmake/ctest_helpers.cmake)

build_test_src(UNIT NAME peer-test SRCS
	peer-test.c
	${TEST_UNIT_COMMON_DIR}/mocks-ibverbs.c
	${LIBRPMA_SOURCE_DIR}/rpma_err.c
	${LIBRPMA_SOURCE_DIR}/peer.c)

target_compile_definitions(peer-test PRIVATE TEST_MOCK_ALLOC)

set_target_properties(peer-test 
	PROPERTIES
	LINK_FLAGS "-Wl,--wrap=_test_malloc")

add_test_generic(NAME peer-test TRACERS none)
