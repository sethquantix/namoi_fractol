#define BOUNDING	2
#define EPS			0.00001f
#define SCALE		0.8f
#define STEPS		2000
#define POWER		8.0f
#define PWR			8.0f
#define MENGER		0
#define BULB		1
#define BOX			2
#define QUAT		3
#define TET			4
#define MINRAD2		0.25f
#define FIXEDRAD	1.0f
#define RRAD		FIXEDRAD / MINRAD2
#define BOX_SCALE	3.5f
#define SRAD		BOX_SCALE / FIXEDRAD
#define BAILOUT		1024.0f
#define K			2.0f

#define LPOS		(float3)(2.0f, 2.0f, -10.0f)

typedef struct s_data
{
	int			width;
	int			height;
	float		min_x;
	float		max_x;
	float		min_y;
	float		max_y;
	float3		c1;
	float3		c2;
	int			max_iter;
	float2		jc;
	float3		cam;
	float3		corners[3];
	float		step;
	float3		mat[3];
	float4		c;
	float3		amb;
	float3		diff;
	float3		spec;
	float		shine;
	float		box_scale;
	float2		rads;
}				t_data;

inline int		rgb(float3 c)
{
	int		ti = (int)(c.x / 60) % 6;
	float	f = c.x / 60.0f - ti;
	float	l = c.z * (1.0f - c.y);
	float	m = c.z * (1.0f - f * c.y);
	float	n = c.z * (1.0f - (1.0f - f) * c.y);
	float3	rgb;

	if (ti == 0)
		rgb	 = (float3)(c.z, n, l);
	if (ti == 1)
		rgb = (float3)(m, c.z, l);
	if (ti == 2)
		rgb = (float3)(l, c.z, n);
	if (ti == 3)
		rgb = (float3)(l, m, c.z);
	if (ti == 4)
		rgb = (float3)(n, l, c.z);
	if (ti == 5)
		rgb = (float3)(c.z, l, m);
	rgb *= 255;
	return (((int)rgb.x << 16) + ((int)rgb.y << 8) + (int)rgb.z);
}

inline int		it_mj(float2 z, float2 c, int max_iter)
{
	int		i;
	float	zz = length(z) - 1;
	float	t;

	i = -1;
	while (++i < max_iter && zz != (t = length(z)) && (zz = t) < 4.0)
		z = c + (float2)(z.x * z.x - z.y * z.y, 2 * z.x * z.y);
	return (zz > 4.0 ? i : max_iter);
}

inline int		it_burning(float2 z, float2 c, int max_iter)
{
	int		i;
	float	zz = length(z) - 1;
	float	t;

	i = -1;
	while (++i < max_iter && zz != (t = length(z)) && (zz = t) < 4.0)
		z = c + (float2)(z.x * z.x - z.y * z.y, fabs(2 * z.x * z.y));
	return (zz > 4.0 ? i : max_iter);
}

__kernel void	mandelbrot(__constant t_data *data, __global int *buffer)
{
	int		l = get_global_size(0);
	int		h = get_global_size(1);
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	float2	z;
	float2	c;
	int		iter;

	z = (float2)(0.0f);
	c = (float2)(
		(float)x * (data->max_x - data->min_x) / (float)l + data->min_x,
		data->min_y + (float)y * (data->max_y - data->min_y) / (float)h);
	iter = it_mj(z, c, data->max_iter);
	buffer[x + y * l] = rgb((data->c2 - data->c1) *
		(float)iter / (float)data->max_iter + data->c1);
}

__kernel void	julia(__constant t_data *data, __global int *buffer)
{
	int		l = get_global_size(0);
	int		h = get_global_size(1);
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	float2	z;
	float2	c;
	int		iter;

	z = (float2)(
		(float)x * (data->max_x - data->min_x) / (float)l + data->min_x,
		data->min_y + (float)y * (data->max_y - data->min_y) / (float)h);
	c = data->jc;
	iter = it_mj(z, c, data->max_iter);
	buffer[x + y * l] = rgb((data->c2 - data->c1) *
		log((float)iter + 1) / log((float)data->max_iter) + data->c1);
}

__kernel void	burning(__constant t_data *data, __global int *buffer)
{
	int		l = get_global_size(0);
	int		h = get_global_size(1);
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	float2	z;
	float2	c;
	int		iter;

	z = (float2)(0.0f);
	c = (float2)(
		(float)x * (data->max_x - data->min_x) / (float)l + data->min_x,
		data->min_y + (float)y * (data->max_y - data->min_y) / (float)h);
	iter = it_burning(z, c, data->max_iter);
	buffer[x + y * l] = rgb((data->c2 - data->c1) *
		(float)iter / (float)data->max_iter + data->c1);
}

inline float de_menger(float3 z, float max_iter)
{
	int		i = -1;

	while (++i < 20)
	{
		z = fabs(z);
		z = z.x < z.y ? (float3)(z.yx, z.z) : z;
		z = z.y < z.z ? (float3)(z.x, z.zy) : z;
		z = z.x < z.y ? (float3)(z.yx, z.z) : z;
		z = 3.0f * z - 2.0f;
		if (z.z < -1.0f)
			z.z += 2.0f;
	}
	return ((length(z) - 1.5f) * pow(3.0f, -((float)i)));
}

inline float4	boxFold(float4 z, float fold)
{
	return ((float4)(clamp(z.xyz, -fold, fold) * 2.0f - z.xyz, z.w));
}

inline float4	ballFold(float4 z, float frad, float rrad, float r2)
{
	return(z * min(max(frad / r2, 1.0f), rrad));
}

inline float4	vPow(float4 z, float power, float r)
{
	float	theta = atan2(z.y, z.x);
	float	phi = r ? asin(z.z / r) : 0;

	theta *= POWER;
	phi *= POWER;
	return (pow(r, POWER - 1.0f) * (float4)(r * (float3)(cos(theta) * cos(phi),
		sin(theta) * cos(phi), sin(phi)), POWER * z.w + 1.0f));
}

inline float4	it_bulb(float4 p, float power, float3 z)
{
	return (vPow(p, power, length(p.xyz)) + (float4)(z, 0.0f));
}

inline float	de_bulb(float3 ray, int max_iter)
{
	float4	z = (float4)(ray, 1.0f);
	float	r = 1.0;
	int		i = -1;

	while (++i < max_iter)
	{
		r = length(z.xyz);
		if (r > 4.0f)
			break;
		z = it_bulb(z, 8.0f, ray);
	}
	return (0.5f * log(r) * r / z.w);
}

inline float	de_box(float3 z, t_data *cam)
{
	float4	p = (float4)(z, 1.0f);
	int		i = -1;

	while (++i < 15)
	{
		p = boxFold(p, 1.0f);
		p = ballFold(p, cam->rads.x, cam->rads.y, dot(p.xyz, p.xyz));
		p.xyz = p.xyz * cam->box_scale + z;
		p.w = p.w * fabs(cam->box_scale) + 1.0f;
	}
	return (length(p.xyz) / p.w);
}

inline float	de_quat(float3 z, int max_iter, float4 c)
{
	float4	zz = (float4)(z.xyz, 0);
	float4	dz = (float4)(1.0f, 0.0f, 0.0f, 0.0f);
	float	r;
	int		i = -1;

	while(++i < max_iter)
	{
		if (dot(zz, zz) > BAILOUT)
			break ;
		dz = 2.0f * (float4)(zz.x * dz.x - dot(zz.yzw, dz.yzw),
		zz.x * dz.yzw + dz.x * zz.yzw + cross(zz.yzw, dz.yzw));
		zz = (float4)(zz.x * zz.x - dot(zz.yzw, zz.yzw),
			2.0f * zz.x * zz.yzw) + c;
	}
	r = length(zz);
	return (0.5f * r * log(r) / length(dz));
}

inline float	de_main(float3 v, t_data *cam, int f)
{
	if (f == MENGER)
		return (de_menger(v, cam->max_iter));
	if (f == BULB)
		return (de_bulb(v, cam->max_iter));
	if (f == BOX)
		return (de_box(v, cam));
	if (f == QUAT)
		return (de_quat(v, cam->max_iter, cam->c));
	return (0.0f);
}

inline float3	rgbf(int col)
{
	int3	c = (int3)(col >> 16, (col >> 8) & 0xff, col & 0xff);
	return ((float3)((float)c.x, (float)c.y, (float)c.z) / 255.0f);
}

inline float3	phong(float3 p, float3 n, float3 k_amb, float3 k_diff,
	float3 k_spec, float shine, float3 v, float3 l, float shadow)
{
	float3	r = 2.0f * dot(l, n) * n - l;
	float3	amb = k_amb;
	float3	diff = k_diff * max(0.0f, dot(l, n));
	float3	spec = k_spec * max(0.0f, pow(dot(r, v), shine));
	return min((float3)(1.0f), (amb + (diff + spec)));
}

inline float3	gradient(float3 ray, t_data *cam, int fr)
{
	float3	grad;

	grad = (float3)(de_main(ray + (float3)(EPS, 0, 0), cam, fr) -
					de_main(ray - (float3)(EPS, 0, 0), cam, fr),
					de_main(ray + (float3)(0, EPS, 0), cam, fr) -
					de_main(ray - (float3)(0, EPS, 0), cam, fr),
					de_main(ray + (float3)(0, 0, EPS), cam, fr) -
					de_main(ray - (float3)(0, 0, EPS), cam, fr));
	return normalize(grad);
}

inline int		raymarch(float3 o, float3 d, t_data *cam, int fr, int3 debug)
{
	float4	ray = (float4)(o + 0.001f * d, 0.0f);
	int		i = -1;
	float	dist = BAILOUT;
	float3	col;
	float3	norm;
	float4	l;
	float4	shad;
	float	shadow;

	while (dist > EPS && ray.w < BAILOUT && ++i < STEPS)
	{
		dist = de_main(ray.xyz, cam, fr);
		ray += (float4)(d, 1.0f) * SCALE * dist;
	}
	if (dist < EPS)
	{
		l = (float4)(normalize(LPOS - ray.xyz), 1.0f);
		shad = (float4)(ray.xyz, 0.0f) + EPS * l;
		dist = BAILOUT;
		i = -1;
		shadow = 1.0;
		while (shad.w < BAILOUT && ++i < STEPS)
		{
			dist = de_main(shad.xyz, cam, fr);
			shad += l * SCALE * dist;
			shadow = min(shadow, K * dist / shad.w);
			if (dist < EPS)
			{
				shadow = 0.0f;
				break;
			}
		}
		norm = gradient(ray.xyz, cam, fr);
		col = phong(ray.xyz, norm, cam->amb, cam->diff, cam->spec, cam->shine,
					-d, l.xyz, shadow);
	}
	else
		col = rgbf(rgb(cam->c2));
	col = 255.0f * clamp(col, (float3)(0.0f), (float3)(1.0f));
	return ((((int)col.x) << 16) + (((int)col.y) << 8) + (int)col.z);
}

__kernel void	menger(__global t_data *cam, __global int *buffer,
	__global float *step)
{
	int		l = get_global_size(0);
	int		h = get_global_size(1);
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	float3	d;
	float2	p;
	float3	o;
	float	dist;
	t_data	data;

	data = *cam;
	o = data.cam;
	if (x == 0 && y == 0)
	{
		dist = de_main(o, &data, MENGER);
		while (dist < data.step && data.step > 0.001f)
			data.step /= 10.0f;
		while (dist > 10 * data.step && data.step < 1.0f)
			data.step *= 10.0f;
		data.step = min(1.0f, data.step);
		step[0] = data.step;
	}
	p = (float2)((float)x / (float)l, (float)y / (float)h);
	d = normalize(data.corners[0] + p.x * (data.corners[1] - data.corners[0]) +
		p.y * (data.corners[2] - data.corners[0]));
	buffer[x + y * l] = raymarch(o, d, &data, MENGER, (int3)(x, y, 0));
}

__kernel void	box(__global t_data *cam, __global int *buffer,
	__global float *step)
{
	int		l = get_global_size(0);
	int		h = get_global_size(1);
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	float3	d;
	float3	v1;
	float3	v2;
	float3	o;
	float	dist;
	int		c;
	t_data	data;

	data = *cam;
	o = data.cam;
	v1 = (data.corners[1] - data.corners[0]) / (float)l;
	v2 = (data.corners[2] - data.corners[0]) / (float)h;
	if (x == 0 && y == 0)
	{
		dist = de_main(o, &data, BOX);
		while (dist < data.step && data.step > EPS)
			data.step /= 10.0f;
		while (dist > 10 * data.step && data.step < 1.0f)
			data.step *= 10.0f;
		data.step = min(1.0f, data.step);
		step[0] = data.step;
	}
	d = data.corners[0] + x * v1 + y * v2;
	c = raymarch(o, normalize(d), &data, BOX, (int3)(x, y, 0));
	buffer[x + y * l] = c;
}

__kernel void	bulb(__global t_data *cam, __global int *buffer,
	__global float *step)
{
	int		l = get_global_size(0);
	int		h = get_global_size(1);
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	float3	d;
	float2	p;
	float3	o;
	float	dist;
	t_data	data;

	data = *cam;
	o = data.cam;
	if (x == 0 && y == 0)
	{
		dist = de_main(o, &data, BULB);
		while (dist < data.step && data.step > EPS)
			data.step /= 10.0f;
		while (dist > 10 * data.step && data.step < 1.0f)
			data.step *= 10.0f;
		data.step = min(1.0f, data.step);
		step[0] = data.step;
	}
	p = (float2)((float)x / (float)l, (float)y / (float)h);
	d = normalize(data.corners[0] + p.x * (data.corners[1] - data.corners[0]) +
		p.y * (data.corners[2] - data.corners[0]));
	buffer[x + y * l] = raymarch(o, d, &data, BULB, (int3)(x, y, 0));
}

__kernel void	quat(__global t_data *cam, __global int *buffer,
	__global float *step)
{
	int		l = get_global_size(0);
	int		h = get_global_size(1);
	int		x = get_global_id(0);
	int		y = get_global_id(1);
	float3	d;
	float2	p;
	float3	o;
	float	dist;
	t_data	data;

	data = *cam;
	o = data.cam;
	if (x == 0 && y == 0)
	{
		dist = de_main(o, &data, QUAT);
		while (dist < data.step && data.step > EPS / 10.0f)
			data.step /= 10.0f;
		while (dist > 10 * data.step && data.step < 1.0f)
			data.step *= 10.0f;
		data.step = min(1.0f, data.step);
		step[0] = data.step;
	}
	p = (float2)((float)x / (float)l, (float)y / (float)h);
	d = normalize(data.corners[0] + p.x * (data.corners[1] - data.corners[0]) +
		p.y * (data.corners[2] - data.corners[0]));
	buffer[x + y * l] = raymarch(o, d, &data, QUAT, (int3)(x, y, 0));
}
