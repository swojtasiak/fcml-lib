/*
 * fcml_coll.c
 *
 *  Created on: 10-03-2013
 *      Author: tAs
 */

#include <string.h>
#include "fcml_coll.h"
#include "fcml_env.h"
#include "fcml_ceh.h"

/* Bidirectional list.*/

fcml_st_coll_list *fcml_fn_coll_list_alloc() {
    fcml_st_coll_list *list =  (fcml_st_coll_list*)fcml_fn_env_memory_alloc( sizeof( fcml_st_coll_list ) );
    if( list ) {
        list->head = NULL;
        list->tail = NULL;
        list->size = 0;
    }
    return list;
}

fcml_st_coll_list_element *fcml_fn_coll_list_add_front( fcml_st_coll_list *list, fcml_ptr item ) {
	fcml_st_coll_list_element *element =  (fcml_st_coll_list_element*)fcml_fn_env_memory_alloc( sizeof( fcml_st_coll_list_element ) );
	if( element ) {
		element->next = list->head;
		if( list->head ) {
			list->head->prev = element;
		}
		element->prev = NULL;
		element->item = item;
		list->head = element;
		if( !list->tail ) {
			list->tail = element;
		}
		list->size++;
	}
	return element;
}

fcml_st_coll_list_element *fcml_fn_coll_list_add_back( fcml_st_coll_list *list, fcml_ptr item ) {
	fcml_st_coll_list_element *element =  (fcml_st_coll_list_element*)fcml_fn_env_memory_alloc( sizeof( fcml_st_coll_list_element ) );
	if( element ) {
		element->next = NULL;
		element->prev = list->tail;
		element->item = item;
		if( list->tail ) {
			list->tail->next = element;
		}
		list->tail = element;
		if( !list->head ) {
			list->head = element;
		}
		list->size++;
	}
	return element;
}

fcml_st_coll_list_element *fcml_fn_coll_list_insert( fcml_st_coll_list *list, fcml_st_coll_list_element *prev_element, fcml_ptr item ) {
	fcml_st_coll_list_element *element;
	if( prev_element ) {
		element = (fcml_st_coll_list_element*)fcml_fn_env_memory_alloc( sizeof( fcml_st_coll_list_element ) );
		if( element ) {
			element->item = item;
			element->prev = prev_element;
			element->next = prev_element->next;
			prev_element->next = element;
		}
	} else {
		element = fcml_fn_coll_list_add_front( list, item );
	}
	return element;
}

void fcml_fn_coll_list_traverse( fcml_st_coll_list *list, fcml_fp_coll_list_action item_handler, fcml_ptr item_handler_args ) {
	fcml_st_coll_list_element *current = list->head;
	while( current ) {
		(item_handler)( current->item, item_handler_args );
		current = current->next;
	}
}

void fcml_fn_coll_list_remove( fcml_st_coll_list *list, fcml_st_coll_list_element *element ) {
	fcml_st_coll_list_element *prev = element->prev;
	fcml_st_coll_list_element *next = element->next;
	if( prev ) {
		prev->next = next;
	} else {
		list->head = next;
	}
	if( next ) {
		next->prev = prev;
	} else {
		list->tail = prev;
	}
	list->size--;
	fcml_fn_env_memory_free( element );
}

void fcml_fn_coll_list_free( fcml_st_coll_list *list, fcml_fp_coll_list_action item_handler, fcml_ptr item_handler_args ) {
	fcml_st_coll_list_element *current = list->head;
	while( current ) {
		(item_handler)( current->item, item_handler_args );
		fcml_st_coll_list_element *tmp = current;
		current = current->next;
		fcml_fn_env_memory_free( tmp );
	}
	fcml_fn_env_memory_free(list);
}

/* Hash map. */

/* Internal data types dedicated for given implementation of the map.*/

struct fcml_ist_coll_map_entry {
	struct fcml_ist_coll_map_entry *next;
	fcml_uint32_t hash;
	fcml_ptr key;
	fcml_ptr value;
};

struct fcml_ist_coll_map {
	fcml_st_coll_map_descriptor descriptor;
	float load_factor;
	fcml_uint32_t boundary;
	fcml_uint32_t capacity;
	fcml_uint32_t size;
	fcml_uint32_t hash_mask;
	struct fcml_ist_coll_map_entry** map_entries;
};

fcml_st_coll_map_descriptor fcml_coll_map_descriptor_string = { fcml_fnp_coll_map_key_hash_string, fcml_fnp_coll_map_key_equals_string, NULL, NULL };
fcml_st_coll_map_descriptor fcml_coll_map_descriptor_uint32 = { fcml_fnp_coll_map_key_hash_uint32, fcml_fnp_coll_map_key_equals_uint32, NULL, NULL };

fcml_coll_map *fcml_fn_coll_map_alloc( fcml_st_coll_map_descriptor *descriptor, fcml_uint32_t capacity, fcml_ceh_error *error ) {
	return fcml_fn_coll_map_alloc_factor( descriptor, capacity, FCML_COLL_MAP_DEFAULT_FACTOR, error );
}

fcml_coll_map *fcml_fn_coll_map_alloc_factor( fcml_st_coll_map_descriptor *descriptor, fcml_uint32_t capacity, float load_factor, fcml_ceh_error *error ) {

	if( capacity > ( 1<< 31 ) ) {
		*error = FCML_CEH_GEC_INVALID_INPUT;
		return NULL;
	}

	int real_capacity = 2;
	while( real_capacity < capacity ) {
		real_capacity <<= 1;
	}

	struct fcml_ist_coll_map *map = fcml_fn_env_memory_alloc( sizeof( struct fcml_ist_coll_map ) );
	if( map == NULL ) {
		*error = FCML_CEH_GEC_OUT_OF_MEMORY;
		return NULL;
	}

	map->descriptor = *descriptor;

	/* Calculate and cache boundary to gain some performance from further calculations.*/
	map->load_factor = load_factor;
	map->boundary = real_capacity * load_factor;
	map->capacity = real_capacity;
	map->hash_mask = real_capacity - 1;
	map->size = 0;

	/* Allocate space for entries.*/
	map->map_entries = (struct fcml_ist_coll_map_entry**)fcml_fn_env_memory_alloc_clear( sizeof( struct fcml_ist_coll_map_entry* ) * real_capacity );
	if( !map->map_entries ) {
		fcml_fn_env_memory_free(map);
		*error = FCML_CEH_GEC_OUT_OF_MEMORY;
		return NULL;
	}

	return (fcml_coll_map)map;
}

fcml_uint32_t fcml_fn_coll_map_size( fcml_coll_map *map_int ) {
	struct fcml_ist_coll_map *map = (struct fcml_ist_coll_map*)map_int;
	return map->size;
}

fcml_bool fcml_ifn_coll_map_expand( struct fcml_ist_coll_map *map, fcml_ceh_error *error ) {

	if( map->capacity > FCML_INT32_MAX ) {
		/* Map reached its maximum capacity.*/
		*error = FCML_CEH_GEC_NO_SPACE_LEFT;
		return FCML_FALSE;
	}

	fcml_uint32_t new_capacity = map->capacity << 1;

	/* Allocate new map entries.*/
	struct fcml_ist_coll_map_entry** new_map_entries = fcml_fn_env_memory_alloc( new_capacity * sizeof( struct fcml_ist_coll_map_entry* ) );
	if( !new_map_entries ) {
		/* Can not*/
		*error = FCML_CEH_GEC_OUT_OF_MEMORY;
		return FCML_FALSE;
	}

	fcml_fn_env_memory_clear( new_map_entries, new_capacity * sizeof( struct fcml_ist_coll_map_entry* ) );

	fcml_uint32_t new_hash_mask = ( new_capacity - 1 );
	int i;
	for( i = 0; i < map->capacity; i++ ) {
		struct fcml_ist_coll_map_entry *entry = map->map_entries[i];
		if( entry ) {
			while( entry ) {
				struct fcml_ist_coll_map_entry *next_entry = entry->next;
				fcml_uint32_t new_index = new_hash_mask & entry->hash;
				entry->next = new_map_entries[new_index];
				new_map_entries[new_index] = entry;
				entry = next_entry;
			}
		}
	}

	fcml_fn_env_memory_free( map->map_entries );

	map->map_entries = new_map_entries;
	map->capacity = new_capacity;
	map->boundary = new_capacity * map->load_factor;
	map->hash_mask = new_hash_mask;

	return FCML_TRUE;
}

void fcml_fn_coll_map_put( fcml_coll_map *map_int, fcml_ptr key, fcml_ptr value, fcml_ceh_error *error ) {

	struct fcml_ist_coll_map *map = (struct fcml_ist_coll_map*)map_int;

	*error = FCML_CEH_GEC_NO_ERROR;

	fcml_st_coll_map_descriptor *descriptor = &(map->descriptor);
	fcml_uint32_t hash = descriptor->hash_function( key );
	fcml_uint32_t index = map->hash_mask & hash;

	struct fcml_ist_coll_map_entry *entry = map->map_entries[index];
	struct fcml_ist_coll_map_entry *current_entry = entry;

	/* Checking for entry with the same key.*/
	while( current_entry ) {
		if( current_entry->hash == hash && ( key == current_entry->key || descriptor->equals_function( key, current_entry->key ) ) ) {
			/* We found element with same key, so replace key and value.*/
			if( descriptor->entry_free_function ) {
				descriptor->entry_free_function( current_entry->key, current_entry->value, map->descriptor.entry_free_args );
			}
			current_entry->key = key;
			current_entry->value = value;
			return;
		}
		current_entry = current_entry->next;
	}

	/* Check if map should be already extended.*/
	if( entry && map->size > map->boundary ) {
		/* Currently we ignore errors, beacuse it really doesn't matter if*/
		/* there is no space in the map or on the heap.*/
		fcml_ceh_error error;
		if( fcml_ifn_coll_map_expand( map, &error ) ) {
			index = map->hash_mask & hash;
		}
	}

	struct fcml_ist_coll_map_entry *newEntry = fcml_fn_env_memory_alloc( sizeof( struct fcml_ist_coll_map_entry ) );
	if( !newEntry ) {
		*error = FCML_CEH_GEC_NO_ERROR;
		return;
	}

	newEntry->key = key;
	newEntry->value = value;
	newEntry->hash = hash;
	newEntry->next = map->map_entries[index];
	map->map_entries[index] = newEntry;
	map->size++;

}

void fcml_fn_coll_map_remove( fcml_coll_map *map_int, fcml_ptr key ) {
	struct fcml_ist_coll_map *map = (struct fcml_ist_coll_map*)map_int;
	fcml_uint32_t hash = map->descriptor.hash_function( key );
	int index = map->hash_mask & hash;
	struct fcml_ist_coll_map_entry *entry = map->map_entries[index];
	struct fcml_ist_coll_map_entry *previous_entry = NULL;
	while( entry ) {
		if( entry->hash == hash && ( key == entry->key || map->descriptor.equals_function( key, entry->key ) ) ) {
			/* We found entry, so remove it.*/
			if( map->descriptor.entry_free_function ) {
				map->descriptor.entry_free_function( entry->key, entry->value, map->descriptor.entry_free_args );
			}
			if( previous_entry ) {
				previous_entry->next = entry->next;
			} else {
				map->map_entries[index] = NULL;
			}
			fcml_fn_env_memory_free( entry );
			map->size--;
			return;
		}
		previous_entry = entry;
		entry = entry->next;
	}
	return;
}

void fcml_fn_coll_map_iterate( fcml_coll_map *map_int, fcml_fnp_coll_map_entry_handler item_handler ) {
	if( item_handler ) {
		struct fcml_ist_coll_map *map = (struct fcml_ist_coll_map*)map_int;
		fcml_uint32_t i;
		for( i = 0; i < map->capacity; i++ ) {
			struct fcml_ist_coll_map_entry *entry = map->map_entries[i];
			while( entry ) {
				item_handler( entry->key, entry->value, map->descriptor.entry_free_args );
				entry = entry->next;
			}
		}
	}
}

void fcml_fn_coll_map_clear( fcml_coll_map *map_int ) {
	struct fcml_ist_coll_map *map = (struct fcml_ist_coll_map*)map_int;
	fcml_uint32_t i;
	for( i = 0; i < map->capacity; i++ ) {
		struct fcml_ist_coll_map_entry *entry = map->map_entries[i];
		struct fcml_ist_coll_map_entry *next_entry;
		while( entry ) {
			next_entry = entry->next;
			if( map->descriptor.entry_free_function ) {
				map->descriptor.entry_free_function( entry->key, entry->value, map->descriptor.entry_free_args );
			}
			fcml_fn_env_memory_free( entry );
			entry = next_entry;
		}
		map->map_entries[i] = NULL;
	}
	map->size = 0;
}

fcml_ptr fcml_fn_coll_map_get( fcml_coll_map *map_int, fcml_ptr key ) {
	struct fcml_ist_coll_map *map = (struct fcml_ist_coll_map*)map_int;
	fcml_uint32_t hash = map->descriptor.hash_function( key );
	fcml_uint32_t index = map->hash_mask & hash;
	struct fcml_ist_coll_map_entry *entry = map->map_entries[index];
	/* Checking for entry with the same key.*/
	while( entry ) {
		if( entry->hash == hash && ( key == entry->key || map->descriptor.equals_function( key, entry->key ) ) ) {
			return entry->value;
		}
		entry = entry->next;
	}
	return NULL;
}

void fcml_fn_coll_map_free( fcml_coll_map *map_int ) {
	if( map_int ) {
		fcml_fn_coll_map_clear( map_int );
		struct fcml_ist_coll_map *map = (struct fcml_ist_coll_map*)map_int;
		if( map->map_entries ) {
		    fcml_fn_env_memory_free( map->map_entries );
		}
		fcml_fn_env_memory_free( map );
	}
}

/* Build-in Hash & Equals implementations.*/

fcml_uint32_t fcml_fnp_coll_map_key_hash_string ( fcml_ptr key ) {
	fcml_uint32_t hash = 0;
	fcml_string str_key = (fcml_string)key;
	int i;
	for (i = 0; str_key[i] != '\0'; i++) {
		hash = (hash << 6) | (hash >> 26);
		hash += (fcml_uint32_t) str_key[i];
	}
	return hash;
}

fcml_bool fcml_fnp_coll_map_key_equals_string( fcml_ptr key1, fcml_ptr key2 ) {
	return fcml_fn_env_str_strcmp( key1, key2 );
}

fcml_uint32_t fcml_fnp_coll_map_key_hash_uint32( fcml_ptr key ) {
	return *((fcml_uint32_t*)key);
}

fcml_bool fcml_fnp_coll_map_key_equals_uint32( fcml_ptr key1, fcml_ptr key2 ) {
	return *((fcml_uint32_t*)key1) == *((fcml_uint32_t*)key2);
}
