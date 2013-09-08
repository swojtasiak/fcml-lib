/*
 * fcml_mnemonic_parser_t.c
 *
 *  Created on: 5 wrz 2013
 *      Author: tAs
 */


#include "fcml_mnemonic_parser_t.h"

#include <fcml_mnemonic_parser.h>

int fcml_tf_mnemonic_parser_suite_init(void) {
    return 0;
}

int fcml_tf_mnemonic_parser_suite_cleanup(void) {
    return 0;
}

void fcml_tf_mnemonic_parser_test_parse_mnemonics(void) {

    fcml_st_mp_mnemonic_set *mnemonics_set;

    fcml_ceh_error error = fcml_fn_mp_parse_mnemonics( "cmps;cmpsw[ts,o*,aw];cmpsd[ts,o*,ad];cmpsq[ts,o*,aq]", &mnemonics_set );
    CU_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );

    fcml_st_coll_list_element *element = mnemonics_set->mnemonics->head;
    fcml_st_mp_mnemonic *mnemonic = (fcml_st_mp_mnemonic*)element->item;
    CU_ASSERT_STRING_EQUAL( mnemonic->mnemonic, "cmps" );
    CU_ASSERT_EQUAL( mnemonic->shortcut, FCML_FALSE );
    CU_ASSERT_EQUAL( mnemonic->supported_asa, FCML_DS_UNDEF );
    CU_ASSERT_EQUAL( mnemonic->supported_osa, FCML_DS_UNDEF );

    element = element->next;
    mnemonic = (fcml_st_mp_mnemonic*)element->item;
    CU_ASSERT_STRING_EQUAL( mnemonic->mnemonic, "cmpsw" );
    CU_ASSERT_EQUAL( mnemonic->shortcut, FCML_TRUE );
    CU_ASSERT_EQUAL( mnemonic->supported_asa, FCML_DS_16 );
    CU_ASSERT_EQUAL( mnemonic->supported_osa, FCML_DS_UNDEF );

    element = element->next;
    mnemonic = (fcml_st_mp_mnemonic*)element->item;
    CU_ASSERT_STRING_EQUAL( mnemonic->mnemonic, "cmpsd" );
    CU_ASSERT_EQUAL( mnemonic->shortcut, FCML_TRUE );
    CU_ASSERT_EQUAL( mnemonic->supported_asa, FCML_DS_32 );
    CU_ASSERT_EQUAL( mnemonic->supported_osa, FCML_DS_UNDEF );

    element = element->next;
    mnemonic = (fcml_st_mp_mnemonic*)element->item;
    CU_ASSERT_STRING_EQUAL( mnemonic->mnemonic, "cmpsq" );
    CU_ASSERT_EQUAL( mnemonic->shortcut, FCML_TRUE );
    CU_ASSERT_EQUAL( mnemonic->supported_asa, FCML_DS_64 );
    CU_ASSERT_EQUAL( mnemonic->supported_osa, FCML_DS_UNDEF );

    CU_ASSERT_PTR_NULL( element->next );

    fcml_fn_mp_free_mnemonics( mnemonics_set );
}

void fcml_tf_mnemonic_parser_test_parse_mnemonics_1(void) {

    fcml_st_mp_mnemonic_set *mnemonics_set;

    fcml_ceh_error error = fcml_fn_mp_parse_mnemonics( "cmps;", &mnemonics_set );
    CU_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );

    fcml_st_coll_list_element *element = mnemonics_set->mnemonics->head;
    fcml_st_mp_mnemonic *mnemonic = (fcml_st_mp_mnemonic*)element->item;
    CU_ASSERT_STRING_EQUAL( mnemonic->mnemonic, "cmps" );
    CU_ASSERT_EQUAL( mnemonic->shortcut, FCML_FALSE );
    CU_ASSERT_EQUAL( mnemonic->supported_asa, FCML_DS_UNDEF );
    CU_ASSERT_EQUAL( mnemonic->supported_osa, FCML_DS_UNDEF );

    CU_ASSERT_PTR_NULL( element->next );

    fcml_fn_mp_free_mnemonics( mnemonics_set );
}

void fcml_tf_mnemonic_parser_test_parse_mnemonics_2(void) {

    fcml_st_mp_mnemonic_set *mnemonics_set;

    fcml_ceh_error error = fcml_fn_mp_parse_mnemonics( "cmps[ts];", &mnemonics_set );
    CU_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );

    fcml_st_coll_list_element *element = mnemonics_set->mnemonics->head;
    fcml_st_mp_mnemonic *mnemonic = (fcml_st_mp_mnemonic*)element->item;
    CU_ASSERT_STRING_EQUAL( mnemonic->mnemonic, "cmps" );
    CU_ASSERT_EQUAL( mnemonic->shortcut, FCML_TRUE );
    CU_ASSERT_EQUAL( mnemonic->supported_asa, FCML_DS_UNDEF );
    CU_ASSERT_EQUAL( mnemonic->supported_osa, FCML_DS_UNDEF );

    CU_ASSERT_PTR_NULL( element->next );

    fcml_fn_mp_free_mnemonics( mnemonics_set );
}

fcml_string fcml_itb_bad_formatted_mnemonics[] = {
    "",
    ";",
    ";[",
    "[;",
    ";;;;",
    ";cmps",
    "cmps[;",
    "cmps[];",
    "cmps];",
    "cmps[[ts];",
    "cmps[ts]];",
    "cmps[ts;",
    "cmps[ts",
    "cmps[t",
    "cmps[t]",
    "cmps[bx]",
    "cmps[om]",
    "cm!ps",
    " cmps",
    "[]",
    "cmps[oda",
    "cmps[oda]",
    "cmps]",
    "cmps[odad]",
    "cmps[od,,ad]",
    "cmps[,od]",
    "cmps[od,]",
    "cmps[,]",
    "cmps[,,]",
    "cmps[,",
    "cmps[ad;]",
};

void fcml_tf_mnemonic_parser_test_parse_mnemonics_3(void) {
    int i;
    for( i = 0; i < sizeof( fcml_itb_bad_formatted_mnemonics ) / sizeof( fcml_string ); i++ ) {
        fcml_st_mp_mnemonic_set *mnemonics_set = NULL;
        fcml_string mnemonic = fcml_itb_bad_formatted_mnemonics[i];
        fcml_ceh_error error = fcml_fn_mp_parse_mnemonics( mnemonic, &mnemonics_set );
        CU_ASSERT_EQUAL( error, FCML_CEH_GEC_INVALID_INPUT );
        CU_ASSERT_PTR_NULL( mnemonics_set );
    }
}

CU_TestInfo fcml_ti_mnemonic_parser[] = {
    { "fcml_tf_mnemonic_parser_test_parse_mnemonics", fcml_tf_mnemonic_parser_test_parse_mnemonics },
    { "fcml_tf_mnemonic_parser_test_parse_mnemonics_1", fcml_tf_mnemonic_parser_test_parse_mnemonics_1 },
    { "fcml_tf_mnemonic_parser_test_parse_mnemonics_2", fcml_tf_mnemonic_parser_test_parse_mnemonics_2 },
    { "fcml_tf_mnemonic_parser_test_parse_mnemonics_3", fcml_tf_mnemonic_parser_test_parse_mnemonics_3 },
    CU_TEST_INFO_NULL,
};

CU_SuiteInfo fcml_si_mnemonic_parser[] = {
    { "suite-fcml-mnemonic-parser", fcml_tf_mnemonic_parser_suite_init, fcml_tf_mnemonic_parser_suite_cleanup, fcml_ti_mnemonic_parser },
    CU_SUITE_INFO_NULL,
};

