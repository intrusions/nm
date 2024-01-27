/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 01:39:38 by xel               #+#    #+#             */
/*   Updated: 2024/01/27 01:16:31 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"
#include "flag.h"
#include "debug.h"

void
nm(char *file_name, const u64 flags) {
    // __DEBUG_PRINT_FLAGS(flags, file_name);
    (void)flags;

    int         fd;
    struct stat file_stat;
    char        *binary_dump;

    if ((fd = open(file_name, O_RDONLY)) < 0) {
        perror("nm: open");
        return ; 
    }
    if (fstat(fd, &file_stat) < 0) {
        perror("nm: fstat");
        return ; 
    }
    if ((binary_dump = mmap(0, file_stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED) {
        perror("nm: mmap");
        close(fd);
        return ; 
    }
    
    Elf64_Ehdr *elf_header = (Elf64_Ehdr *)binary_dump;
    if (memcmp(elf_header->e_ident, ELFMAG, SELFMAG) != 0) {
        printf("nm: not an elf file\n");
        munmap(binary_dump, file_stat.st_size);
        close(fd);
        return;
    }

    if (elf_header->e_ident[EI_CLASS] == ELFCLASS32) {
        // handle_32();
    } else if (elf_header->e_ident[EI_CLASS] == ELFCLASS64) {
        handle_64(elf_header, binary_dump, flags);
    }
    
    munmap(binary_dump, file_stat.st_size);
    close(fd);
}
