/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 18:11:11 by lcoreen           #+#    #+#             */
/*   Updated: 2022/03/13 21:35:59 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "errors.h"


float	intersect_plane(t_pl *tmp, t_vec *ray, t_vec *o, float *t2)
{
	float	c;
	float	ret;

	if (t2)
		*t2 = FLT_MAX;
	c = vec_scalar_mul(ray, &tmp->n);
	if (c == 0)
		return (FLT_MAX);
	ret = (tmp->d - vec_scalar_mul(o, &tmp->n)) / c;
	if (ret < 0)
		return (FLT_MAX);
	return (ret);
}

float	intersect_cylinder(t_cy *tmp, t_vec *ray, t_vec *o, float *t2)
{
	t_vec	v;
	t_vec	u;
	t_vec	n;
	t_vec	oc;
	float	a;
	float	b;
	float	c;
	float	descr;
	float	t1;
	float	t;
	t_pl	plane;

	v = vec_mul_nbr(&tmp->norm, vec_scalar_mul(&tmp->norm, ray));
	v = vec_sub(ray, &v);
	oc = vec_sub(o, &tmp->pos);
	u = vec_mul_nbr(&tmp->norm, vec_scalar_mul(&oc, &tmp->norm));
	u = vec_sub(&oc, &u);
	a = vec_scalar_mul(&v, &v);
	b = 2 * vec_scalar_mul(&v, &u);
	c = vec_scalar_mul(&u, &u) - (pow(tmp->diameter / 2, 2));
	descr = pow(b, 2) - 4 * a * c;
	if (descr < 0)
		return (FLT_MAX);
	t1 = (-b + sqrt(descr)) / (2 * a);
	*t2 = (-b - sqrt(descr)) / (2 * a);
	plane.d = vec_scalar_mul(&tmp->pos, &tmp->norm) + tmp->height
			* vec_scalar_mul(&tmp->norm, &tmp->norm) / 2;
	plane.n = tmp->norm;
	t = intersect_plane(&plane, ray, o, NULL);
	if (t > tmp->height / 2)
		t1 = t;
	n = vec_mul_nbr(&tmp->norm, -1);
	plane.d = vec_scalar_mul(&tmp->pos, &n) + tmp->height
			* vec_scalar_mul(&n, &n) / 2;
	plane.n = n;
	t = intersect_plane(&plane, ray, o, NULL);
	if (t > tmp->height / 2)
		t1 = t;
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

	closest_fig = trasing(data, o, 0.1, FLT_MAX);
	if (closest_fig == NULL)
		return (0);
	if (!ft_strncmp(closest_fig->key, "cy", 3))
		return (pcolor_from_struct(&closest_fig->color));
	closest_ray = vec_mul_nbr(&data->ray, closest_fig->t);
	P = vec_sum(&closest_ray, o);
	if (!ft_strncmp(closest_fig->key, "sp", 3))
		N = vec_sub(&P, &((t_sph *) closest_fig->par)->cntr);
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
	
	sc_x = tan(data->cam.fov * M_PI / 360) * x / data->w;
	sc_y = data->whratio * y / data->h;
	data->ray = new_vector(sc_x, sc_y, 1);
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

	(void) argv;
	(void) argc;
	ft_bzero(&data, sizeof(t_data));
	data.mlx = mlx_init();
	if (!data.mlx)
		error(ERROR_MLX);
	data.w = 400;
	data.h = 300;
	data.whratio = (float) data.h / data.w;
	parser("C 0.0,0.0,-50.0 0,0,1 90", &data);
	parser("A 0.2 255,255,255", &data);
	parser("L 0.0,50.0,50.0 1 255,255,255", &data);
	// parser("sp 0.0,0.0,100.0  30 255,0,10", &data);
	// parser("sp 0,20.0,150.0  20.0 10,0,255", &data);
	// parser("sp 30,20,90 20.0 10,255,0", &data);
	parser("pl 0.0,-50,0.0 0,1,0 124,124,140", &data);
	// parser("A 1 255,255,255", &data);
	// parser("C 0,0,-100 0,0,1", &data);
	parser("cy 0,0,100 0,1,0 20 10 10,0,255", &data);
	// TODO (bstrong): Парсер файла через гнл шоб не париться с изменением параметров в мейнике)
	// TODO (lcoreen): Добавить обработку цилиндра
	// CHANGES: Поменял структуры сферы и плоскости, все общие поля вынес в obj (color, параметр t)
	// 			В структурах остаются только их геометрические параметры
	//			Лист объектов хранит только объекты фигур и их параметры
	//			Лист света (data.light) хранит свет в виде одного типа t_light (для определения типа света используется data.light->type)
	//			Камера в структуре расположена тоже отдельным полем (data.cam)
	//			Изменения в структуре data немного коснулись функций list_obj.c (не сильно :))
	// =======> TODO: Добавить структуру цилиндра шоб она в себе хранила ток нужные геомертрические параметры
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
