/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   applies_flag.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:27:24 by jucheval          #+#    #+#             */
/*   Updated: 2024/01/29 09:02:14 by xel              ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "nm.h"
#include "flag.h"

void
applies_flags_sym_list(t_sym_list **sym_list, const u16 n_sym, const u64 flags) {

    (void)mask_absolute_value_sym(sym_list, n_sym);
    
    if (!(flags & FLAG_P)) {
        (void)ascii_sort(sym_list, n_sym);
    }
    if (flags & FLAG_A) {
        (void)unmask_absolute_value_sym(sym_list, n_sym);
    }
    if (flags & FLAG_G) {
        (void)mask_internal_sym(sym_list, n_sym);
    }
    if (flags & FLAG_U) {
        (void)mask_undef_sym(sym_list, n_sym);
    }
    if (flags & FLAG_R && !(flags & FLAG_P)) {
        (void)reverse_sort_sym(sym_list, n_sym);    
    }
}

void
mask_internal_sym(t_sym_list **sym_list, const u16 n_sym) {
    
    for (u16 i = 0; i < n_sym - 1; i++) {
        if ((sym_list[i]->sym_type < 'A'
                || sym_list[i]->sym_type > 'Z')
                && sym_list[i]->sym_type != 'w')
            sym_list[i]->is_masked = true;
    }
}

void
mask_undef_sym(t_sym_list **sym_list, const u16 n_sym) {
    
    for (u16 i = 0; i < n_sym - 1; i++) {
        if (!sym_list[i]->is_undef)
            sym_list[i]->is_masked = true;
    }
}

void
mask_absolute_value_sym(t_sym_list **sym_list, const u16 n_sym) {
    
    for (u16 i = 0; i < n_sym - 1; i++) {
        if (sym_list[i]->sym_type == 'a')
            sym_list[i]->is_masked = true;
    }
}

void
unmask_absolute_value_sym(t_sym_list **sym_list, const u16 n_sym) {
    
    for (u16 i = 0; i < n_sym - 1; i++) {
        if (sym_list[i]->sym_type == 'a')
            sym_list[i]->is_masked = false;
    }
}

void
reverse_sort_sym(t_sym_list **sym_list, const u16 n_sym) {
    
    for (u16 i = 0, j = n_sym - 2; i < j; i++, j--) {
        swap_sym(&sym_list[i], &sym_list[j]);
    }
}