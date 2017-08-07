/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 21:11:49 by cchaumar          #+#    #+#             */
/*   Updated: 2016/10/23 17:59:06 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define WIDTH		720
# define HEIGHT		720
# define NM_KERNEL	"kernels/main.cl"
# define NM_C_KER	"kernels/double.cl"
# define NAME_SIZE	64
# define MANDELBROT	0
# define JULIA		1
# define BURNING	2
# define MENGER		3
# define BULB		4
# define BOX		5
# define QUAT		6
# define BUDDHA		7
# define FRACTALS	8
# define NKEYS		32

# define UGLY		void CL_CALLBACK

# define ZOOM		0.9
# define ZOOM_M		0.97

# define RAD_STEP	1
# define SAT_STEP	0.01
# define HUE		1
# define SAT		2
# define EPS		0.00001
# define MIN_HUE	0.0
# define MAX_HUE	360.0
# define MIN_SAT	0.0
# define MAX_SAT	1.0
# define MIN_BR		0.0
# define MAX_BR		100.0

# define ROT		1
# define RAD_ROT	(ROT / 180.0) * M_PI

# define TBOX(x)	((t_box *)x)

# define J_VARX		0.001
# define J_VARY		0.001
# define MAX_HD		7
# define MAX(a, b) a > b ? a : b
# define MIN(a, b) a < b ? a : b

#endif
