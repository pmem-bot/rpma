#
# SPDX-License-Identifier: BSD-3-Clause
# Copyright 2020, Intel Corporation
#

include(../../cmake/ctest_helpers.cmake)

build_test_src(UNIT NAME conn_req-test SRCS
       conn_req-test.c
       ${TEST_UNIT_COMMON_DIR}/mocks-ibverbs.c
       ${TEST_UNIT_COMMON_DIR}/mocks-rdma_cm.c
       ${TEST_UNIT_COMMON_DIR}/mocks-rpma-conn.c
       ${TEST_UNIT_COMMON_DIR}/mocks-rpma-info.c
       ${TEST_UNIT_COMMON_DIR}/mocks-rpma-peer.c
       ${TEST_UNIT_COMMON_DIR}/mocks-rpma-private_data.c
       ${TEST_UNIT_COMMON_DIR}/mocks-stdlib.c
       ${LIBRPMA_SOURCE_DIR}/conn_req.c
       ${LIBRPMA_SOURCE_DIR}/rpma_err.c)

target_compile_definitions(conn_req-test PRIVATE TEST_MOCK_ALLOC)

set_target_properties(conn_req-test
       PROPERTIES
       LINK_FLAGS "-Wl,--wrap=_test_malloc")

add_test_generic(NAME conn_req-test TRACERS none)
