/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/04 14:23:08 by cchaumar          #+#    #+#             */
/*   Updated: 2016/10/23 08:59:05 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void			get_source(t_env *e)
{
	char	*source;
	char	*buff;
	int		fd;

	source = NULL;
	if ((fd = open(NM_KERNEL, O_RDONLY)) == -1)
		die("couldnt load kernel.", e, EXIT_FAILURE);
	while (get_next_line(fd, &buff) > 0)
		source = ft_strjoinfree(source,
				ft_strjoinfree(buff, "\n", 1), 2 + (source ? 1 : 0));
	e->source = source;
	close(fd);
}

t_callback			notify(const char *errinfo, const void *private_info,
		size_t cb, void *user_data)
{
	static int		errcount = 0;

	(void)private_info;
	(void)cb;
	(void)user_data;
	ft_printf("Error %d (notified) : %s\n", ++errcount, errinfo);
}

static void			opencl_memory(t_env *e, cl_device_id device)
{
	int		err;

	if ((e->queue = clCreateCommandQueue(e->context, device,
		CL_QUEUE_PROFILING_ENABLE, NULL)) == NULL)
		die("Couldnt create command queue.", e, EXIT_FAILURE);
	if ((e->program = clCreateProgramWithSource(e->context, 1,
		(const char **)(&e->source), NULL, NULL)) == NULL)
		die("couldnt create program.", e, EXIT_FAILURE);
	if (clBuildProgram(e->program, 0, NULL, "-cl-fast-relaxed-math",
		NULL, NULL))
		die("Couldnt build program.", e, EXIT_FAILURE);
	e->cl_buffer = clCreateBuffer(e->context, CL_MEM_WRITE_ONLY,
			sizeof(int) * WIDTH * HEIGHT, NULL, &err);
	e->cl_data = clCreateBuffer(e->context, CL_MEM_READ_WRITE,
			sizeof(e->data), NULL, &err);
	e->step = clCreateBuffer(e->context, CL_MEM_READ_WRITE,
			sizeof(float), NULL, &err);
	if (err)
		die("Couldnt create buffer on VRAM. Cause reasons.", e, EXIT_FAILURE);
}

static void			create_kernels(t_env *e, int err, int i)
{
	cl_kernel		ker;
	static char		names[FRACTALS][NAME_SIZE] = {"mandelbrot", "julia",
		"burning", "menger", "bulb", "box", "quat", "tet"};

	while (++i < FRACTALS)
		if (i < BUDDHA)
		{
			ker = clCreateKernel(e->program, names[i], &err);
			ft_printf("%s : %s\n", names[i], err ? "Failed !" :
				"Built !");
			e->kernels[i] = ker;
			if (!ker)
				ft_printf("something went wrong\n");
			err = clSetKernelArg(e->kernels[i], 1, sizeof(cl_mem),
				&e->cl_buffer);
			err |= clSetKernelArg(e->kernels[i], 0, sizeof(cl_mem),
				&e->cl_data);
			if (i >= MENGER)
				err |= clSetKernelArg(e->kernels[i], 2, sizeof(cl_mem),
					&e->step);
			if (err)
				ft_printf("error setting up args. No seeing that coming\n");
		}
}

void				opencl_init(t_env *e)
{
	cl_platform_id	platform;
	cl_device_id	device;
	int				err;

	get_source(e);
	clGetPlatformIDs(1, &platform, NULL);
	if (clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL))
		die("GPU not detected by opencl. Now, that's new.", e, EXIT_FAILURE);
	if (!(e->context = clCreateContext(0, 1, &device, &notify, NULL, &err)))
		die("Couldnt create opencl context.", e, EXIT_FAILURE);
	e->k_size->global[0] = WIDTH;
	e->k_size->global[1] = HEIGHT;
	e->k_size->local[0] = 16;
	e->k_size->local[1] = 16;
	opencl_memory(e, device);
	create_kernels(e, 0, -1);
}
