/*
 * main.c
 *
 *  Created on: Mar 18, 2014
 *      Author: tas
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

#include <fcml_disassembler.h>

fcml_st_disassembler_context context = {0};

int main(int argc, char **argv) {

	// Interpret arguments.
	if( argc <= 1 ) {
		printf("Bad arguments.\n");
		exit(1);
	}

	int i;
	for( i = 1; i < argc; i++ ) {
		if( strcmp( argv[i], "-m16" ) == 0 ) {
			context.entry_point.addr_form = FCML_AF_16_BIT;
		} else if( strcmp( argv[i], "-m32" ) == 0 ) {
			context.entry_point.addr_form = FCML_AF_32_BIT;
		} else if( strcmp( argv[i], "-m64" ) == 0 ) {
			context.entry_point.addr_form = FCML_AF_64_BIT;
		} else if( strcmp( argv[i], "-ip" ) == 0 ) {
			if( ++i < argc ) {
				char *res;
				errno = 0;
				context.entry_point.ip.rip = strtoll( argv[i], &res, 16 );
				if ((errno == ERANGE && (context.entry_point.ip.rip == FCML_INT64_MAX || context.entry_point.ip.rip == FCML_INT64_MIN)) || (errno != 0 && context.entry_point.ip.rip == 0) || (argv[i] == res) ) {
				   perror("Wrong instruction pointer.");
				   exit(EXIT_FAILURE);
			   }
			} else {
				printf("IP not set.\n");
				exit(1);
			}
		} else if( strcmp( argv[i], "-s" ) == 0 ) {
			context.configuration.short_forms = FCML_TRUE;
		}
	}

	if( !context.entry_point.addr_form ) {
		printf("Addressing mode not specified.\n");
		exit(1);
	}

	return 0;
}
