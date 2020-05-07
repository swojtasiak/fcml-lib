/*
 * FCML - Free Code Manipulation Library.
 * Copyright (C) 2010-2015 Slawomir Wojtasiak
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

#ifndef FCML_COLL_H_
#define FCML_COLL_H_

#include <fcml_types.h>

#include "fcml_ceh.h"

/***********************/
/* Bidirectional List. */
/***********************/

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

typedef void (*fcml_fp_coll_list_action)(fcml_ptr item_value, fcml_ptr args);

fcml_st_coll_list* fcml_fn_coll_list_alloc_with_args(fcml_ptr handler_args);

fcml_st_coll_list* fcml_fn_coll_list_alloc();

fcml_st_coll_list_element* fcml_fn_coll_list_add_front(fcml_st_coll_list *list,
        const fcml_ptr item);

fcml_st_coll_list_element* fcml_fn_coll_list_add_back(fcml_st_coll_list *list,
        const fcml_ptr item);

fcml_st_coll_list_element* fcml_fn_coll_list_insert(fcml_st_coll_list *list,
        fcml_st_coll_list_element *prev_element, const fcml_ptr item);

void fcml_fn_coll_list_free(fcml_st_coll_list *list,
        fcml_fp_coll_list_action item_handler,
        const fcml_ptr item_handler_args);

/*************/
/* Hash Map. */
/*************/

#define FCML_COLL_ERROR_NO_ERROR			0x0000
#define FCML_COLL_ERROR_OUT_OF_MEMORY		0x0001
#define FCML_COLL_ERROR_MAP_FULL			0x0002
#define FCML_COLL_ERROR_BAD_ARGS			0x0003

#define FCML_COLL_MAP_DEFAULT_FACTOR		0.75

/* Hash & Equals for strings.*/

typedef void (*fcml_fnp_coll_map_entry_handler)(fcml_ptr key, fcml_ptr value,
        fcml_ptr args);

typedef fcml_bool (*fcml_fnp_coll_map_entry_handler_if)(fcml_ptr key,
        fcml_ptr value, fcml_ptr args);

typedef fcml_uint32_t (*fcml_fnp_coll_map_key_hash)(fcml_ptr key);

typedef fcml_bool (*fcml_fnp_coll_map_key_equals)(fcml_ptr key1, fcml_ptr key2);

typedef struct fcml_st_coll_map_descriptor {
    fcml_fnp_coll_map_key_hash hash_function;
    fcml_fnp_coll_map_key_equals equals_function;
    fcml_fnp_coll_map_entry_handler entry_free_function;
    fcml_ptr entry_free_args;
} fcml_st_coll_map_descriptor;

typedef fcml_ptr fcml_coll_map;

fcml_coll_map fcml_fn_coll_map_alloc(
        const fcml_st_coll_map_descriptor *descriptor, fcml_uint32_t capacity,
        fcml_int *error);

void fcml_fn_coll_map_put(fcml_coll_map map, const fcml_ptr key,
        const fcml_ptr value, fcml_int *error);

fcml_ptr fcml_fn_coll_map_get(fcml_coll_map map, const fcml_ptr key);

fcml_uint32_t fcml_fn_coll_map_size(const fcml_coll_map map);

void fcml_fn_coll_map_clear(fcml_coll_map map);

void fcml_fn_coll_map_remove(fcml_coll_map map, const fcml_ptr key);

void fcml_fn_coll_map_remove_if(fcml_coll_map map,
        fcml_fnp_coll_map_entry_handler_if item_handler,
        const fcml_ptr item_handler_args);

void fcml_fn_coll_map_free(fcml_coll_map map);

extern fcml_st_coll_map_descriptor fcml_coll_map_descriptor_string;
extern fcml_st_coll_map_descriptor fcml_coll_map_descriptor_uint32;

#endif /* FCML_COLL_H_ */
