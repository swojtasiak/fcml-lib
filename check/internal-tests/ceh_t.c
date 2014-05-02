
#include "ceh_t.h"

#include <fcml_ceh.h>

fcml_bool fcml_tf_ceh_suite_init(void) {
	return FCML_TRUE;
}

fcml_bool fcml_tf_ceh_suite_cleanup(void) {
	return FCML_TRUE;
}

void fcml_tf_ceh_test_remove_errors_by_level(void) {

	fcml_st_ceh_error_container conteiner = { NULL };

	STF_ASSERT_PTR_NOT_NULL( fcml_fn_ceh_add_error( &conteiner, "Message 1.", 1, FCML_EN_CEH_EL_ERROR ) );
	STF_ASSERT_PTR_NOT_NULL( fcml_fn_ceh_add_error( &conteiner, "Message 2.", 2, FCML_EN_CEH_EL_ERROR ) );
	STF_ASSERT_PTR_NOT_NULL( fcml_fn_ceh_add_error( &conteiner, "Message 3.", 3, FCML_EN_CEH_EL_WARN ) );
	STF_ASSERT_PTR_NOT_NULL( fcml_fn_ceh_add_error( &conteiner, "Message 4.", 4, FCML_EN_CEH_EL_WARN ) );

	fcml_st_ceh_error_info *error = conteiner.errors;
	STF_ASSERT_EQUAL( error->code, 1 );
	error = error->next_error;
	STF_ASSERT_EQUAL( error->code, 2 );
	error = error->next_error;
	STF_ASSERT_EQUAL( error->code, 3 );
	error = error->next_error;
	STF_ASSERT_EQUAL( error->code, 4 );
	error = error->next_error;
	STF_ASSERT_PTR_NULL( error );

	fcml_fn_ceh_free_errors_only_with_level( &conteiner, FCML_EN_CEH_EL_ERROR );

	error = conteiner.errors;
	STF_ASSERT_EQUAL( error->code, 3 );
	error = error->next_error;
	STF_ASSERT_EQUAL( error->code, 4 );
	error = error->next_error;
	STF_ASSERT_PTR_NULL( error );

	fcml_fn_ceh_free_errors_only_with_level( &conteiner, FCML_EN_CEH_EL_WARN );

	STF_ASSERT_PTR_NULL( conteiner.errors );
	STF_ASSERT_PTR_NULL( conteiner.last_error );

}

void fcml_tf_ceh_test_remove_errors(void) {

	fcml_st_ceh_error_container conteiner = { NULL };

	STF_ASSERT_PTR_NOT_NULL( fcml_fn_ceh_add_error( &conteiner, "Message 1.", 1, FCML_EN_CEH_EL_ERROR ) );
	STF_ASSERT_PTR_NOT_NULL( fcml_fn_ceh_add_error( &conteiner, "Message 2.", 2, FCML_EN_CEH_EL_ERROR ) );
	STF_ASSERT_PTR_NOT_NULL( fcml_fn_ceh_add_error( &conteiner, "Message 3.", 3, FCML_EN_CEH_EL_WARN ) );
	STF_ASSERT_PTR_NOT_NULL( fcml_fn_ceh_add_error( &conteiner, "Message 4.", 4, FCML_EN_CEH_EL_WARN ) );

	fcml_st_ceh_error_info *error = conteiner.errors;
	STF_ASSERT_EQUAL( error->code, 1 );
	error = error->next_error;
	STF_ASSERT_EQUAL( error->code, 2 );
	error = error->next_error;
	STF_ASSERT_EQUAL( error->code, 3 );
	error = error->next_error;
	STF_ASSERT_EQUAL( error->code, 4 );
	error = error->next_error;
	STF_ASSERT_PTR_NULL( error );

	fcml_fn_ceh_free_errors_only( &conteiner );

	STF_ASSERT_PTR_NULL( conteiner.errors );
	STF_ASSERT_PTR_NULL( conteiner.last_error );

}

void fcml_tf_ceh_test_move(void) {

	fcml_st_ceh_error_container conteiner = { NULL };
	fcml_st_ceh_error_container conteiner_next = { NULL };

	STF_ASSERT_PTR_NOT_NULL( fcml_fn_ceh_add_error( &conteiner, "Message 1.", 1, FCML_EN_CEH_EL_ERROR ) );
	STF_ASSERT_PTR_NOT_NULL( fcml_fn_ceh_add_error( &conteiner, "Message 2.", 2, FCML_EN_CEH_EL_ERROR ) );
	STF_ASSERT_PTR_NOT_NULL( fcml_fn_ceh_add_error( &conteiner, "Message 3.", 3, FCML_EN_CEH_EL_WARN ) );
	STF_ASSERT_PTR_NOT_NULL( fcml_fn_ceh_add_error( &conteiner, "Message 4.", 4, FCML_EN_CEH_EL_WARN ) );

	fcml_st_ceh_error_info *error = conteiner.errors;
	STF_ASSERT_EQUAL( error->code, 1 );
	error = error->next_error;
	STF_ASSERT_EQUAL( error->code, 2 );
	error = error->next_error;
	STF_ASSERT_EQUAL( error->code, 3 );
	error = error->next_error;
	STF_ASSERT_EQUAL( error->code, 4 );
	error = error->next_error;
	STF_ASSERT_PTR_NULL( error );

	fcml_fn_ceh_move_errors( &conteiner_next, &conteiner );

	STF_ASSERT_PTR_NULL( conteiner.errors );
	STF_ASSERT_PTR_NULL( conteiner.last_error );

	error = conteiner_next.errors;
	STF_ASSERT_EQUAL( error->code, 1 );
	error = error->next_error;
	STF_ASSERT_EQUAL( error->code, 2 );
	error = error->next_error;
	STF_ASSERT_EQUAL( error->code, 3 );
	error = error->next_error;
	STF_ASSERT_EQUAL( error->code, 4 );
	error = error->next_error;
	STF_ASSERT_PTR_NULL( error );

}

fcml_stf_test_case fcml_ti_ceh[] = {
	{ "fcml_tf_ceh_test_remove_errors_by_level", fcml_tf_ceh_test_remove_errors_by_level },
	{ "fcml_tf_ceh_test_remove_errors", fcml_tf_ceh_test_remove_errors },
	{ "fcml_tf_ceh_test_move", fcml_tf_ceh_test_move },
	FCML_STF_NULL_TEST
};

fcml_stf_test_suite fcml_si_ceh = {
	"suite-fcml-ceh", fcml_tf_ceh_suite_init, fcml_tf_ceh_suite_cleanup, fcml_ti_ceh
};
