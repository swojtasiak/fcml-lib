/*
 * FCML - Free Code Manipulation Library.
 * Copyright (C) 2010-2014 Slawomir Wojtasiak
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

#include <fcml_symbols.h>

#include "fcml_coll.h"
#include "fcml_env_int.h"

void LIB_CALL fcml_fn_symbol_free( fcml_st_symbol *symbol ) {
	if( symbol ) {
		if( symbol->symbol ) {
			fcml_fn_env_str_strfree( symbol->symbol );
		}
		fcml_fn_env_memory_free( symbol );
	}
}

void fcml_itf_eff_free_symbol( fcml_ptr key, fcml_ptr value, fcml_ptr args ) {
	/* Key do not have to be freed, because it the same symbol as in symbol descriptor. */
	if( value ) {
		/* Free symbol structure. */
		fcml_st_symbol *symbol = (fcml_st_symbol*)value;
		fcml_fn_symbol_free( symbol );
	}
}

fcml_st_symbol_table LIB_CALL fcml_fn_symbol_table_alloc() {
	fcml_st_coll_map_descriptor desc = fcml_coll_map_descriptor_string;
	desc.entry_free_function = &fcml_itf_eff_free_symbol;
	fcml_int error;
	fcml_coll_map symbol_table = fcml_fn_coll_map_alloc( &desc, 1, &error );
	return symbol_table;
}

fcml_st_symbol* LIB_CALL fcml_fn_symbol_alloc() {
	return (fcml_st_symbol*)fcml_fn_env_memory_alloc_clear( sizeof( fcml_st_symbol ) );
}

fcml_ceh_error LIB_CALL fcml_fn_symbol_add( fcml_st_symbol_table symbol_table, fcml_st_symbol *symbol ) {
	fcml_int error = FCML_COLL_ERROR_NO_ERROR;
	fcml_fn_coll_map_put( (fcml_coll_map)symbol_table, symbol->symbol, symbol, &error );
	if( error ) {
		return FCML_CEH_GEC_OUT_OF_MEMORY;
	}
	return FCML_CEH_GEC_NO_ERROR;
}

fcml_ceh_error LIB_CALL fcml_fn_symbol_add_raw( fcml_st_symbol_table symbol_table, fcml_string symbol, fcml_int64_t value ) {
	fcml_coll_map symbol_map = (fcml_coll_map)symbol_table;
	fcml_st_symbol *sym = (fcml_st_symbol*)fcml_fn_env_memory_alloc( sizeof( fcml_st_symbol ) );
	if( !sym ) {
		return FCML_CEH_GEC_OUT_OF_MEMORY;
	}
	sym->symbol = fcml_fn_env_str_strdup( symbol );
	if( !sym->symbol ) {
		fcml_fn_env_memory_free( sym );
		return FCML_CEH_GEC_OUT_OF_MEMORY;
	}
	sym->value = value;
	fcml_int error = FCML_COLL_ERROR_NO_ERROR;
	fcml_fn_coll_map_put( symbol_map, sym->symbol, sym, &error );
	if( error ) {
		fcml_fn_env_str_strfree( sym->symbol );
		fcml_fn_env_memory_free( sym );
		return FCML_CEH_GEC_OUT_OF_MEMORY;
	}
	return FCML_CEH_GEC_NO_ERROR;
}

void LIB_CALL fcml_fn_symbol_remove( fcml_st_symbol_table symbol_table, fcml_string symbol ) {
	fcml_coll_map symbol_map = (fcml_coll_map)symbol_table;
	if( symbol_table && symbol ) {
		fcml_fn_coll_map_remove( symbol_map, symbol );
	}
}

fcml_st_symbol* LIB_CALL fcml_fn_symbol_get( fcml_st_symbol_table symbol_table, fcml_string symbol ) {
	fcml_coll_map symbol_map = (fcml_coll_map)symbol_table;
	if( symbol_map && symbol ) {
		return (fcml_st_symbol*)fcml_fn_coll_map_get(symbol_map, symbol );
	}
	return NULL;
}

void LIB_CALL fcml_fn_symbol_remove_all( fcml_st_symbol_table symbol_table ) {
	fcml_coll_map symbol_map = (fcml_coll_map)symbol_table;
	if( symbol_map ) {
		fcml_fn_coll_map_clear( symbol_map );
	}
}

void LIB_CALL fcml_fn_symbol_table_free( fcml_st_symbol_table symbol_table ) {
	fcml_coll_map symbol_map = (fcml_coll_map)symbol_table;
	if( symbol_map ) {
		fcml_fn_coll_map_free( symbol_map );
	}
}

