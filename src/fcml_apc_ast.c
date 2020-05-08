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

#include <string.h>
#include <fcml_errors.h>
#include <fcml_symbols.h>

#include "fcml_env_int.h"
#include "fcml_apc_ast.h"
#include "fcml_utils.h"
#include "fcml_trace.h"
#include "fcml_messages.h"

struct fcml_ist_ast_extracted_symbols {
    /* List of extracted symbols. */
    fcml_st_coll_list *symbols;
};

fcml_st_ast_node *fcml_fn_ast_alloc_node_integer(
    fcml_st_ast_val_integer *integer_value) {

    FCML_ENV_ALLOC_CLEAR(node, fcml_st_ast_node);
    if (!node) {
        return NULL;
    }
    
    FCML_ENV_ALLOC_CLEAR(value_node, fcml_st_ast_node_value);
    if (!value_node) {
        fcml_fn_env_memory_free(node);
        return NULL;
    }

    value_node->type = FCML_EN_ET_INTEGER;
    value_node->integer_value = *integer_value;

    node->type = FCML_EN_TN_VALUE;
    node->node = value_node;

    return node;
}

fcml_st_ast_node *fcml_fn_ast_alloc_node_float(
    fcml_st_ast_val_float *float_value) {

    FCML_ENV_ALLOC_CLEAR(node, fcml_st_ast_node);
    if (!node) {
        return NULL;
    }

    FCML_ENV_ALLOC_CLEAR(exp_node, fcml_st_ast_node_value);
    if (!exp_node) {
        fcml_fn_env_memory_free(node);
        return NULL;
    }

    exp_node->type = FCML_EN_ET_FLOAT;
    exp_node->float_value = *float_value;

    node->type = FCML_EN_TN_VALUE;
    node->node = exp_node;

    return node;
}

fcml_st_ast_node *fcml_fn_ast_alloc_node_pseudo_operation(
    fcml_string mnemonic, fcml_usize length, fcml_st_ast_node *exp
) {

    fcml_st_ast_node *operand_list =
        fcml_fn_ast_alloc_node_operand_list(exp, NULL);

    if (!operand_list) {
        return NULL;
    }

    fcml_st_ast_node *pseudo_operation = fcml_fn_ast_alloc_node_instruction(0,
        mnemonic, length, 0, operand_list);
    if (!pseudo_operation) {
        fcml_fn_ast_free_node(operand_list);
        return NULL;
    }

    return pseudo_operation;
}

fcml_st_ast_node *fcml_fn_ast_alloc_node_instruction(fcml_prefixes prefixes,
    fcml_string mnemonic, fcml_usize length, fcml_hints hints,
    fcml_st_ast_node *operands_list) {

    FCML_ENV_ALLOC_CLEAR(node, fcml_st_ast_node);
    if (!node) {
        return NULL;
    }

    FCML_ENV_ALLOC_CLEAR(instruction_node, fcml_st_ast_node_instruction);
    if (!instruction_node) {
        fcml_fn_env_memory_free(node);
        return NULL;
    }

    instruction_node->mnemonic = (fcml_string)fcml_fn_env_str_strldup(mnemonic,
            length);
    
    if (!instruction_node->mnemonic) {
        fcml_fn_env_memory_free(node);
        fcml_fn_env_memory_free(instruction_node);
        return NULL;
    }

    instruction_node->operands = operands_list;
    instruction_node->hints = hints;
    instruction_node->prefixes = prefixes;

    node->type = FCML_EN_TN_INSTRUCTION;
    node->node = instruction_node;

    return node;
}

fcml_st_ast_node *fcml_fn_ast_alloc_node_virtual(fcml_bool sae,
        fcml_bool er_enabled, fcml_uint8_t er_value) {

    FCML_ENV_ALLOC_CLEAR(node, fcml_st_ast_node);
    if (!node) {
        return NULL;
    }

    FCML_ENV_ALLOC_CLEAR(virtual_node, fcml_st_ast_node_virtual);
    if (!virtual_node) {
        fcml_fn_env_memory_free(node);
        return NULL;
    }

    if (er_enabled) {
        virtual_node->decorators.er.is_not_null = FCML_TRUE;
        virtual_node->decorators.er.value = er_value;
    }

    virtual_node->decorators.sae = sae;

    node->type = FCML_EN_TN_VIRTUAL;
    node->node = virtual_node;

    return node;
}

fcml_st_ast_node *fcml_fn_ast_decorate_effective_address(
        fcml_st_ast_node *node,
        fcml_st_register *opmask_reg_decorator,
        fcml_bool zero_decorator) {

    fcml_st_operand_decorators *decorators =
            &((fcml_st_ast_node_effective_address*)node->node)->decorators;

    if (opmask_reg_decorator) {
        decorators->operand_mask_reg = *opmask_reg_decorator;
    }

    decorators->z = zero_decorator;
    return node;
}

fcml_st_ast_node *fcml_fn_ast_alloc_node_register(fcml_st_register *reg,
        fcml_st_register *opmask_reg_decorator, fcml_bool zero_decorator) {

    FCML_ENV_ALLOC_CLEAR(node, fcml_st_ast_node);
    if (!node) {
        return NULL;
    }

    FCML_ENV_ALLOC_CLEAR(reg_node, fcml_st_ast_node_register);
    if (!reg_node) {
        fcml_fn_env_memory_free(node);
        return NULL;
    }

    /* Decorators. */
    if (opmask_reg_decorator) {
        reg_node->decorators.operand_mask_reg = *opmask_reg_decorator;
    }

    reg_node->decorators.z = zero_decorator;
    reg_node->reg = *reg;

    node->type = FCML_EN_TN_REG;
    node->node = reg_node;

    return node;
}

fcml_st_ast_node *fcml_fn_ast_alloc_node_operand_list(
    fcml_st_ast_node *operand_l,
    fcml_st_ast_node *operand_r) 
{

    fcml_st_ast_node *operand_list_node = NULL;
    fcml_st_ast_node_operand_list *operand_list = NULL;

    if (operand_l->type != FCML_EN_TN_OPERAND_LIST) {

        operand_list_node = (fcml_st_ast_node*)fcml_fn_env_memory_alloc_clear(
                sizeof(fcml_st_ast_node));

        if (!operand_list_node) {
            return NULL;
        }

        operand_list = (fcml_st_ast_node_operand_list*)
            fcml_fn_env_memory_alloc_clear(
                sizeof(fcml_st_ast_node_operand_list));

        if (!operand_list) {
            fcml_fn_env_memory_free(operand_list_node);
            return NULL;
        }

        operand_list_node->type = FCML_EN_TN_OPERAND_LIST;
        operand_list_node->node = operand_list;
        operand_list->operands = fcml_fn_coll_list_alloc();

        if (!operand_list->operands) {
            fcml_fn_env_memory_free(operand_list_node);
            fcml_fn_env_memory_free(operand_list);
            return NULL;
        }

        if (!fcml_fn_coll_list_add_back(operand_list->operands, operand_l)
                || (operand_r != NULL && !fcml_fn_coll_list_add_back(
                        operand_list->operands, operand_r))) {

            fcml_fn_env_memory_free(operand_list_node);
            fcml_fn_env_memory_free(operand_list);
            fcml_fn_coll_list_free(operand_list->operands, NULL, NULL);
            return NULL;
        }

    } else {

        operand_list_node = operand_l;
        operand_list = (fcml_st_ast_node_operand_list*)operand_l->node;

        if (!fcml_fn_coll_list_add_back(operand_list->operands, operand_r)) {
            return NULL;
        }
    }

    return operand_list_node;
}

fcml_st_symbol *fcml_fn_ast_alloc_node_define_symbol(fcml_ip ip,
    fcml_string symbol_name, fcml_usize length) {

    FCML_ENV_ALLOC_CLEAR(symbol, fcml_st_symbol);
    if (!symbol) {
        return FCML_FALSE;
    }

    /* Allocate symbol. */
    symbol->symbol = (fcml_string)fcml_fn_env_str_strldup(symbol_name, length);
    if (!symbol->symbol) {
        fcml_fn_env_memory_free(symbol);
        return NULL;
    }

    symbol->value = (fcml_int64_t)ip;

    return symbol;
}

fcml_st_ast_node *fcml_fn_ast_alloc_node_use_symbol(fcml_string symbol_name,
        fcml_usize length) {

    FCML_ENV_ALLOC_CLEAR(node, fcml_st_ast_node);
    if (!node) {
        return NULL;
    }

    FCML_ENV_ALLOC_CLEAR(symbol_node, fcml_st_ast_node_use_symbol);
    if (!symbol_node){
        fcml_fn_env_memory_free(node);
        return NULL;
    }

    /* Allocate symbol name. */
    symbol_node->symbol = (fcml_string)fcml_fn_env_str_strldup(symbol_name,
            length);

    if (!symbol_node->symbol) {
        fcml_fn_env_memory_free(symbol_node);
        fcml_fn_env_memory_free(node);
        return NULL;
    }

    node->node = symbol_node;
    node->type = FCML_EN_TN_USE_SYMBOL;

    return node;
}

fcml_st_ast_node *fcml_fn_ast_alloc_node_exp(fcml_en_ast_exp_node_operator op,
    fcml_st_ast_node *exp_left, fcml_st_ast_node *exp_right) {

    FCML_ENV_ALLOC_CLEAR(node, fcml_st_ast_node);
    if (!node) {
        return NULL;
    }

    FCML_ENV_ALLOC_CLEAR(exp_node, fcml_st_ast_node_exp);
    if (!exp_node) {
        fcml_fn_env_memory_free(node);
        return NULL;
    }

    exp_node->l = exp_left;
    exp_node->r = exp_right;
    exp_node->op = op;

    node->type = FCML_EN_TN_EXP;
    node->node = exp_node;

    return node;
}

fcml_st_ast_node *fcml_fn_ast_alloc_node_far_pointer(
    fcml_st_ast_node *segment_selector,
    fcml_st_ast_node *offset) {

    FCML_ENV_ALLOC_CLEAR(node, fcml_st_ast_node);
    if (!node) {
        return NULL;
    }

    FCML_ENV_ALLOC_CLEAR(fp_node, fcml_st_ast_node_far_pointer);
    if (!fp_node) {
        fcml_fn_env_memory_free(node);
        return NULL;
    }

    fp_node->segment_selector = segment_selector;
    fp_node->offset = offset;

    node->type = FCML_EN_TN_FAR_POINTER;
    node->node = fp_node;

    return node;
}

fcml_st_ast_node *fcml_fn_ast_set_effective_address_hins(
    fcml_st_ast_node *effective_address_node,
    fcml_hints hints) {

    fcml_st_ast_node_effective_address *effective_address =
        (fcml_st_ast_node_effective_address *) effective_address_node->node;

    effective_address->instruction_hints |= hints;
    return effective_address_node;
}

fcml_st_ast_node *fcml_fn_ast_set_effective_address_details(
    fcml_st_register *segment_selector, fcml_st_size_operator *size_operator,
    fcml_uint8_t bcast_decorator, fcml_st_ast_node *effective_address_node) {

    fcml_st_ast_node_effective_address *effective_address =
        (fcml_st_ast_node_effective_address *)effective_address_node->node;

    if (segment_selector) {
        effective_address->segment_selector = *segment_selector;
    }

    if (bcast_decorator > 0) {
        effective_address->decorators.bcast.is_not_null = FCML_TRUE;
        effective_address->decorators.bcast.value = bcast_decorator;
    }

    /* Size operator is optional because not all assembler dialects allows 
     * to specify it here.
     */
    if (size_operator) {
        effective_address->size_operator = size_operator->size;
        if (size_operator->multimedia) {
            effective_address->addressing_hints |=
                FCML_OP_HINT_MULTIMEDIA_INSTRUCTION;
        }
    }

    return effective_address_node;
}

fcml_st_ast_node *fcml_fn_ast_set_displacemnt(
    fcml_st_ast_node *displacement, fcml_st_ast_node *effective_address_node) {

    fcml_st_ast_node_effective_address *effective_address =
        (fcml_st_ast_node_effective_address *)effective_address_node->node;

    if (displacement) {
        effective_address->displacement = displacement;
    }

    return effective_address_node;
}

fcml_st_ast_node *fcml_fn_ast_alloc_node_effective_address(
    fcml_st_register *base, fcml_st_register *index,
    fcml_st_ast_val_integer *scale_factor, fcml_st_ast_node *displacement,
    fcml_bool uminus_displacement, fcml_hints hints) {

    FCML_ENV_ALLOC_CLEAR(node, fcml_st_ast_node);
    if (!node) {
        return NULL;
    }

    FCML_ENV_ALLOC_CLEAR(ea_node, fcml_st_ast_node_effective_address);
    if (!ea_node) {
        fcml_fn_env_memory_free(node);
        return NULL;
    }

    ea_node->addressing_hints = hints;

    if (base) {
        ea_node->base = *base;
    }

    if (index) {
        ea_node->index = *index;
    }

    if (scale_factor) {
        ea_node->scale_factor = *scale_factor;
    }

    if (displacement) {
        ea_node->displacement = (uminus_displacement) ?
            fcml_fn_ast_alloc_node_uminus(displacement) : displacement;

        if (!ea_node->displacement) {
            /* Out of memory. */
            fcml_fn_env_memory_free(node);
            fcml_fn_env_memory_free(ea_node);
            return NULL;
        }
    }

    node->node = ea_node;
    node->type = FCML_EN_TN_EFFECTIVE_ADDRESS;

    return node;
}

fcml_st_ast_node *fcml_fn_ast_alloc_node_uminus(fcml_st_ast_node *exp) {

    fcml_st_ast_node *node;
    fcml_st_ast_node_uminus *uminus_node;

    /* Two unary minuses, so they can be reduced here. */
    if (exp->type == FCML_EN_TN_UMINUS) {
        uminus_node = (fcml_st_ast_node_uminus*)exp->node;
        node = uminus_node->exp;
        fcml_fn_env_memory_free(exp);
        fcml_fn_env_memory_free(uminus_node);
        return node;
    }

    node = (fcml_st_ast_node*)fcml_fn_env_memory_alloc_clear(
            sizeof(fcml_st_ast_node));

    if (!node) {
        return NULL;
    }

    uminus_node = (fcml_st_ast_node_uminus*)fcml_fn_env_memory_alloc_clear(
            sizeof(fcml_st_ast_node_uminus));

    if (!uminus_node) {
        fcml_fn_env_memory_free(node);
        return NULL;
    }

    uminus_node->exp = exp;

    node->node = uminus_node;
    node->type = FCML_EN_TN_UMINUS;

    return node;

}

static void free_operand_node_list_action(fcml_ptr item_value, fcml_ptr args) {
    fcml_st_ast_node *node = (fcml_st_ast_node*) item_value;
    fcml_fn_ast_free_node(node);
}

void fcml_fn_ast_free_node(fcml_st_ast_node *exp) {
    if (!exp) {
        return;
    } else {
        switch (exp->type) {
        case FCML_EN_TN_INSTRUCTION: {
            fcml_st_ast_node_instruction *instruction =
                    (fcml_st_ast_node_instruction*) exp->node;
            if (instruction->mnemonic) {
                fcml_fn_env_str_strfree(instruction->mnemonic);
            }
            fcml_fn_ast_free_node(instruction->operands);
        }
            break;
        case FCML_EN_TN_OPERAND_LIST: {
            fcml_st_ast_node_operand_list *operand_list =
                    (fcml_st_ast_node_operand_list*) exp->node;
            fcml_fn_coll_list_free(operand_list->operands,
                    free_operand_node_list_action, NULL);
        }
            break;
        case FCML_EN_TN_EXP: {
            fcml_st_ast_node_exp *expr = (fcml_st_ast_node_exp*) exp->node;
            fcml_fn_ast_free_node(expr->l);
            fcml_fn_ast_free_node(expr->r);
        }
            break;
        case FCML_EN_TN_UMINUS: {
            fcml_st_ast_node_uminus *uminus =
                    (fcml_st_ast_node_uminus*) exp->node;
            fcml_fn_ast_free_node(uminus->exp);
        }
            break;
        case FCML_EN_TN_FAR_POINTER: {
            fcml_st_ast_node_far_pointer *far_pointer =
                    (fcml_st_ast_node_far_pointer*) exp->node;
            fcml_fn_ast_free_node(far_pointer->offset);
            fcml_fn_ast_free_node(far_pointer->segment_selector);
        }
            break;
        case FCML_EN_TN_EFFECTIVE_ADDRESS: {
            fcml_st_ast_node_effective_address *effective_address =
                    (fcml_st_ast_node_effective_address*) exp->node;
            fcml_fn_ast_free_node(effective_address->displacement);
        }
            break;
        case FCML_EN_TN_USE_SYMBOL: {
            fcml_st_ast_node_use_symbol *symbol_node =
                    (fcml_st_ast_node_use_symbol*) exp->node;
            if (symbol_node->symbol) {
                fcml_fn_env_str_strfree(symbol_node->symbol);
            }
        }
            break;
        default:
            break;
        }

        if (exp->node) {
            fcml_fn_env_memory_free(exp->node);
        }

        fcml_fn_env_memory_free(exp);
    }
}

fcml_ceh_error fcml_fn_ast_visit_nodes(fcml_st_ast_node *ast_node,
        fcml_fnp_ast_node_visitor visitor, fcml_ptr visitor_args) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    if (ast_node) {
        switch (ast_node->type) {
        case FCML_EN_TN_INSTRUCTION: {
            fcml_st_ast_node_instruction *node_instruction =
                    (fcml_st_ast_node_instruction*) ast_node->node;
            error = fcml_fn_ast_visit_nodes(node_instruction->operands, visitor,
                    visitor_args);
            if (error)
                break;
            break;
        }
        case FCML_EN_TN_OPERAND_LIST: {
            fcml_st_ast_node_operand_list *operand_list =
                    (fcml_st_ast_node_operand_list*) ast_node->node;
            fcml_st_coll_list_element *current = operand_list->operands->head;
            int i = 0;
            while (current && i < FCML_OPERANDS_COUNT) {
                error = fcml_fn_ast_visit_nodes(
                        (fcml_st_ast_node*) current->item, visitor,
                        visitor_args);
                if (error)
                    break;
                current = current->next;
            }
            break;
        }
        case FCML_EN_TN_EXP: {
            fcml_st_ast_node_exp *exp_node =
                    (fcml_st_ast_node_exp*) ast_node->node;
            error = fcml_fn_ast_visit_nodes(exp_node->l, visitor, visitor_args);
            if (error)
                break;
            error = fcml_fn_ast_visit_nodes(exp_node->r, visitor, visitor_args);
            if (error)
                break;
            break;
        }
        case FCML_EN_TN_UMINUS: {
            fcml_st_ast_node_uminus *uminus_node =
                    (fcml_st_ast_node_uminus*) ast_node->node;
            error = fcml_fn_ast_visit_nodes(uminus_node->exp, visitor,
                    visitor_args);
            if (error)
                break;
            break;
        }
        case FCML_EN_TN_FAR_POINTER: {
            fcml_st_ast_node_far_pointer *far_pointer_node =
                    (fcml_st_ast_node_far_pointer*) ast_node->node;
            error = fcml_fn_ast_visit_nodes(far_pointer_node->offset, visitor,
                    visitor_args);
            if (error)
                break;
            error = fcml_fn_ast_visit_nodes(far_pointer_node->segment_selector,
                    visitor, visitor_args);
            if (error)
                break;
            break;
        }
        case FCML_EN_TN_EFFECTIVE_ADDRESS: {
            fcml_st_ast_node_effective_address *eff_addr_node =
                    (fcml_st_ast_node_effective_address*) ast_node->node;
            error = fcml_fn_ast_visit_nodes(eff_addr_node->displacement,
                    visitor, visitor_args);
            if (error)
                break;
            break;
        }
        default:
            /* Just visit current node. */
            break;
        }
        /* Visit original node. */
        error = visitor(ast_node, visitor_args);
    }
    return error;
}

/* Visitor responsible for extracting used symbols. */
static fcml_ceh_error extract_symbols_visitor(fcml_st_ast_node *node,
        fcml_ptr visitor_args) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    if (node->type == FCML_EN_TN_USE_SYMBOL) {
        fcml_st_ast_node_use_symbol *symbol_node =
                (fcml_st_ast_node_use_symbol*) node->node;
        if (symbol_node->symbol) {
            struct fcml_ist_ast_extracted_symbols *extracted_symbols =
                    (struct fcml_ist_ast_extracted_symbols*) visitor_args;
            if (!extracted_symbols->symbols) {
                extracted_symbols->symbols = fcml_fn_coll_list_alloc();
                if (!extracted_symbols->symbols) {
                    return FCML_CEH_GEC_OUT_OF_MEMORY;
                }
            }
            if (!fcml_fn_coll_list_add_front(extracted_symbols->symbols,
                    symbol_node->symbol)) {
                return FCML_CEH_GEC_OUT_OF_MEMORY;
            }
        }
    }

    return error;
}

/* Extracts all symbols used by whole instruction AST tree. */
fcml_ceh_error fcml_fn_ast_extract_used_symbols(fcml_st_ast_node *ast_tree,
        fcml_st_coll_list **extracted_symbols) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    struct fcml_ist_ast_extracted_symbols symbols;
    symbols.symbols = NULL;

    error = fcml_fn_ast_visit_nodes(ast_tree,
            &extract_symbols_visitor, &symbols);
    if (error) {
        if (symbols.symbols) {
            fcml_fn_coll_list_free(symbols.symbols, NULL, NULL);
            symbols.symbols = NULL;
        }
    }

    *extracted_symbols = symbols.symbols;

    return error;
}

void fcml_fn_ast_free_converted_cif(fcml_st_instruction *cif_instruction) {
    if (cif_instruction) {
        if (cif_instruction->mnemonic) {
            fcml_fn_env_str_strfree(cif_instruction->mnemonic);
        }
        fcml_fn_env_memory_free(cif_instruction);
    }
}

static inline float get_float_value(fcml_st_ast_node_value *value) {
    return value->float_value.value;
}

static inline fcml_int64_t get_integer_value(fcml_st_ast_node_value *value) {
    return (fcml_int64_t) value->integer_value.value;
}

static fcml_st_ast_val_integer convert_to_val_integer(fcml_int64_t val) {
    fcml_st_ast_val_integer int_value;
    int_value.value = (fcml_uint64_t) val;
    int_value.is_signed = val < 0;
    int_value.overflow = FCML_FALSE;
    return int_value;
}

static fcml_ceh_error eval_symbol(fcml_st_cif_converter_context *context,
        fcml_st_ast_node_use_symbol *symbol_node,
        fcml_st_ast_node_value *result) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    /* Get symbol definition from symbol table. */
    fcml_st_symbol *symbol_def = fcml_fn_symbol_get(context->symbol_table,
            symbol_node->symbol);

    if (!symbol_def && !context->ignore_undefined_symbols) {

        /* Symbol is undefined. */
        fcml_fn_msg_add_error_message(context->errors,
                FCML_MC_SEGMENT_UNDEFINED_SYMBOL,
                FCML_CEH_MEC_ERROR_UNDEFINED_SYMBOL, FCML_EN_CEH_EL_ERROR,
                symbol_node->symbol);

        error = FCML_CEH_GEC_UNDEFINED_SYMBOL;

    } else {

        /* Ignored symbols are treated as 0. Possibility to ignore
         * symbols is used in case of load-and-go assembler.
         */

        if (!symbol_def) {
            context->ignored_symbols++;
        }

        context->evaluated_symbols++;

        result->type = FCML_EN_ET_INTEGER;
        result->integer_value.is_signed = FCML_TRUE;
        result->integer_value.overflow = FCML_FALSE;
        result->integer_value.value = symbol_def ? symbol_def->value : 0L;

    }

    return error;
}

fcml_ceh_error fcml_ifn_ast_eval_exp(fcml_st_cif_converter_context *context,
        fcml_st_ast_node *exp, fcml_st_ast_node_value *result) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    switch (exp->type) {
    case FCML_EN_TN_VALUE: {
        *result = *((fcml_st_ast_node_value*) exp->node);
        if (result->integer_value.overflow) {
            fcml_fn_ceh_add_error(context->errors,
                    fcml_fn_msg_get_message(FCML_MC_CEH_GEC_VALUE_OUT_OF_RANGE),
                    FCML_CEH_MEW_WARN_VALUE_OUT_OF_RANGE, FCML_EN_CEH_EL_WARN);
        }
        break;
    }
    case FCML_EN_TN_UMINUS: {
        error = fcml_ifn_ast_eval_exp(context,
                ((fcml_st_ast_node_uminus*) exp->node)->exp, result);
        if (error) {
            return error;
        }
        if (result->type == FCML_EN_ET_INTEGER) {
            result->integer_value = convert_to_val_integer(
                    -((fcml_int64_t) result->integer_value.value));
        } else {
            result->float_value.value = -result->float_value.value;
        }
        break;
    }
    case FCML_EN_TN_USE_SYMBOL: {
        fcml_st_ast_node_use_symbol *symbol_node =
                (fcml_st_ast_node_use_symbol*) exp->node;
        error = eval_symbol(context, symbol_node, result);
        break;
    }
    case FCML_EN_TN_EXP: {
        fcml_st_ast_node_exp *exp_node = (fcml_st_ast_node_exp*) exp->node;
        fcml_st_ast_node_value lval = { (fcml_st_ast_value_node_type) 0 };
        fcml_st_ast_node_value rval = { (fcml_st_ast_value_node_type) 0 };
        fcml_ceh_error error = fcml_ifn_ast_eval_exp(context, exp_node->l,
                &lval);
        if (error) {
            return error;
        }
        error = fcml_ifn_ast_eval_exp(context, exp_node->r, &rval);
        if (error) {
            return error;
        }
        fcml_bool is_float = FCML_FALSE;
        result->type = FCML_EN_ET_INTEGER;
        if (lval.type == FCML_EN_ET_FLOAT || rval.type == FCML_EN_ET_FLOAT) {
            result->type = FCML_EN_ET_FLOAT;
            is_float = FCML_TRUE;
        }
        switch (exp_node->op) {
        case FCML_EN_EXN_SUB:
            if (is_float) {
                result->float_value.value =
                        get_float_value(&lval) - get_float_value(&rval);
            } else {
                result->integer_value = convert_to_val_integer(
                        get_integer_value(&lval) - get_integer_value(&rval));
            }
            break;
        case FCML_EN_EXN_ADD:
            if (is_float) {
                result->float_value.value =
                        get_float_value(&lval) + get_float_value(&rval);
            } else {
                result->integer_value = convert_to_val_integer(
                        get_integer_value(&lval) + get_integer_value(&rval));
            }
            break;
        case FCML_EN_EXN_MUL:
            if (is_float) {
                result->float_value.value =
                        get_float_value(&lval) * get_float_value(&rval);
            } else {
                result->integer_value = convert_to_val_integer(
                        get_integer_value(&lval) * get_integer_value(&rval));
            }
            break;
        case FCML_EN_EXN_DIV:
            if (is_float) {
                result->float_value.value =
                        get_float_value(&lval) / get_float_value(&rval);
            } else {
                fcml_int64_t divisor = get_integer_value(&rval);
                if (divisor == 0) {
                    fcml_fn_ceh_add_error(context->errors, "Division by zero.",
                            FCML_CEH_MEC_ERROR_DIVISION_BY_0,
                            FCML_EN_CEH_EL_ERROR);
                    error = FCML_CEH_GEC_INVALID_INPUT;
                } else {
                    result->integer_value = convert_to_val_integer(
                            get_integer_value(&lval) / divisor);
                }
            }
            break;
        }
        break;
    }
    default:
        FCML_TRACE("Unsupported AST node %d.", exp->type);
        error = FCML_CEH_GEC_INTERNAL_ERROR;
        break;
    }

    return error;
}

static fcml_ceh_error convert_value_to_immediate(fcml_st_ast_node_value *value,
        fcml_st_integer *immediate) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    immediate->is_signed = FCML_FALSE;
    if (value->type == FCML_EN_ET_FLOAT) {
        /* Floats are not supported yet. */
        error = FCML_CEH_GEC_FEATURE_NOT_SUPPORTED;
    } else if (value->type == FCML_EN_ET_INTEGER) {
        error = fcml_fn_utils_conv_int64_to_int(value->integer_value.value,
                value->integer_value.is_signed, immediate, FCML_ENUSF_ALL);
    } else {
        /* Unknown value type.*/
        FCML_TRACE("Unknown value type: %d.", value->type);
        error = FCML_CEH_GEC_INTERNAL_ERROR;
    }
    return error;
}

static fcml_ceh_error convert_far_pointer_node_to_operand(
        fcml_st_cif_converter_context *context,
        fcml_st_ast_node_far_pointer *far_pointer_node,
        fcml_st_far_pointer *far_pointer_operand) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    fcml_st_ast_node *segment_selector_node =
            far_pointer_node->segment_selector;
    fcml_st_ast_node *offset_node = far_pointer_node->offset;
    fcml_st_ast_node_value segment_selector_value;
    fcml_st_ast_node_value offset_value;

    /* Evaluate expressions.*/
    if ((error = fcml_ifn_ast_eval_exp(context, segment_selector_node,
            &segment_selector_value))) {
        return error;
    }

    if ((error = fcml_ifn_ast_eval_exp(context, offset_node, &offset_value))) {
        return error;
    }

    /* Segment selector and offset have to be integers.*/
    if (segment_selector_value.type != FCML_EN_ET_INTEGER
            || offset_value.type != FCML_EN_ET_INTEGER) {
        /* Only integer values are supported here.*/
        if (!fcml_fn_ceh_add_error(context->errors,
                "Segment selector and offset have to be an integer values.",
                FCML_CEH_MEC_ERROR_WRONG_VALUE_FORMAT, FCML_EN_CEH_EL_ERROR)) {
            error = FCML_CEH_GEC_OUT_OF_MEMORY;
        } else {
            error = FCML_CEH_GEC_INVALID_INPUT;
        }
        return error;
    }

    /* Set segment selector.*/
    fcml_bool overflow = FCML_FALSE;

    if (segment_selector_value.integer_value.is_signed) {
        fcml_int64_t segment =
                (fcml_int64_t) segment_selector_value.integer_value.value;
        if (segment <= FCML_INT16_MAX && segment >= FCML_INT16_MIN) {
            far_pointer_operand->segment = (fcml_int16_t) segment;
        } else {
            overflow = FCML_TRUE;
        }
    } else {
        if (segment_selector_value.integer_value.value <= FCML_UINT16_MAX) {
            far_pointer_operand->segment =
                    (fcml_uint16_t) segment_selector_value.integer_value.value;
        } else {
            overflow = FCML_TRUE;
        }
    }

    /* In case of far pointer calculation such problem is
     * reported as an error.
     */
    if (overflow) {
        if (!fcml_fn_ceh_add_error(context->errors,
                "Segment selector out of range.",
                FCML_CEH_MEC_ERROR_VALUE_OUT_OF_RANGE, FCML_EN_CEH_EL_ERROR)) {
            error = FCML_CEH_GEC_OUT_OF_MEMORY;
        } else {
            error = FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
        }
        return error;
    }

    /* Set offset.*/
    if (offset_value.integer_value.is_signed) {
        fcml_int64_t offset = (fcml_int64_t) offset_value.integer_value.value;
        if (offset <= FCML_INT16_MAX && offset >= FCML_INT16_MIN) {
            far_pointer_operand->offset16 = (fcml_int16_t) offset;
            far_pointer_operand->offset_size = FCML_DS_16;
        } else if (offset <= FCML_INT32_MAX && offset >= FCML_INT32_MIN) {
            far_pointer_operand->offset32 = (fcml_int32_t) offset;
            far_pointer_operand->offset_size = FCML_DS_32;
        } else {
            overflow = FCML_TRUE;
        }
    } else {
        fcml_uint64_t offset = offset_value.integer_value.value;
        if (offset <= FCML_UINT16_MAX) {
            far_pointer_operand->offset16 =
                    (fcml_int16_t) offset_value.integer_value.value;
            far_pointer_operand->offset_size = FCML_DS_16;
        } else if (offset <= FCML_UINT32_MAX) {
            far_pointer_operand->offset32 =
                    (fcml_uint32_t) offset_value.integer_value.value;
            far_pointer_operand->offset_size = FCML_DS_32;
        } else {
            overflow = FCML_TRUE;
        }
    }

    if (overflow) {
        if (!fcml_fn_ceh_add_error(context->errors, "Offset out of range.",
                FCML_CEH_MEC_ERROR_VALUE_OUT_OF_RANGE, FCML_EN_CEH_EL_ERROR)) {
            error = FCML_CEH_GEC_OUT_OF_MEMORY;
        } else {
            error = FCML_CEH_GEC_VALUE_OUT_OF_RANGE;
        }
    }

    return error;
}

static fcml_ceh_error convert_effective_address_node_to_operand(
        fcml_st_cif_converter_context *context,
        fcml_st_instruction *cif_instruction,
        fcml_st_ast_node_effective_address *effective_address_node,
        fcml_en_effective_address_form address_form, fcml_st_operand *operand) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    fcml_st_address *address = &(operand->address);

    /* Copy operands and instruction hints.*/
    operand->hints |= effective_address_node->addressing_hints;
    cif_instruction->hints |= effective_address_node->instruction_hints;

    operand->decorators = effective_address_node->decorators;

    fcml_st_effective_address *effective_address =
            &(address->effective_address);

    fcml_bool is_combined = !is_reg_undef(&(effective_address_node->base))
            || !is_reg_undef(&(effective_address_node->index));

    address->address_form = is_combined ? FCML_AF_COMBINED : FCML_AF_OFFSET;

    /* Evaluate displacement.*/
    if (effective_address_node->displacement) {

        fcml_st_ast_node_value value;

        if ((error = fcml_ifn_ast_eval_exp(context,
                effective_address_node->displacement, &value))) {
            return error;
        }

        if (value.type != FCML_EN_ET_INTEGER) {
            fcml_fn_ceh_add_error(context->errors,
                    "Displacement has to be an integer value.",
                    FCML_CEH_MEC_ERROR_WRONG_VALUE_FORMAT,
                    FCML_EN_CEH_EL_ERROR);
            error = FCML_CEH_GEC_INVALID_INPUT;
            return error;
        }

        fcml_st_integer disp_value;

        error = fcml_fn_utils_conv_int64_to_int(value.integer_value.value,
                value.integer_value.is_signed, &disp_value,
                is_combined ?
                        FCML_ENUSF_ALL :
                        (fcml_en_utils_size_flags) (FCML_ENUSF_16
                                | FCML_ENUSF_32 | FCML_ENUSF_64));
        if (error) {
            return error;
        }

        if (is_combined) {
            effective_address->displacement = disp_value;
        } else {
            error = fcml_fn_utils_integer_to_offset(&disp_value,
                    &(address->offset));
            if (error) {
                return error;
            }
        }

    }

    if (is_combined) {

        effective_address->base = effective_address_node->base;
        effective_address->index = effective_address_node->index;

        fcml_uint32_t scale_factor =
                (fcml_uint32_t) effective_address_node->scale_factor.value;
        if ((scale_factor == 0 || scale_factor == 1 || scale_factor == 2
                || scale_factor == 4 || scale_factor == 8)) {
            effective_address->scale_factor = (fcml_uint8_t) scale_factor;
        } else {
            fcml_fn_ceh_add_error(context->errors, "Wrong scale factor value.",
                    FCML_CEH_MEC_ERROR_WRONG_VALUE_FORMAT,
                    FCML_EN_CEH_EL_ERROR);
            return FCML_CEH_GEC_INVALID_INPUT;
        }

    }

    address->segment_selector.segment_selector =
            effective_address_node->segment_selector;
    address->size_operator = effective_address_node->size_operator;

    return error;
}

static fcml_ceh_error handle_ast_node(fcml_st_cif_converter_context *context,
        fcml_st_instruction *cif_instruction, fcml_st_operand *current_operand,
        fcml_st_ast_node *ast_node) {

    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;

    switch (ast_node->type) {
    case FCML_EN_TN_INSTRUCTION: {
        fcml_st_ast_node_instruction *node_instruction =
                (fcml_st_ast_node_instruction*) ast_node->node;
        /* Handle mnemonic.*/
        cif_instruction->prefixes = node_instruction->prefixes;
        cif_instruction->hints |= node_instruction->hints;
        cif_instruction->mnemonic = fcml_fn_env_str_strdup(
                node_instruction->mnemonic);
        if (cif_instruction->mnemonic) {
            /* Handle operands.*/
            if (node_instruction->operands) {
                error = handle_ast_node(context, cif_instruction,
                        NULL, node_instruction->operands);
            }
        } else {
            error = FCML_CEH_GEC_OUT_OF_MEMORY;
        }
        break;
    }
    case FCML_EN_TN_OPERAND_LIST: {
        fcml_st_ast_node_operand_list *operand_list =
                (fcml_st_ast_node_operand_list*) ast_node->node;
        if (operand_list->operands->size > FCML_OPERANDS_COUNT) {
            fcml_fn_ceh_add_error(context->errors, "Too many operands.",
                    FCML_CEH_MEC_ERROR_TO_MANY_OPERANDS, FCML_EN_CEH_EL_ERROR);
            error = FCML_CEH_GEC_INVALID_INPUT;
        } else {
            fcml_st_coll_list_element *current = operand_list->operands->head;
            int i = 0;
            while (current && i < FCML_OPERANDS_COUNT) {
                error = handle_ast_node(context, cif_instruction,
                        &(cif_instruction->operands[i++]),
                        (fcml_st_ast_node*) current->item);
                if (error) {
                    return error;
                }
                current = current->next;
            }
            cif_instruction->operands_count = operand_list->operands->size;
        }
        break;
    }
    case FCML_EN_TN_USE_SYMBOL:
    case FCML_EN_TN_EXP:
    case FCML_EN_TN_VALUE:
    case FCML_EN_TN_UMINUS: {
        fcml_st_ast_node_value value;
        error = fcml_ifn_ast_eval_exp(context, ast_node, &value);
        if (!error) {
            if (current_operand != NULL) {
                /* Convert value to immediate operand.*/
                error = convert_value_to_immediate(&value,
                        &(current_operand->immediate));
                if (!error) {
                    current_operand->type = FCML_OT_IMMEDIATE;
                }
            } else {
                FCML_TRACE_MSG("Operand is mandatory here.");
                error = FCML_CEH_GEC_INTERNAL_ERROR;
            }
        }
        break;
    }
    case FCML_EN_TN_VIRTUAL: {
        fcml_st_ast_node_virtual *node_virtual =
                (fcml_st_ast_node_virtual*) ast_node->node;
        current_operand->type = FCML_OT_VIRTUAL;
        current_operand->decorators = node_virtual->decorators;
        break;
    }
    case FCML_EN_TN_REG: {
        fcml_st_ast_node_register *node_register =
                (fcml_st_ast_node_register*) ast_node->node;
        current_operand->reg = node_register->reg;
        current_operand->type = FCML_OT_REGISTER;
        current_operand->decorators = node_register->decorators;
        break;
    }
    case FCML_EN_TN_FAR_POINTER: {
        fcml_st_ast_node_far_pointer *far_pointer_node =
                (fcml_st_ast_node_far_pointer*) ast_node->node;
        error = convert_far_pointer_node_to_operand(context,
                far_pointer_node, &(current_operand->far_pointer));
        current_operand->type = FCML_OT_FAR_POINTER;
        break;
    }
    case FCML_EN_TN_EFFECTIVE_ADDRESS: {
        fcml_st_ast_node_effective_address *effective_address_node =
                (fcml_st_ast_node_effective_address*) ast_node->node;
        error = convert_effective_address_node_to_operand(
                context, cif_instruction, effective_address_node,
                effective_address_node->address_form, current_operand);
        current_operand->type = FCML_OT_ADDRESS;
        break;
    }
    default:
        /* Unsupported node type. */
        error = FCML_CEH_GEC_INTERNAL_ERROR;
        break;
    }

    return error;
}

fcml_ceh_error fcml_fn_ast_to_cif_converter(
        fcml_st_cif_converter_context *context,
        fcml_st_ast_node *ast_instruction_node,
        fcml_st_instruction **out_instruction) {
    fcml_ceh_error error = FCML_CEH_GEC_NO_ERROR;
    context->evaluated_symbols = 0;
    fcml_st_instruction *instruction =
            (fcml_st_instruction*) fcml_fn_env_memory_alloc_clear(
                    sizeof(fcml_st_instruction));
    if (instruction) {
        error = handle_ast_node(context, instruction, NULL,
                ast_instruction_node);
        if (error) {
            fcml_fn_ast_free_converted_cif(instruction);
        } else {
            *out_instruction = instruction;
        }
    }
    return error;
}
