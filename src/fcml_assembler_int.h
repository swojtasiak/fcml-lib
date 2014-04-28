/*
 * fcml_assembler_int.h
 *
 *  Created on: Apr 28, 2014
 *      Author: tas
 */

#ifndef FCML_ASSEMBLER_INT_H_
#define FCML_ASSEMBLER_INT_H_

#include <fcml_dialect.h>

/**
 * Extracts dialect from assembler instance.
 *
 * @param assembler Assembler dialect should be extracted from.
 * @return Extracted dialect.
 */
fcml_st_dialect *fcml_fn_assembler_extract_dialect( fcml_st_assembler *assembler );

#endif /* FCML_ASSEMBLER_INT_H_ */
