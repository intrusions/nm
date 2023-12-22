/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_flag.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 23:32:41 by xel               #+#    #+#             */
/*   Updated: 2023/12/22 17:56:11 by xel              ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "nm.h"
#include "flag.h"

#define N_FLAGS 5

static void print_man() {
    
    printf(
        "Usage: nm [options(s)] [file(s)]\n"
        " List symbols in [file(s)] (a.out by default).\n"
        " The options are:\n"
        " -a, --debug-syms          Display debugger-only symbols\n"
        " -g, --extern-only         Display only external symbols\n"
        " -p, --no-sort             Do not sort the symbols\n"
        " -u, --undefined-only      Display only undefined symbols\n"
        " -r, --reverse-sort        Reverse the sense of the sort\n"
    );
}

static u64 what_option_bit(const char *options) {
    
    if (!strcmp(options, "--debug-syms"))       { return FLAG_A; }
    if (!strcmp(options, "--extern-only"))      { return FLAG_G; }
    if (!strcmp(options, "--no-sort"))          { return FLAG_P; }
    if (!strcmp(options, "--undefined-only"))   { return FLAG_U; }
    if (!strcmp(options, "--reverse-sort"))     { return FLAG_R; }
    return 0;
}

static u64 what_flag_bit(const char flag) {
    
    if (flag == 'a')     { return FLAG_A; }
    if (flag == 'g')     { return FLAG_G; }
    if (flag == 'p')     { return FLAG_P; }
    if (flag == 'u')     { return FLAG_U; }
    if (flag == 'r')     { return FLAG_R; }
    return 0;
}

static bool is_valid_option(const char *option, u64 *flags) {
    
    const char *valid_options[N_FLAGS] = {
        "--debug-syms",
        "--extern-only",
        "--no-sort",
        "--undefined-only",
        "--reverse-sort"
    };

    for (u8 i = 0; i < N_FLAGS; i++) {
        if (!strcmp(option, valid_options[i])) {
            *flags |= what_option_bit(valid_options[i]);
            return true;
        }
    }
    return false;
}

static bool is_valid_option_flag(const char *option, char *invalid_flag, u64 *flags) {
    
    const char *valid_flags = "agpur";

    for (u8 i = 0; option[i]; i++) {
        bool valid = false;

        for (u8 j = 0; valid_flags[j]; j++) {
            if (valid_flags[j] == option[i]) {
                valid = true;
                *flags |= what_flag_bit(option[i]);
                break;
            }
        }

        if (!valid) {
            *invalid_flag = option[i];
            return false;
        }
    }
    return true; 
}

bool manage_flag(int argc, char **argv, u64 *flags) {

    int     n_param = argc - 1;
    char    **options = argv + 1;
    char    invalid_flag;

    if (argv[argc - 1][0] != '-') {
        n_param--;
    }

    for (u16 i = 0; i < n_param; i++) {
        if (options[i][0] == '-' && options[i][1] == '-') {
            if (!is_valid_option(options[i], flags)) {
                printf("nm: unrecognized option '%s'\n", options[i]);
                print_man();
                return false;
            }
        } else if (options[i][0] == '-') {
            if (!is_valid_option_flag(options[i] + 1, &invalid_flag, flags)) {
                printf("nm: unrecognized option '%c'\n", invalid_flag);
                print_man();
                return false;
            }
        }
    }
    return true;
}