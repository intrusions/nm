/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 01:39:38 by xel               #+#    #+#             */
/*   Updated: 2024/01/02 01:46:40 by xel              ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "nm.h"
#include "flag.h"
#include "debug.h"

#if defined(__LP64__)
    #define ElfW(type) Elf64_ ## type
#else
    #define ElfW(type) Elf32_ ## type
#endif

void    read_elf_header(const char *file_name) {
    
    ElfW(Ehdr) header;
    FILE *file = fopen(file_name, "rb");

    if (file) {
        
        if (fread(&header, sizeof(header), 1, file)) {
            
            printf(
                "e_type: %d\n"
                "e_machine: %d\n"
                "e_version: %d\n"
                "e_entry: %ld\n"
                "e_phoff: %ld\n"
                "e_shoff: %ld\n"
                "e_flags: %d\n"
                "e_ehsize: %d\n"
                "e_phentsize: %d\n"
                "e_phnum: %d\n"
                "e_shentsize: %d\n"
                "e_shnum: %d\n"
                "e_shstrndx: %d\n",
                header.e_type,
                header.e_machine,
                header.e_version,
                header.e_entry,
                header.e_phoff,
                header.e_shoff,
                header.e_flags,
                header.e_ehsize,
                header.e_phentsize,
                header.e_phnum,
                header.e_shentsize,
                header.e_shnum,
                header.e_shstrndx
            );
            fclose(file);
        }
    }
}

void nm(char *file_name, const u64 flags) {
    __DEBUG_PRINT_FLAGS(flags, file_name);

    read_elf_header(file_name);
}
