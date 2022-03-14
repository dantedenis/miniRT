/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 18:11:11 by lcoreen           #+#    #+#             */
/*   Updated: 2022/03/14 22:58:16 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "errors.h"

float	intersect_plane(t_pl *tmp, t_vec *ray, t_vec *o, float *t2)
{
	float	c;
	float	ret;
	t_vec	oc;

	if (t2)
		*t2 = FLT_MAX;
	c = vec_scalar_mul(ray, &tmp->n);
	oc = vec_sub(o, &tmp->c);
	if (c == 0)
		return (FLT_MAX);
	ret = -vec_scalar_mul(&oc, &tmp->n) / c;
	if (ret < 0)
		return (FLT_MAX);
	return (ret);
}

t_vec	get_cy_norm(t_cy *cy, t_vec *ray, t_vec *o, float t)
{
	t_vec	oc;
	t_vec	tmp;
	if (!cy->part)
	{
		oc = vec_sub(o, &cy->pos);
		tmp = vec_mul_nbr(&cy->norm, vec_scalar_mul(ray, &cy->norm));
		tmp = vec_sub(ray, &tmp);
		tmp = vec_mul_nbr(&tmp, t);
		tmp = vec_sum(&tmp, &oc);
		oc = vec_mul_nbr(&cy->norm, vec_scalar_mul(&oc, &cy->norm));
		tmp = vec_sub(&tmp, &oc);
		return (tmp);
	}
	else
		return (vec_mul_nbr(&cy->norm, cy->part));
}

float	intersect_cylinder(t_cy *tmp, t_vec *ray, t_vec *o, float *t2)
{
	t_vec	oc;
	float	a;
	float	b;
	float	c;
	float	descr;
	float	t1;
	float	t;
	float	m;
	t_vec	pc;
	t_pl	plane;

	tmp->part = 0;
	oc = vec_sub(o, &tmp->pos);
	a = vec_scalar_mul(ray, ray) - pow(vec_scalar_mul(ray, &tmp->norm), 2);
	b = 2 * (vec_scalar_mul(ray, &oc) - vec_scalar_mul(ray, &tmp->norm)*vec_scalar_mul(&oc, &tmp->norm));
	c = vec_scalar_mul(&oc, &oc) - pow(vec_scalar_mul(&oc, &tmp->norm), 2) - (pow(tmp->diameter / 2, 2));
	descr = pow(b, 2) - 4 * a * c;
	if (descr < 0)
	{
		*t2 = FLT_MAX;
		return (FLT_MAX);
	}
	t1 = (-b + sqrt(descr)) / (2 * a);
	*t2 = (-b - sqrt(descr)) / (2 * a);
	t = t1;
	if (*t2 > 0 && *t2 < t1)
		t = *t2;
	m = vec_scalar_mul(&oc, &tmp->norm) + t * vec_scalar_mul(ray, &tmp->norm);
	if (m <= 0 || m >= tmp->height)
	{
		t1 = FLT_MAX;
		plane.c = tmp->pos;
		plane.n = vec_mul_nbr(&tmp->norm, -1);
		t = intersect_plane(&plane, ray, o, t2);
		if (t < FLT_MAX)
		{
			pc = vec_mul_nbr(ray, t);
			pc = vec_sum(&pc, o);
			pc = vec_sub(&pc, &plane.c);
			if (vec_len(&pc) <= tmp->diameter / 2)
			{
				tmp->part = -1;
				t1 = t;
			}
		}
		plane.c = vec_mul_nbr(&tmp->norm, tmp->height);
		plane.c = vec_sum(&tmp->pos, &plane.c);
		plane.n = tmp->norm;
		t = intersect_plane(&plane, ray, o, t2);
		if (t < FLT_MAX)
		{
			pc = vec_mul_nbr(ray, t);
			pc = vec_sum(&pc, o);
			pc = vec_sub(&pc, &plane.c);
			if (vec_len(&pc) <= tmp->diameter / 2)
			{
				tmp->part = 1;
				t1 = t;
			}
		}
	}
	return (t1);
}

float	intersect_sphere(t_sph *tmp, t_vec *ray, t_vec *o, float *t2)
{
	float		k1;
	float		k2;
	float		k3;
	float		descr;
	t_vec		oc;

	oc = vec_sub(o, &tmp->cntr);
	k1 = vec_scalar_mul(ray, ray);
	k2 = 2 * vec_scalar_mul(ray, &oc);
	k3 = vec_scalar_mul(&oc, &oc) - pow(tmp->radius, 2);
	descr = pow(k2, 2) - 4 * k1 * k3;
	if (descr < 0)
	{
		*t2 = FLT_MAX;
		return (FLT_MAX);
	}
	*t2 = (-k2 - sqrt(descr)) / (2 * k1);
	return ((-k2 + sqrt(descr)) / (2 * k1));
}

t_obj	*trasing(t_data *data, t_vec *o, float t_min, float t_max)
{
	float	closest;
	t_obj	*closest_obj;
	float	t2;
	float	t1;
	t_obj	*obj;
	
	closest = FLT_MAX;
	closest_obj = NULL;
	obj = data->obj;
	while (obj)
	{
		if (!ft_strncmp(obj->key, "sp", 3))
			t1 = intersect_sphere((t_sph *) obj->par, &data->ray, o, &t2);
		else if (!ft_strncmp(obj->key, "pl", 3))
			t1 = intersect_plane((t_pl *) obj->par, &data->ray, o, &t2);
		else if (!ft_strncmp(obj->key, "cy", 3))
			t1 = intersect_cylinder((t_cy *) obj->par, &data->ray, o, &t2);
		if ((t1 > t_min && t1 < t_max) && t1 < closest)
		{
			closest_obj = obj;
			closest_obj->t = t1;
			closest = t1;
		}
		if ((t2 > t_min && t2 < t_max) && t2 < closest)
		{
			closest_obj = obj;
			closest_obj->t = t2;
			closest = t2;
		}
		obj = obj->next;
	}
	return (closest_obj);
}

t_vec	compute_light(t_data *data, t_light *light, t_vec *P, t_vec *N)
{
	t_vec	i;
	float	L_dot_N;
	t_obj	*close_obj;
	
	i = new_vector(0, 0, 0);
	while (light)
	{
		if (!ft_strncmp(light->type, "A", 2))
			add_intensity(&i, &light->color, light->ratio);
		else
		{
			data->ray = vec_sub(&light->pos, P);
			close_obj = trasing(data, P, 0.001, 1);
			if (close_obj)
			{
				light = light->next;
				continue ;
			}
			L_dot_N = vec_scalar_mul(&data->ray, N);
			if (L_dot_N > 0)
				add_intensity(&i, &light->color, light->ratio * L_dot_N / vec_len(&data->ray));
		}
		light = light->next;
	}
	return (i);
}

int	get_color(t_data *data, t_vec *o)
{
	t_vec	P;
	t_vec	N;
	t_vec	closest_ray;
	t_obj	*closest_fig;
	int		color;

	closest_fig = trasing(data, o, 1, FLT_MAX);
	if (closest_fig == NULL)
		return (0);
	closest_ray = vec_mul_nbr(&data->ray, closest_fig->t);
	P = vec_sum(&closest_ray, o);
	if (!ft_strncmp(closest_fig->key, "sp", 3))
		N = vec_sub(&P, &((t_sph *) closest_fig->par)->cntr);
	else if (!ft_strncmp(closest_fig->key, "cy", 3))
		N = get_cy_norm((t_cy *) closest_fig->par, &data->ray, o, closest_fig->t);
	else
		N = vec_copy(&((t_pl *) closest_fig->par)->n);
	vec_norm(&N);
	closest_ray = compute_light(data, data->light, &P, &N);
	color = mul_pcolor(&closest_fig->color, &closest_ray);
	return (color);
}

int	ray_trase(t_data *data, t_vec *o, int x, int y)
{
	float	sc_x;
	float	sc_y;
	int		color;
	t_vec	u;
	t_vec	v;
	
	sc_x = tan(data->cam.fov * M_PI / 360) * x / data->w;
	sc_y = data->whratio * y / data->h;
	u = vec_mul_nbr(&data->cam.right, sc_x);
	v = vec_mul_nbr(&data->cam.up, sc_y);
	data->ray = vec_sum(&u, &v);
	data->ray = vec_sum(&data->ray, &data->cam.orient);
	color = get_color(data, o);
	return (color);
}

void	draw(t_data *data)
{
	int	x;
	int	y;
	int	new_x;
	int	new_y;
	int	color;
	t_vec	*o;

	y = 0;
	data->img.img = mlx_new_image(data->mlx, data->w, data->h);
	if (!data->img.img)
		error(ERROR_IMG);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
			&data->img.line_length, &data->img.endian);
	o = &data->cam.pos;
	while (y < data->h)
	{
		x = 0;
		new_y = data->h / 2 - y;
		while (x < data->w)
		{
			new_x = x - data->w / 2;
			color = ray_trase(data, o, new_x, new_y);
			my_mlx_pixel_put(&data->img, x, y, color);
			++x;
		}
		++y;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	mlx_destroy_image(data->mlx, data->img.img);
}

int	main(int argc, char **argv)
{
	t_data	data;

	(void) argc;
	ft_bzero(&data, sizeof(t_data));
	data.mlx = mlx_init();
	if (!data.mlx)
		error(ERROR_MLX);
	data.w = 800;
	data.h = 600;
	data.whratio = (float) data.h / data.w;
	reader_file(argv[1], &data);
	// CHANGES: Поменял структуры сферы и плоскости, все общие поля вынес в obj (color, параметр t)
	// 			В структурах остаются только их геометрические параметры
	//			Лист объектов хранит только объекты фигур и их параметры
	//			Лист света (data.light) хранит свет в виде одного типа t_light (для определения типа света используется data.light->type)
	//			Камера в структуре расположена тоже отдельным полем (data.cam)
	//			Изменения в структуре data немного коснулись функций list_obj.c (не сильно :))
	// TODO (from subject):
	// 	• Your program must be able to resize the object’s unique properties: diameter for a
	// sphere and the width and height for a cylinder.
	// • Your program must be able to apply translation and rotation transformation to
	// objects, lights and cameras (except for spheres and lights that cannot be rotated).
	// TODO: Реализовать вращение и перемещение по остальным осям (приорирет пока низкий)
	// TODO: Реализовать зеркальное отражение (бонус)
	data.win = mlx_new_window(data.mlx, data.w, data.h, "miniRT");
	if (!data.win)
		error(ERROR_WIN);
	draw(&data);
	mlx_hook(data.win, 17, 0, close_crest, &data);
	mlx_key_hook(data.win, key_hook, &data);
	mlx_loop(data.mlx);
	clear_lst_light(&data.light);
	free_list_obj(&data.obj);
	return (0);
}
