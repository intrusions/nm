/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 23:22:32 by xel               #+#    #+#             */
/*   Updated: 2023/12/22 22:48:54 by xel              ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "nm.h"

int main(int ac, char **av) {

    u64 flags = 0;

    if (ac == 1) {                                      // Search a.out by default without flag
        nm("a.out", flags);
    } else if (av[ac - 1][0] == '-') {                  // Search a.out by default with flag
        if (manage_flag(ac, av, &flags)) {
            nm("a.out", flags);
        } else {}
    } else if (av[ac - 1][0] != '-' && ac == 2) {     // Search personal binary without flag
        nm(av[ac - 1], flags);
    } else if (av[ac - 1][0] != '-' && ac > 2) {      // Search personal binary with flag
        if (manage_flag(ac, av, &flags)) {
            nm(av[ac - 1], flags);
        } else {}
    }

    return EXIT_SUCCESS;
}