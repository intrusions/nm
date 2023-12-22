/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 01:39:38 by xel               #+#    #+#             */
/*   Updated: 2023/12/22 18:28:58 by xel              ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "nm.h"
#include "flag.h"

void    __DEBUG_PRINT_FLAGS(const u64 flags, const char *file_name) {
    
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

void nm(char *file_name, const u64 flags) {
    __DEBUG_PRINT_FLAGS(flags, file_name);

}
