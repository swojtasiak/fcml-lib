/*
 * FCML - Free Code Manipulation Library.
 * Copyright (C) 2010-2020 Slawomir Wojtasiak
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "mnemonic_parser_t.h"

#include <fcml_mnemonic_parser.h>

#include <fcml_common.h>

fcml_bool fcml_tf_mnemonic_parser_suite_init(void) {
	return FCML_TRUE;
}

fcml_bool fcml_tf_mnemonic_parser_suite_cleanup(void) {
	return FCML_TRUE;
}

void fcml_tf_mnemonic_parser_test_parse_mnemonics(void) {

    fcml_st_mp_mnemonic_set *mnemonics_set;

    fcml_ceh_error error = fcml_fn_mp_parse_mnemonics( "cmps[sb,mm];cmpsw[ts,o*,aw,sf,mr];cmpsd[ts,o*,ad,sf];cmpsq[ts,o*,aq,sf]", &mnemonics_set );
    STF_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );

    fcml_st_coll_list_element *element = mnemonics_set->mnemonics->head;
    fcml_st_mp_mnemonic *mnemonic = (fcml_st_mp_mnemonic*)element->item;
    STF_ASSERT_STRING_EQUAL( mnemonic->mnemonic, "cmps" );
    STF_ASSERT_EQUAL( mnemonic->is_shortcut, FCML_FALSE );
    STF_ASSERT_EQUAL( mnemonic->supported_asa, FCML_DS_UNDEF );
    STF_ASSERT_EQUAL( mnemonic->supported_osa, FCML_DS_UNDEF );
    STF_ASSERT_EQUAL( mnemonic->is_byte_ds, FCML_TRUE );
    STF_ASSERT_EQUAL( mnemonic->is_full_ds, FCML_FALSE );
    STF_ASSERT_EQUAL( mnemonic->is_mode_mem_only, FCML_TRUE );
    STF_ASSERT_EQUAL( mnemonic->is_mode_reg_only, FCML_FALSE );

    element = element->next;
    mnemonic = (fcml_st_mp_mnemonic*)element->item;
    STF_ASSERT_STRING_EQUAL( mnemonic->mnemonic, "cmpsw" );
    STF_ASSERT_EQUAL( mnemonic->is_shortcut, FCML_TRUE );
    STF_ASSERT_EQUAL( mnemonic->supported_asa, FCML_DS_16 );
    STF_ASSERT_EQUAL( mnemonic->supported_osa, FCML_DS_UNDEF );
    STF_ASSERT_EQUAL( mnemonic->is_byte_ds, FCML_FALSE );
	STF_ASSERT_EQUAL( mnemonic->is_full_ds, FCML_TRUE );
	STF_ASSERT_EQUAL( mnemonic->is_mode_mem_only, FCML_FALSE );
	STF_ASSERT_EQUAL( mnemonic->is_mode_reg_only, FCML_TRUE );

    element = element->next;
    mnemonic = (fcml_st_mp_mnemonic*)element->item;
    STF_ASSERT_STRING_EQUAL( mnemonic->mnemonic, "cmpsd" );
    STF_ASSERT_EQUAL( mnemonic->is_shortcut, FCML_TRUE );
    STF_ASSERT_EQUAL( mnemonic->supported_asa, FCML_DS_32 );
    STF_ASSERT_EQUAL( mnemonic->supported_osa, FCML_DS_UNDEF );

    element = element->next;
    mnemonic = (fcml_st_mp_mnemonic*)element->item;
    STF_ASSERT_STRING_EQUAL( mnemonic->mnemonic, "cmpsq" );
    STF_ASSERT_EQUAL( mnemonic->is_shortcut, FCML_TRUE );
    STF_ASSERT_EQUAL( mnemonic->supported_asa, FCML_DS_64 );
    STF_ASSERT_EQUAL( mnemonic->supported_osa, FCML_DS_UNDEF );

    STF_ASSERT_PTR_NULL( element->next );

    fcml_fn_mp_free_mnemonics( mnemonics_set );
}

void fcml_tf_mnemonic_parser_test_parse_mnemonics_1(void) {

    fcml_st_mp_mnemonic_set *mnemonics_set;

    fcml_ceh_error error = fcml_fn_mp_parse_mnemonics( "cmps;", &mnemonics_set );
    STF_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );

    fcml_st_coll_list_element *element = mnemonics_set->mnemonics->head;
    fcml_st_mp_mnemonic *mnemonic = (fcml_st_mp_mnemonic*)element->item;
    STF_ASSERT_STRING_EQUAL( mnemonic->mnemonic, "cmps" );
    STF_ASSERT_EQUAL( mnemonic->is_shortcut, FCML_FALSE );
    STF_ASSERT_EQUAL( mnemonic->supported_asa, FCML_DS_UNDEF );
    STF_ASSERT_EQUAL( mnemonic->supported_osa, FCML_DS_UNDEF );

    STF_ASSERT_PTR_NULL( element->next );

    fcml_fn_mp_free_mnemonics( mnemonics_set );
}

void fcml_tf_mnemonic_parser_test_parse_mnemonics_2(void) {

    fcml_st_mp_mnemonic_set *mnemonics_set;

    fcml_ceh_error error = fcml_fn_mp_parse_mnemonics( "cmps[ts];", &mnemonics_set );
    STF_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );

    fcml_st_coll_list_element *element = mnemonics_set->mnemonics->head;
    fcml_st_mp_mnemonic *mnemonic = (fcml_st_mp_mnemonic*)element->item;
    STF_ASSERT_STRING_EQUAL( mnemonic->mnemonic, "cmps" );
    STF_ASSERT_EQUAL( mnemonic->is_shortcut, FCML_TRUE );
    STF_ASSERT_EQUAL( mnemonic->supported_asa, FCML_DS_UNDEF );
    STF_ASSERT_EQUAL( mnemonic->supported_osa, FCML_DS_UNDEF );

    STF_ASSERT_PTR_NULL( element->next );

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
    "cmps]",
    "cmps[odadddf]",
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
       /* printf("%d:%d\n", i, error);*/
        STF_ASSERT_EQUAL( error, FCML_CEH_GEC_INVALID_INPUT );
        STF_ASSERT_PTR_NULL( mnemonics_set );
    }
}

void fcml_tf_mnemonic_parser_test_parse_mnemonics_4(void) {

    fcml_st_mp_mnemonic_set *mnemonics_set;

    fcml_ceh_error error = fcml_fn_mp_parse_mnemonics( "cmpordsd[p07]", &mnemonics_set );
    STF_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );

    fcml_st_coll_list_element *element = mnemonics_set->mnemonics->head;
    fcml_st_mp_mnemonic *mnemonic = (fcml_st_mp_mnemonic*)element->item;
    STF_ASSERT_STRING_EQUAL( mnemonic->mnemonic, "cmpordsd" );
    STF_ASSERT_EQUAL( mnemonic->is_shortcut, FCML_FALSE );
    STF_ASSERT_EQUAL( mnemonic->supported_asa, FCML_DS_UNDEF );
    STF_ASSERT_EQUAL( mnemonic->supported_osa, FCML_DS_UNDEF );
    STF_ASSERT_EQUAL( mnemonic->pseudo_op.is_not_null, FCML_TRUE );
    STF_ASSERT_EQUAL( mnemonic->pseudo_op.value, 0x07 );

    STF_ASSERT_PTR_NULL( element->next );

    fcml_fn_mp_free_mnemonics( mnemonics_set );
}

void fcml_tf_mnemonic_parser_test_parse_mnemonics_5(void) {

    fcml_st_mp_mnemonic_set *mnemonics_set;

    fcml_ceh_error error = fcml_fn_mp_parse_mnemonics( "cmpordsd[S07]", &mnemonics_set );
    STF_ASSERT_EQUAL( error, FCML_CEH_GEC_NO_ERROR );

    fcml_st_coll_list_element *element = mnemonics_set->mnemonics->head;
    fcml_st_mp_mnemonic *mnemonic = (fcml_st_mp_mnemonic*)element->item;
    STF_ASSERT_STRING_EQUAL( mnemonic->mnemonic, "cmpordsd" );
    STF_ASSERT_EQUAL( mnemonic->is_shortcut, FCML_FALSE );
    STF_ASSERT_EQUAL( mnemonic->supported_asa, FCML_DS_UNDEF );
    STF_ASSERT_EQUAL( mnemonic->supported_osa, FCML_DS_UNDEF );
    STF_ASSERT_EQUAL( mnemonic->suffix.is_not_null, FCML_TRUE );
    STF_ASSERT_EQUAL( mnemonic->suffix.value, 0x07 );

    STF_ASSERT_PTR_NULL( element->next );

    fcml_fn_mp_free_mnemonics( mnemonics_set );
}

fcml_stf_test_case fcml_ti_mnemonic_parser[] = {
	{ "fcml_tf_mnemonic_parser_test_parse_mnemonics", fcml_tf_mnemonic_parser_test_parse_mnemonics },
	{ "fcml_tf_mnemonic_parser_test_parse_mnemonics_1", fcml_tf_mnemonic_parser_test_parse_mnemonics_1 },
	{ "fcml_tf_mnemonic_parser_test_parse_mnemonics_2", fcml_tf_mnemonic_parser_test_parse_mnemonics_2 },
	{ "fcml_tf_mnemonic_parser_test_parse_mnemonics_3", fcml_tf_mnemonic_parser_test_parse_mnemonics_3 },
	{ "fcml_tf_mnemonic_parser_test_parse_mnemonics_4", fcml_tf_mnemonic_parser_test_parse_mnemonics_4 },
	{ "fcml_tf_mnemonic_parser_test_parse_mnemonics_5", fcml_tf_mnemonic_parser_test_parse_mnemonics_5 },
	FCML_STF_NULL_TEST
};

fcml_stf_test_suite fcml_si_mnemonic_parser = {
	"suite-fcml-mnemonic-parser", fcml_tf_mnemonic_parser_suite_init, fcml_tf_mnemonic_parser_suite_cleanup, fcml_ti_mnemonic_parser
};


