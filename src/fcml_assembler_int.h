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

#ifndef FCML_ASSEMBLER_INT_H_
#define FCML_ASSEMBLER_INT_H_

#include <fcml_dialect.h>

/**
 * Extracts dialect from assembler instance.
 *
 * @param assembler Assembler dialect should be extracted from.
 * @return Extracted dialect.
 */
fcml_st_dialect *fcml_fn_assembler_extract_dialect(fcml_st_assembler *assembler);

#endif /* FCML_ASSEMBLER_INT_H_ */
