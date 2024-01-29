/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ascii_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 08:52:32 by xel               #+#    #+#             */
/*   Updated: 2024/01/29 09:09:22 by xel              ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "nm.h"

void
ascii_sort(t_sym_list **sym_list, const u16 n_sym) {
    
    for (u16 i = 0; i < n_sym - 1; ++i) {
        
        u16 min_index = i;
        for (u16 j = i + 1; j < n_sym - 1; ++j) {
            
            if (strcmp(sym_list[j]->sym_name, sym_list[min_index]->sym_name) < 0) {
                min_index = j;
            }
        }
        if (min_index != i) {
            swap_sym(&sym_list[i], &sym_list[min_index]);
        }
    }
}