/*
 * SPDX-License-Identifier: BSD-3-Clause
 * Copyright 2020, Intel Corporation
 */

/*
 * mr-test-common.h -- the memory region unit tests's common definitions
 */

#ifndef MR_COMMON_H
#define MR_COMMON_H

#include <stdlib.h>
#include <infiniband/verbs.h>

#include "cmocka_headers.h"
#include "mr.h"
#include "librpma.h"
#include "rpma_err.h"

#define MOCK_PEER	(struct rpma_peer *)0x0AD0
#define MOCK_PTR	(void *)0x0001020304050607
#define MOCK_SIZE	(size_t)0x08090a0b0c0d0e0f
#define MOCK_RKEY	(uint32_t)0x10111213
#define MOCK_USAGE \
	((int)(RPMA_MR_USAGE_READ_SRC | RPMA_MR_USAGE_READ_DST |\
	RPMA_MR_USAGE_WRITE_SRC | RPMA_MR_USAGE_WRITE_DST))
#define MOCK_ACCESS \
	((int)(IBV_ACCESS_REMOTE_READ | IBV_ACCESS_LOCAL_WRITE |\
	IBV_ACCESS_REMOTE_WRITE | IBV_ACCESS_LOCAL_WRITE))
#define MOCK_PLT	RPMA_MR_PLT_PERSISTENT
#define MOCK_ERRNO	(int)(123)
#define MOCK_OK		(int)0

#define DESC_EXP	{{0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00, \
			0x0f, 0x0e, 0x0d, 0x0c, 0x0b, 0x0a, 0x09, 0x08, \
			0x13, 0x12, 0x11, 0x10, \
			0x01}}

#define MOCK_DST_OFFSET		(size_t)0xC413
#define MOCK_SRC_OFFSET		(size_t)0xC414
#define MOCK_LEN		(size_t)0xC415
#define MOCK_OP_CONTEXT		(void *)0xC417

/* a state used for rpma_mr_read/_write tests */
struct mrs {
	struct rpma_mr_local *local;
	struct rpma_mr_remote *remote;
};

/* prestate structure passed to unit test functions */
struct prestate {
	int usage;
	int access;
	/* mr passed from setup to test and to teardown */
	struct rpma_mr_local *mr;
};

/* structure of arguments used in rpma_peer_mr_reg() */
struct rpma_peer_mr_reg_args {
	int usage;
	int access;
	struct ibv_mr *mr;
	int verrno;
};

extern const rpma_mr_descriptor Desc_exp;

/* setups & teardowns */

int setup__reg_success(void **pprestate);
int teardown__dereg_success(void **pprestate);

int setup__mr_local_and_remote(void **mrs_ptr);
int teardown__mr_local_and_remote(void **mrs_ptr);

int setup__mr_remote(void **mr_ptr);
int teardown__mr_remote(void **mr_ptr);

int group_setup_mr_read(void **unused);
int group_setup_mr_write(void **unused);

#endif /* MR_COMMON_H */
