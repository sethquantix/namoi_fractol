/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/24 05:40:24 by cchaumar          #+#    #+#             */
/*   Updated: 2016/09/24 05:40:45 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H
# define BUFFSIZE			2048
# define MAX(a, b)			(a > b ? a : b)
# define MIN(a, b)			(a < b ? a : b)
# define CHECK(v, c, m)		v &= c ? m : 0xFF

# define ALT				0x1
# define ZRO				0x2
# define NEG				0x4
# define SPC				0x8
# define PLS				0x10
# define THD				0x20
# define NOM				0x0
# define HHM				0x1
# define H_M				0x2
# define CLM				0x3
# define LLM				0x4
# define L_M				0x5
# define J_M				0x6
# define T_M				0x7
# define Z_M				0x8
# define LIS				0x0
# define LDS				0x1
# define UDS				0x2
# define LUS				0x3
# define UUS				0x4
# define LOS				0x5
# define UOS				0x6
# define LXS				0x7
# define UXS				0x8
# define LCS				0x9
# define UCS				0xA
# define LSS				0xB
# define USS				0xC
# define LFS				0xD
# define UFS				0xE
# define LPS				0xF

# define CS					(1 << 0)
# define FS					(1 << 1)
# define XS					(1 << 2)
# define OS					(1 << 3)
# define US					(1 << 4)
# define SS					(1 << 5)
# define DS					(1 << 6)
# define PS					(1 << 7)
# define DECIMAL			(XS | OS | US | DS)
# define CHAR				CS
# define FLOAT				FS
# define STRING				SS
# define TEXT				(STRING | CHAR)
# define POINTER			PS
# define BASE8				OS
# define BASE16				XS
# define UNSIGNED			(US + BASE8 + BASE16)
# define BASE10				(DS + US)

# define BYTE2				0x7F
# define BYTE3				0x7FF
# define BYTE4				0xFFFF
# define MASK_2				0xC080
# define MASK_3				0xE08080
# define MASK_4				0xF0808080

# define MODS				{"", "hh", "h", "L", "ll", "l", "j", "t", "z", NULL}
# define FLAG				"#0- +'"
# define CONV				"idDuUoOxXcCsSfFp"

#endif
