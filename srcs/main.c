/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 23:22:32 by xel               #+#    #+#             */
/*   Updated: 2023/12/22 01:58:52 by xel              ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "nm.h"

int main(int argc, char **argv) {

    if (argc == 1) {                                        // Search a.out by default without flag
        nm("a.out");
    } else if (argv[argc - 1][0] == '-') {                  // Search a.out by default with flag
        if (manage_flag(argc, argv)) {
            nm("a.out");
        }
    } else if (argv[argc - 1][0] != '-' && argc == 2) {     // Search personal binary without flag
        nm(argv[argc - 1]);
    } else if (argv[argc - 1][0] != '-' && argc > 2) {      // Search personal binary with flag
        if (manage_flag(argc, argv)) {
            nm(argv[argc - 1]);
        }
    }

    return EXIT_SUCCESS;
}