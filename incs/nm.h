/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 23:40:20 by xel               #+#    #+#             */
/*   Updated: 2023/12/22 01:40:30 by xel              ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef FLAG_H
# define FLAG_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

bool manage_flag(int argc, char **argv);
void nm(char *file_name);

#endif