/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   applies_flag.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:27:24 by jucheval          #+#    #+#             */
/*   Updated: 2024/01/26 14:28:35 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include "flag.h"

void mask_internal_sym(t_sym_list **sym_list, u16 num_symbols) {
    
    for (u16 i = 0; i < num_symbols - 1; i++) {
        if ((sym_list[i]->sym_type < 'A'
                || sym_list[i]->sym_type > 'Z')
                && sym_list[i]->sym_type != 'w')
            sym_list[i]->is_masked = true;
    }
}

void mask_undef_sym(t_sym_list **sym_list, u16 num_symbols) {
    
    for (u16 i = 0; i < num_symbols - 1; i++) {
        if (!sym_list[i]->is_undef)
            sym_list[i]->is_masked = true;
    }
}

void mask_absolute_value_sym(t_sym_list **sym_list, u16 num_symbols) {
    
    for (u16 i = 0; i < num_symbols - 1; i++) {
        if (sym_list[i]->sym_type == 'a')
            sym_list[i]->is_masked = true;
    }
}

void unmask_absolute_value_sym(t_sym_list **sym_list, u16 num_symbols) {
    
    for (u16 i = 0; i < num_symbols - 1; i++) {
        if (sym_list[i]->sym_type == 'a')
            sym_list[i]->is_masked = false;
    }
}

void reverse_sort_sym(t_sym_list **sym_list, u16 num_symbols) {
    
    (void)sym_list;
    (void)num_symbols;
}