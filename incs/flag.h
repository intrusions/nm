/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 23:33:04 by xel               #+#    #+#             */
/*   Updated: 2024/01/26 14:34:07 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLAG_H
# define FLAG_H

// ========================================================================= //
//                                   Header                                  //
// ========================================================================= //

#include "nm.h"


// ========================================================================= //
//                                   Define                                  //
// ========================================================================= //

# define N_FLAGS    5

# define FLAG_A  0x01 << 1
# define FLAG_G  0x01 << 2
# define FLAG_P  0x01 << 3
# define FLAG_U  0x01 << 4
# define FLAG_R  0x01 << 5


// ========================================================================= //
//                               Prototypes                                  //
// ========================================================================= //

void mask_internal_sym(t_sym_list **sym_list, u16 num_symbols);
void mask_undef_sym(t_sym_list **sym_list, u16 num_symbols);
void mask_absolute_value_sym(t_sym_list **sym_list, u16 num_symbols);

void unmask_absolute_value_sym(t_sym_list **sym_list, u16 num_symbols);

void reverse_sort_sym(t_sym_list **sym_list, u16 num_symbols);


#endif