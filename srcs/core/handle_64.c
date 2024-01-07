/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 06:46:29 by xel               #+#    #+#             */
/*   Updated: 2024/01/07 09:41:12 by xel              ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "nm.h"
#include "flag.h"
#include "debug.h"

// void    print_line(char *strtab, Elf64_Sym *symtab, u64 flags) {

//     char *sym_name = strtab + symtab->st_name;
//     i8 extension_ptr = strlen(sym_name) - 2;

//     if ((flags & FLAG_A) && (flags == FLAG_A)) {
//         printf("%s\n", strtab + symtab->st_name);

//     } else if ((flags & FLAG_G) && (flags == FLAG_G)) {
//         if (ELF64_ST_BIND(symtab->st_info) == STB_GLOBAL
//             || ELF64_ST_BIND(symtab->st_info) == STB_WEAK)
//             printf("%s\n", strtab + symtab->st_name);

//     } else if (flags & FLAG_P && (flags == FLAG_P)) {
//         if (memcmp(sym_name + extension_ptr, ".c", 2)
//             && memcmp(sym_name + extension_ptr, ".o", 2)
//             && strlen(sym_name))
//             printf("%s\n", strtab + symtab->st_name);
    
//     } else if (flags & FLAG_U && (flags == FLAG_U)) {
//         if ((ELF64_ST_BIND(symtab->st_info) == STB_GLOBAL
//             && symtab->st_shndx == SHN_UNDEF)
//             || ELF64_ST_BIND(symtab->st_info) == STB_WEAK)
//             printf("%s\n", strtab + symtab->st_name);
    
//     }
// }

void    print_line(char *strtab, Elf64_Sym *symtab, u64 flags) {
    (void)flags;

    if (symtab->st_shndx == SHN_UNDEF)
        printf("                ");
    else
        printf("%016lx ", (u64)symtab->st_value);

    printf("%s\n", strtab + symtab->st_name);
}


void    handle_64(Elf64_Ehdr *elf_header, char *base_address, u64 flags) {
    
    Elf64_Shdr *section_header = (Elf64_Shdr *)(base_address + elf_header->e_shoff);
    Elf64_Shdr *symtab_header = NULL;
    Elf64_Sym *symtab = NULL;
    char *strtab = NULL;
    u16 num_symbols = 0;

    for (u16 i = 0; i < elf_header->e_shnum; ++i) {
        if (section_header[i].sh_type == SHT_SYMTAB) {
            symtab_header = &section_header[i];
            break;
        }
    }
    if (!symtab_header) {
        printf("no symbol table found\n");
        return;
    }

    strtab = (char *)base_address + section_header[symtab_header->sh_link].sh_offset;
    symtab = (Elf64_Sym *)(base_address + symtab_header->sh_offset);
    num_symbols = symtab_header->sh_size / sizeof(Elf64_Sym);

    for (u16 i = 1; i < num_symbols; i++) {
        (void)print_line(strtab, &symtab[i], flags);
    }
}