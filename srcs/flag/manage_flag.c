/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_flag.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 23:32:41 by xel               #+#    #+#             */
/*   Updated: 2023/12/22 01:43:31 by xel              ###   ########.fr       */
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

static bool is_valid_option(const char *option) {
    
    const char *valid_options[N_FLAGS] = {
        "--debug-syms",
        "--extern-only",
        "--no-sort",
        "--undefined-only",
        "--reverse-sort"
    };

    for (u8 i = 0; i < N_FLAGS; i++) {
        if (!strcmp(option, valid_options[i])) {
            return true;
        }
    }
    return false;
}

static bool is_valid_option_flag(const char *option, char *invalid_flag) {
    
    const char *valid_flags = "agpur";

    for (u8 i = 0; option[i]; i++) {
        bool valid = false;

        for (u8 j = 0; valid_flags[j]; j++) {
            if (valid_flags[j] == option[i]) {
                valid = true;
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


bool manage_flag(int argc, char **argv) {

    int     n_param = argc - 1;
    char    **options = argv + 1;
    char    invalid_flag;

    if (argv[argc - 1][0] != '-') {
        n_param--;
    }

    for (u16 i = 0; i < n_param; i++) {
        if (options[i][0] == '-' && options[i][1] == '-') {
            if (!is_valid_option(options[i])) {
                printf("nm: unrecognized option '%s'\n", options[i]);
                print_man();
                return false;
            }
        } else if (options[i][0] == '-') {
            if (!is_valid_option_flag(options[i] + 1, &invalid_flag)) {
                printf("nm: unrecognized option '%c'\n", invalid_flag);
                print_man();
                return false;
            }
        }
    }
    return true;
}