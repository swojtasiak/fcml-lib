/*
 * fcml_coll.h
 *
 *  Created on: 10-03-2013
 *      Author: tAs
 */

#ifndef FCML_COLL_H_
#define FCML_COLL_H_

#include "fcml_types.h"
#include "fcml_ceh.h"

/* List. */

typedef struct fcml_st_coll_list_element {
	struct fcml_st_coll_list_element *prev;
	struct fcml_st_coll_list_element *next;
	fcml_ptr item;
} fcml_st_coll_list_element;

typedef struct fcml_st_coll_list {
	struct fcml_st_coll_list_element *head;
	struct fcml_st_coll_list_element *tail;
	fcml_int32_t size;
} fcml_st_coll_list;

typedef void (*fcml_fp_coll_list_action)( fcml_ptr item_value, fcml_ptr args );

fcml_st_coll_list *fcml_fn_coll_list_alloc_with_args( fcml_ptr handler_args );
fcml_st_coll_list *fcml_fn_coll_list_alloc();
fcml_st_coll_list_element *fcml_fn_coll_list_add_front( fcml_st_coll_list *list, fcml_ptr item );
fcml_st_coll_list_element *fcml_fn_coll_list_add_back( fcml_st_coll_list *list, fcml_ptr item );
fcml_st_coll_list_element *fcml_fn_coll_list_insert( fcml_st_coll_list_element *prev_element, fcml_ptr item );
void fcml_fn_coll_list_traverse( fcml_st_coll_list *list, fcml_fp_coll_list_action item_handler, fcml_ptr item_handler_args );
void fcml_fn_coll_list_remove( fcml_st_coll_list *list, fcml_st_coll_list_element *element );
void fcml_fn_coll_list_free( fcml_st_coll_list *list, fcml_fp_coll_list_action item_handler, fcml_ptr item_handler_args );

/* Hash map. */

#define FCML_COLL_MAP_DEFAULT_FACTOR		0.75

// Hash & Equals for strings.

typedef void (*fcml_fnp_coll_map_entry_handler) ( fcml_ptr key, fcml_ptr value, fcml_ptr args );
typedef fcml_uint32_t (*fcml_fnp_coll_map_key_hash) ( fcml_ptr key );
typedef fcml_bool (*fcml_fnp_coll_map_key_equals) ( fcml_ptr key1, fcml_ptr key2 );

typedef struct fcml_st_coll_map_descriptor {
	fcml_fnp_coll_map_key_hash hash_function;
	fcml_fnp_coll_map_key_equals equals_function;
	fcml_fnp_coll_map_entry_handler entry_free_function;
	fcml_ptr entry_free_args;
} fcml_st_coll_map_descriptor;

typedef fcml_ptr fcml_coll_map;

fcml_coll_map *fcml_fn_coll_map_alloc( fcml_st_coll_map_descriptor *descriptor, fcml_uint32_t capacity, fcml_ceh_error *error );
fcml_coll_map *fcml_fn_coll_map_alloc_factor( fcml_st_coll_map_descriptor *descriptor, fcml_uint32_t capacity, float load_factor, fcml_ceh_error *error );
void fcml_fn_coll_map_put( fcml_coll_map *map, fcml_ptr key, fcml_ptr value, fcml_ceh_error *error );
fcml_ptr fcml_fn_coll_map_get( fcml_coll_map *map, fcml_ptr key );
fcml_uint32_t fcml_fn_coll_map_size( fcml_coll_map *map );
void fcml_fn_coll_map_iterate( fcml_coll_map *map, fcml_fnp_coll_map_entry_handler item_handler );
void fcml_fn_coll_map_clear( fcml_coll_map *map );
void fcml_fn_coll_map_remove( fcml_coll_map *map, fcml_ptr key );
void fcml_fn_coll_map_free( fcml_coll_map *map );

// Builtin hash code and equals implementations.

fcml_uint32_t fcml_fnp_coll_map_key_hash_string( fcml_ptr key );
fcml_bool fcml_fnp_coll_map_key_equals_string( fcml_ptr key1, fcml_ptr key2 );
fcml_uint32_t fcml_fnp_coll_map_key_hash_uint32( fcml_ptr key );
fcml_bool fcml_fnp_coll_map_key_equals_uint32( fcml_ptr key1, fcml_ptr key2 );

extern fcml_st_coll_map_descriptor fcml_coll_map_descriptor_string;

#endif /* FCML_COLL_H_ */
