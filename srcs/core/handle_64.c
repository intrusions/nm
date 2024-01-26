/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 06:46:29 by xel               #+#    #+#             */
/*   Updated: 2024/01/26 11:39:42 by xel              ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "nm.h"
#include "flag.h"
#include "debug.h"

static char    get_symtype_64(Elf64_Ehdr *elf_header, Elf64_Sym *sym) {
    
    const i32   bind = ELF64_ST_BIND(sym->st_info);
    const i32   type = ELF64_ST_TYPE(sym->st_info);
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
    

    const Elf64_Shdr *shdr =    (Elf64_Shdr *)
                                ((char *)elf_header
                                + elf_header->e_shoff 
                                + sym->st_shndx 
                                * elf_header->e_shentsize);

    const Elf64_Shdr *shstrtb = (Elf64_Shdr *)
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

static void    print_sym_list_64(t_sym_list **sym_list, u16 n_sym) {
    
    for (u16 i = 0; i < n_sym - 1; i++) {
        
        if (sym_list[i]->is_masked)
            continue ;
        
        if (sym_list[i]->is_undef == true)
            (void)printf("                ");
        else
            (void)printf("%016lx", (u64)sym_list[i]->sym_value);
        
        (void)printf(" %c ", sym_list[i]->sym_type);
        (void)printf("%s\n", sym_list[i]->sym_name);
    }
}

static t_sym_list    *fill_sym_struct_64(Elf64_Ehdr *elf_header, char *strtab, Elf64_Sym *symtab) {

    t_sym_list  *sym = malloc(sizeof(t_sym_list));
    if (!sym)
        return NULL;
    (void)memset(sym, 0, sizeof(t_sym_list));

    if (symtab->st_shndx == SHN_UNDEF)
        sym->is_undef = true;
    else
        sym->sym_value = (u64)symtab->st_value;

    sym->sym_type = get_symtype_64(elf_header, symtab);
    sym->sym_name = strtab + symtab->st_name;

    return (sym);
}

static void mask_internal_sym(t_sym_list **sym_list, u16 num_symbols) {
    
    for (u16 i = 0; i < num_symbols - 1; i++) {
        
        if (sym_list[i]->sym_type < 65
            && sym_list[i]->sym_type > 90)
        sym_list[i]->is_masked = true;
    }
}

static void apply_flags_sym_list_64(t_sym_list **sym_list, u16 num_symbols, u64 flags) {
    (void)sym_list;
    (void)flags;
    
    if (flags & FLAG_A) {
        
    }
    if (flags & FLAG_G) {
        (void)mask_internal_sym(sym_list, num_symbols);
    }
}

void handle_64(Elf64_Ehdr *elf_header, char *base_address, u64 flags) {
    
    Elf64_Shdr  *section_header = (Elf64_Shdr *)(base_address + elf_header->e_shoff);
    Elf64_Shdr  *symtab_header = NULL;
    Elf64_Sym   *symtab = NULL;
    char        *strtab = NULL;
    t_sym_list  **sym_list = NULL;
    u16          num_symbols = 0;
    

    for (u16 i = 0; i < elf_header->e_shnum; ++i) {
        if (section_header[i].sh_type == SHT_SYMTAB) {
            symtab_header = &section_header[i];
            break;
        }
    }
    if (!symtab_header) {
        (void)printf("no symbol table found\n");
        return;
    }

    strtab = (char *)base_address + section_header[symtab_header->sh_link].sh_offset;
    symtab = (Elf64_Sym *)(base_address + symtab_header->sh_offset);
    num_symbols = symtab_header->sh_size / sizeof(Elf64_Sym);

    sym_list = malloc(num_symbols * sizeof(t_sym_list *));
    if (!sym_list)
        return ;

    for (u16 i = 1; i < num_symbols; i++) {
        sym_list[i - 1] = fill_sym_struct_64(elf_header, strtab, &symtab[i]);
    }
    
    (void)apply_flags_sym_list_64(sym_list, num_symbols, flags);
    (void)print_sym_list_64(sym_list, num_symbols);
    (void)free_sym_list(sym_list, num_symbols);
}
