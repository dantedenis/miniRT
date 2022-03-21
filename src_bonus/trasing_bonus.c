/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trasing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:12:50 by lcoreen           #+#    #+#             */
/*   Updated: 2022/03/19 13:09:09 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

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
	else if (!ft_strncmp(obj->key, "co", 3))
		t1 = intersect_cone((t_co *) obj->par, ray, o, t2);
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
