/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_32.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 06:46:29 by xel               #+#    #+#             */
/*   Updated: 2024/01/29 09:12:51 by xel              ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "nm.h"
#include "flag.h"
#include "debug.h"

static char
get_symtype_32(const Elf32_Ehdr *elf_header, const Elf32_Sym *sym) {
    
    const i32   bind = ELF32_ST_BIND(sym->st_info);
    const i32   type = ELF32_ST_TYPE(sym->st_info);
    char        st;

    if (type == STT_FILE)
        return 'a';
    if (type == STT_SECTION)
        return 'n';
    
    if (bind == STB_WEAK) {
        if (type == STT_OBJECT) {
            if (sym->st_shndx == SHN_UNDEF)
                return 'v';
            else
                return 'V';
        }
        if (sym->st_shndx == SHN_UNDEF)
            return 'w';
        else
            return 'W';
    }

    if (sym->st_shndx == SHN_ABS)
        return 'A';
    if (sym->st_shndx == SHN_UNDEF)
        return 'U';
    

    const Elf32_Shdr *shdr =    (Elf32_Shdr *)
                                ((char *)elf_header
                                + elf_header->e_shoff 
                                + sym->st_shndx 
                                * elf_header->e_shentsize);

    const Elf32_Shdr *shstrtb = (Elf32_Shdr *)
                                ((char *)elf_header
                                + elf_header->e_shoff
                                + elf_header->e_shstrndx
                                * elf_header->e_shentsize);
    
    const char *section_name =  (char *)
                                ((char *)elf_header
                                + shstrtb->sh_offset
                                + shdr->sh_name);

    if (!strcmp(section_name, ".text")
            || !strcmp(section_name, ".fini")
            || !strcmp(section_name, ".init"))
        st = 'T';
    else if (!strcmp(section_name, "completed.0")
            || !strcmp(section_name, ".bss")
            || !strcmp(section_name, ".tbss"))
        st = 'B';
    else if (!strcmp(section_name, ".data")
            || !strcmp(section_name, ".fini_array")
            || !strcmp(section_name, ".init_array")
            || !strcmp(section_name, ".dynamic")
            || !strcmp(section_name, ".got.plt")
            || !strcmp(section_name, ".got"))
        st = 'D';
    else if (!strcmp(section_name, ".rodata")
            || !strcmp(section_name, ".eh_frame")
            || !strcmp(section_name, ".eh_frame_hdr")
            || !strcmp(section_name, ".note.ABI-tag"))
        st = 'R';
    else if (!strcmp(section_name, ".jcr"))
        st = 'd';
    else
        st = '?';

    if (bind == STB_LOCAL)
        st += 32;
    
    return (st);
}

static void
print_sym_list_32(t_sym_list **sym_list, const u16 n_sym) {
    
    for (u16 i = 0; i < n_sym - 1; i++) {
        
        if (sym_list[i]->is_masked)
            continue ;
        
        if (sym_list[i]->is_undef == true)
            (void)printf("        ");
        else
            (void)printf("%08lx", (u64)sym_list[i]->sym_value);
        
        (void)printf(" %c ", sym_list[i]->sym_type);
        (void)printf("%s\n", sym_list[i]->sym_name);
    }
}

static t_sym_list*
fill_sym_struct_32(const Elf32_Ehdr *elf_header, char *strtab, const Elf32_Sym *symtab) {

    t_sym_list  *sym = malloc(sizeof(t_sym_list));
    if (!sym)
        return NULL;
    (void)memset(sym, 0, sizeof(t_sym_list));

    if (symtab->st_shndx == SHN_UNDEF)
        sym->is_undef = true;
    else
        sym->sym_value = (u64)symtab->st_value;

    sym->sym_type = get_symtype_32(elf_header, symtab);
    sym->sym_name = strtab + symtab->st_name;

    return (sym);
}

void
handle_32(const Elf32_Ehdr *elf_header, const char *base_address, const u64 flags) {
    
    Elf32_Shdr  *section_header = (Elf32_Shdr *)(base_address + elf_header->e_shoff);
    Elf32_Shdr  *symtab_header = NULL;
    Elf32_Sym   *symtab = NULL;
    char        *strtab = NULL;
    t_sym_list  **sym_list = NULL;
    u16          n_sym = 0;

    for (u16 i = 0; i < elf_header->e_shnum; ++i) {
        if (section_header[i].sh_type == SHT_SYMTAB) {
            symtab_header = &section_header[i];
            break ;
        }
    }
    if (!symtab_header) {
        (void)printf("no symbol table found\n");
        return ;
    }

    strtab = (char *)base_address + section_header[symtab_header->sh_link].sh_offset;
    symtab = (Elf32_Sym *)(base_address + symtab_header->sh_offset);
    n_sym = symtab_header->sh_size / sizeof(Elf32_Sym);

    sym_list = malloc(n_sym * sizeof(t_sym_list *));
    if (!sym_list)
        return ;

    for (u16 i = 1; i < n_sym; i++) {
        sym_list[i - 1] = fill_sym_struct_32(elf_header, strtab, &symtab[i]);
    }

    (void)applies_flags_sym_list(sym_list, n_sym, flags);
    (void)print_sym_list_32(sym_list, n_sym);
    (void)free_sym_list(sym_list, n_sym);
}
