/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 21:11:49 by cchaumar          #+#    #+#             */
/*   Updated: 2016/10/23 07:37:14 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include <OpenCL/opencl.h>
# include <stdlib.h>
# include <X11/X.h>
# include <time.h>
# include <math.h>
# include <unistd.h>
# include "defines.h"
# include "../libft/libft.h"
# include "mlx.h"

typedef UGLY	t_callback;
typedef struct	s_size
{
	size_t		global[2];
	size_t		local[2];
}				t_size;

typedef struct	s_box
{
	float	*p;
	float	min;
	float	max;
	float	pos;
	int		type;
	int		x;
	int		y;
	int		sx;
	int		sy;
	int		cond;
}				t_box;

typedef struct	s_data
{
	int			width;
	int			height;
	float		min_x;
	float		max_x;
	float		min_y;
	float		max_y;
	cl_float3	c1;
	cl_float3	c2;
	int			max_iter;
	cl_float2	jc;
	cl_float3	cam;
	cl_float3	corners[3];
	float		step;
	cl_float3	mat[3];
	cl_float4	c;
	cl_float3	amb;
	cl_float3	diff;
	cl_float3	spec;
	float		shine;
	float		box_scale;
	cl_float2	rads;
}				t_data;

typedef struct	s_fract
{
	char		name[11];
	int			fract;
}				t_fract;

typedef struct	s_mouse
{
	int		button[6];
	int		x;
	int		y;
	t_box	*box;
}				t_mouse;

typedef struct	s_val
{
	int		keycode;
	int		*val;
}				t_val;

typedef struct	s_env
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*buf;
	int					bpp;
	int					lsz;
	int					end;
	int					info;
	int					hd;
	char				*source;
	int					mode;
	int					fps;
	int					colors;
	cl_context			context;
	cl_command_queue	queue;
	cl_program			program;
	cl_kernel			kernels[FRACTALS];
	cl_mem				cl_buffer;
	cl_mem				cl_data;
	cl_mem				step;
	t_data				data;
	t_size				*k_size;
	int					fractal;
	int					julia_mode;
	t_mouse				mouse;
	struct s_key		*keys;
	cl_int2				m_old;
	cl_float2			j_var;
	cl_float2			jc;
	int					dir;
	char				drag;
	char				state;
	int					rand;
	cl_int2				centers[2];
	cl_int2				p[2][3];
	cl_int2				rads;
	cl_int2				borders;
	cl_float3			**mats;
	t_list				*boxes;
	int					hook_mode;
}				t_env;

typedef struct	s_key
{
	int		keycode;
	int		pressed;
	int		(*func)(int, t_env *);
}				t_key;

void			die(char *s, t_env *e, int exit_code);
int				k_exit(int keycode, t_env *e);
void			opencl_init(t_env *e);
void			init_keys(t_env *e);
int				key_hook(int keycode, t_env *e);
int				key_release_hook(int keycode, t_env *e);
int				mouse_hook(int button, int x, int y, t_env *e);
int				mouse_free_hook(int x, int y, t_env *e);
int				mouse_release_hook(int button, int x, int y, t_env *e);
int				loop_hook(t_env *e);
int				hook(t_env *e);
void			draw(t_env *e);
void			new_coord(t_env *e, int x, int y, float zoom);
void			c_new_coord(t_env *e, int x, int y, double zoom);
void			move_coord(t_env *e, int x, int y);
void			c_opencl_init(t_env *e);
t_callback		notify(const char *errinfo, const void *private_info,
	size_t cb, void *user_data);
cl_double2		compute(cl_double2 z, cl_double2 c);
double			size(cl_double2 z);
int				most(int *buf, int size);
void			plot_circle(t_env *e, cl_int2 center, cl_int2 pos,
	cl_float3 col);
void			plot_triangle(t_env *e, cl_int2 *p, cl_int2 pos,
	cl_float3 col);
cl_int2			int2(int x, int y);
cl_int3			int3(int x, int y, int z);
cl_float2		float2(float x, float y);
cl_double4		double4(double x, double y, double z, double w);
cl_double2		double2(double x, double y);
cl_float3		float3(float x, float y, float z);
cl_int2			rot(cl_int2 p, cl_int2 center, float rad);
float			dot3(cl_float3 v1, cl_float3 v2);
float			dist(cl_int2 o, cl_int2 p);
int				hue(t_env *e, cl_int2 p, int col);
int				set_sv(t_env *e, cl_float2 r, int col);
cl_float2		sv(cl_int2 pos, cl_int2 *p);
int				hsv(float h, float s, float v);
float			area(cl_int2 p1, cl_int2 p2, cl_int2 p3);
void			buddha(t_env *e, t_data *data);
void			m_set_ident3(cl_float3 *m);
void			m_mult3(cl_float3 *m1, cl_float3 *m2);
void			m_set_rot(cl_float3 **mats);
void			alloc_mats(t_env *e);
void			rotate_corners(t_env *e);
int				rotate_cam(int keycode, t_env *e);
int				move_cam(int keycode, t_env *e);
cl_float4		quat(cl_float4 c, cl_float2 mv, int dir);
t_box			new_box(cl_int2 pos, cl_int2 size, float v);
void			create_boxes(t_env *e);
t_box			*intersect(int x, int y, t_list *boxes);
t_list			*add_box(float *p, float min, float max, int type);
t_box			*get_box(t_list *boxes, float *addr);
void			set_values(t_list *boxes);
void			get_values(t_list *boxes);
void			draw_boxes(t_env *e);
void			menu(t_env *e);
void			rand_colors(t_env *e);
void			julia_move(int x, int y, t_env *e);
void			zoom(int x, int y, t_env *e);
void			move(int x, int y, t_env *e);
int				iter(int keycode, t_env *e);
int				space(int keycode, t_env *e);

#endif
