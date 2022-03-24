/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trasing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:35:28 by lcoreen           #+#    #+#             */
/*   Updated: 2022/03/21 10:11:51 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	save_parameters(t_obj *obj, t_obj **tmp, float t, float *clst_t)
{
	*tmp = obj;
	(*tmp)->t = t;
	*clst_t = t;
}

static float	intersect_figure(t_obj *obj, t_vec *ray, t_vec *o, float *t2)
{
	float	t1;

	t1 = 0.0;
	if (!ft_strncmp(obj->key, "sp", 3))
		t1 = intersect_sphere((t_sph *) obj->par, ray, o, t2);
	else if (!ft_strncmp(obj->key, "pl", 3))
		t1 = intersect_plane((t_pl *) obj->par, ray, o, t2);
	else if (!ft_strncmp(obj->key, "cy", 3))
		t1 = intersect_cylinder((t_cy *) obj->par, ray, o, t2);
	return (t1);
}

t_obj	*trasing(t_data *data, t_vec *o, float t_min, float t_max)
{
	t_obj	*closest_obj;
	t_obj	*obj;
	float	t1;
	float	t2;
	float	closest;

	closest = FLT_MAX;
	closest_obj = NULL;
	obj = data->obj;
	while (obj)
	{
		t1 = intersect_figure(obj, &data->ray, o, &t2);
		if ((t1 > t_min && t1 < t_max) && t1 < closest)
			save_parameters(obj, &closest_obj, t1, &closest);
		if ((t2 > t_min && t2 < t_max) && t2 < closest)
			save_parameters(obj, &closest_obj, t2, &closest);
		obj = obj->next;
	}
	return (closest_obj);
}

static int	get_color(t_data *data, t_vec *o)
{
	t_vec	p;
	t_vec	n;
	t_vec	closest_ray;
	t_obj	*clst_fig;
	int		color;

	clst_fig = trasing(data, o, 1, FLT_MAX);
	if (clst_fig == NULL)
		return (0);
	closest_ray = vec_mul_nbr(&data->ray, clst_fig->t);
	p = vec_sum(&closest_ray, o);
	if (!ft_strncmp(clst_fig->key, "sp", 3))
		n = vec_sub(&p, &((t_sph *) clst_fig->par)->cntr);
	else if (!ft_strncmp(clst_fig->key, "cy", 3))
		n = get_cy_norm((t_cy *) clst_fig->par, &data->ray, o, clst_fig->t);
	else
		n = vec_copy(&((t_pl *) clst_fig->par)->n);
	vec_norm(&n);
	closest_ray = compute_light(data, data->light, &p, &n);
	color = mul_pcolor(&clst_fig->color, &closest_ray);
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
