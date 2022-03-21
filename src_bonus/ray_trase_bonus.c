/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trase.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:35:28 by lcoreen           #+#    #+#             */
/*   Updated: 2022/03/18 17:16:47 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static t_color	get_color(t_data *data, t_vec *o, float t_min, float t_max);

static t_color	ray_effects(t_data *data, t_vec *p, t_vec *n)
{
	t_vec	l;

	l = compute_light(data, data->light, p, n);
	return (color_mul_vec(&data->clst_obj->color, &l));
}

static t_color	reflection(t_data *data, t_vec *p, t_color *color)
{
	t_color	refl_color;
	float	r;

	r = data->clst_obj->refl;
	refl_color = get_color(data, p, 0.01, FLT_MAX);
	color_mul_nbr(color, 1 - r);
	color_mul_nbr(&refl_color, r);
	return (color_sum(color, &refl_color));
}

static t_color	get_color(t_data *data, t_vec *o, float t_min, float t_max)
{
	t_vec	p;
	t_vec	n;
	t_vec	d;
	t_color	color;

	d = vec_mul_nbr(&data->ray, -1);
	data->clst_obj = trasing(data, o, t_min, t_max);
	if (data->clst_obj == NULL)
		return (new_color(0, 0, 0));
	p = vec_mul_nbr(&data->ray, data->clst_obj->t);
	p = vec_sum(&p, o);
	n = get_norm(data, o, &p);
	color = ray_effects(data, &p, &n);
	if (data->depth <= 0 || data->clst_obj->refl <= 0)
		return (color);
	data->ray = reflect_ray(&n, &d);
	--data->depth;
	return (reflection(data, &p, &color));
}

int	ray_trase(t_data *data, t_vec *o, int x, int y)
{
	float	sc_x;
	float	sc_y;
	t_color	color;
	t_vec	u;
	t_vec	v;

	data->depth = 2;
	sc_x = tan(data->cam.fov * M_PI / 360) * x / data->w;
	sc_y = data->whratio * y / data->h;
	u = vec_mul_nbr(&data->cam.right, sc_x);
	v = vec_mul_nbr(&data->cam.up, sc_y);
	data->ray = vec_sum(&u, &v);
	data->ray = vec_sum(&data->ray, &data->cam.orient);
	color = get_color(data, o, 1, FLT_MAX);
	return (pcolor(&color));
}
