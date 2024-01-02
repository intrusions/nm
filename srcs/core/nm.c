/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 01:39:38 by xel               #+#    #+#             */
/*   Updated: 2024/01/02 07:02:07 by xel              ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "nm.h"
#include "flag.h"
#include "debug.h"

void    handle_64(Elf64_Ehdr *elf_header, char *base_address) {
    
    Elf64_Shdr *section_header = (Elf64_Shdr *)(base_address + elf_header->e_shoff);
    Elf64_Shdr *symtab_header = NULL;
    char *strtab = NULL;

    for (int i = 0; i < elf_header->e_shnum; ++i) {
        if (section_header[i].sh_type == SHT_SYMTAB) {
            symtab_header = &section_header[i];
            break;
        }
    }
    if (!symtab_header) {
        printf("no symbol table found\n");
        return;
    }

    strtab = base_address + section_header[symtab_header->sh_link].sh_offset;
    Elf64_Sym *symtab = (Elf64_Sym *)(base_address + symtab_header->sh_offset);
    
    int num_symbols = symtab_header->sh_size / sizeof(Elf64_Sym);
    for (int i = 0; i < num_symbols; ++i) {
        printf("%s\n", strtab + symtab[i].st_name);
    }
}

void nm(char *file_name, const u64 flags) {
    __DEBUG_PRINT_FLAGS(flags, file_name);

    int         fd;
    struct stat file_stat;
    char        *file_data;

    if ((fd = open(file_name, O_RDONLY)) < 0) {
        perror("nm: open");
        return ; 
    }
    if (fstat(fd, &file_stat) < 0) {
        perror("nm: fstat");
        return ; 
    }
    if ((file_data = mmap(0, file_stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED) {
        perror("nm: mmap");
        close(fd);
        return ; 
    }
    
    Elf64_Ehdr *elf_header = (Elf64_Ehdr *)file_data;
    if (memcmp(elf_header->e_ident, ELFMAG, SELFMAG) != 0) {
        printf("not an ELF file\n");
        munmap(file_data, file_stat.st_size);
        close(fd);
        return;
    }

    if (elf_header->e_ident[EI_CLASS] == ELFCLASS32) {
        // handle_32();
    } else if (elf_header->e_ident[EI_CLASS] == ELFCLASS64) {
        handle_64(elf_header, file_data);
    }
    
    munmap(elf_header, sizeof(Elf64_Ehdr));
    close(fd);
}
