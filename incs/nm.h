/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 23:40:20 by xel               #+#    #+#             */
/*   Updated: 2024/01/29 09:14:56 by xel              ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef NM_H
# define NM_H

// ========================================================================= //
//                                   Header                                  //
// ========================================================================= //

#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <elf.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>


// ========================================================================= //
//                                  Typedef                                  //
// ========================================================================= //

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;


// ========================================================================= //
//                                  Structure                                //
// ========================================================================= //

typedef struct s_sym_list {
    u64     sym_value;
    char    sym_type;
    char    *sym_name;
    bool    is_undef;
    bool    is_masked;
}   t_sym_list;

// ========================================================================= //
//                                  Prototype                                //
// ========================================================================= //

void nm(const char *file_name, const u64 flags);
void handle_32(const Elf32_Ehdr *elf_header, const char *base_address, const u64 flags);
void handle_64(const Elf64_Ehdr *elf_header, const char *base_address, const u64 flags);

bool manage_flag(int ac, char **av, u64 *flags);
void applies_flags_sym_list(t_sym_list **sym_list, const u16 n_sym, const u64 flags);

void ascii_sort(t_sym_list **sym_list, const u16 n_sym);

void free_sym_list(t_sym_list **sym_list, const u16 n_sym);
void swap_sym(t_sym_list **a, t_sym_list **b);

#endif