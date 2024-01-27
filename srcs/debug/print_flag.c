/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 18:34:51 by xel               #+#    #+#             */
/*   Updated: 2024/01/27 01:16:40 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flag.h"
#include "nm.h"

void
__DEBUG_PRINT_FLAGS(const u64 flags, const char *file_name) {
    
    printf("Searching file: '%s'\n", file_name);

    if (flags) {
        printf("Active flag(s): ");

        if (flags & FLAG_A)     { printf("-a "); }
        if (flags & FLAG_G)     { printf("-g "); }
        if (flags & FLAG_P)     { printf("-p "); }
        if (flags & FLAG_U)     { printf("-u "); }
        if (flags & FLAG_R)     { printf("-r "); }
        printf("\n");
    } else {
        printf("No active flag\n");
    }
}