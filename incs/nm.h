/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 23:40:20 by xel               #+#    #+#             */
/*   Updated: 2024/01/26 11:30:17 by xel              ###   ########.fr       */
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

bool manage_flag(int ac, char **av, u64 *flags);
void nm(char *file_name, const u64 flags);
void handle_64(Elf64_Ehdr *elf_header, char *base_address, u64 flags);
void free_sym_list(t_sym_list **sym_list, u16 n_sym);

#endif