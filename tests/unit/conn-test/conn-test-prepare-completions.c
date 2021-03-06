// SPDX-License-Identifier: BSD-3-Clause
/* Copyright 2020, Intel Corporation */

/*
 * conn-prepare-completions.c -- the rpma_conn_prepare_completions() unit tests
 *
 * APIs covered:
 * - rpma_conn_prepare_completions()
 */

#include "conn-test-common.h"
#include "mocks-ibverbs.h"

/*
 * prepare_completions__conn_NULL - NULL conn is invalid
 */
static void
prepare_completions__conn_NULL(void **unused)
{
	/* run test */
	int ret = rpma_conn_prepare_completions(NULL);

	/* verify the results */
	assert_int_equal(ret, RPMA_E_INVAL);
}

/*
 * prepare_completions__get_cq_event_fail - ibv_get_cq_event() fails
 */
static void
prepare_completions__get_cq_event_fail(void **cstate_ptr)
{
	struct conn_test_state *cstate = *cstate_ptr;

	/* configure mock */
	expect_value(ibv_get_cq_event, channel, MOCK_COMP_CHANNEL);
	will_return(ibv_get_cq_event, MOCK_ERRNO);

	/* run test */
	int ret = rpma_conn_prepare_completions(cstate->conn);

	/* verify the result */
	assert_int_equal(ret, RPMA_E_NO_COMPLETION);
}

/*
 * prepare_completions__req_notify_cq_fail - ibv_req_notify_cq() fails
 */
static void
prepare_completions__req_notify_cq_fail(void **cstate_ptr)
{
	struct conn_test_state *cstate = *cstate_ptr;

	/* configure mocks */
	expect_value(ibv_get_cq_event, channel, MOCK_COMP_CHANNEL);
	will_return(ibv_get_cq_event, MOCK_OK);
	will_return(ibv_get_cq_event, MOCK_IBV_CQ);
	expect_value(ibv_ack_cq_events, cq, MOCK_IBV_CQ);
	will_return(ibv_req_notify_cq_mock, MOCK_ERRNO);

	/* run test */
	int ret = rpma_conn_prepare_completions(cstate->conn);

	/* verify the result */
	assert_int_equal(ret, RPMA_E_PROVIDER);
	assert_int_equal(rpma_err_get_provider_error(), MOCK_ERRNO);
}

/*
 * prepare_completions__success - happy day scenario
 */
static void
prepare_completions__success(void **cstate_ptr)
{
	struct conn_test_state *cstate = *cstate_ptr;

	/* configure mocks */
	expect_value(ibv_get_cq_event, channel, MOCK_COMP_CHANNEL);
	will_return(ibv_get_cq_event, MOCK_OK);
	will_return(ibv_get_cq_event, MOCK_IBV_CQ);
	expect_value(ibv_ack_cq_events, cq, MOCK_IBV_CQ);
	will_return(ibv_req_notify_cq_mock, MOCK_OK);

	/* run test */
	int ret = rpma_conn_prepare_completions(cstate->conn);

	/* verify the result */
	assert_int_equal(ret, MOCK_OK);
}

/*
 * group_setup_prepare_completions -- prepare resources
 * for all tests in the group
 */
int
group_setup_prepare_completions(void **unused)
{
	/* set the req_notify_cq callback in mock of IBV CQ */
	Ibv_context.ops.req_notify_cq = ibv_req_notify_cq_mock;
	Ibv_cq.context = &Ibv_context;

	return 0;
}

const struct CMUnitTest tests_prepare_completions[] = {
	/* rpma_conn_prepare_completions() unit tests */
	cmocka_unit_test(prepare_completions__conn_NULL),
	cmocka_unit_test_setup_teardown(
		prepare_completions__get_cq_event_fail,
		conn_setup, conn_teardown),
	cmocka_unit_test_setup_teardown(
		prepare_completions__req_notify_cq_fail,
		conn_setup, conn_teardown),
	cmocka_unit_test_setup_teardown(
		prepare_completions__success,
		conn_setup, conn_teardown),
	cmocka_unit_test(NULL)
};
