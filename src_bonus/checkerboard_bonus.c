/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 21:49:43 by lcoreen           #+#    #+#             */
/*   Updated: 2022/03/21 20:20:58 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static t_color	uv_pattern_at(float u, float v)
{
	int	u2;
	int	v2;

	u2 = 8 * u;
	v2 = 8 * v;
	if ((u2 + v2) % 2 == 0)
		return (new_color(255, 255, 255));
	else
		return (new_color(0, 0, 0));
}

static t_color	spherical_map(t_sph *fig, t_vec *p)
{
	t_vec	pc;
	float	u;
	float	v;

	pc = vec_sub(p, &fig->cntr);
	u = 1 - (atan2(pc.x, pc.z) / (2 * M_PI) + 0.5);
	v = 1 - acos(pc.y / fig->radius) / M_PI;
	return (uv_pattern_at(u, v));
}

static t_color	planar_map(t_pl *fig, t_vec *p, t_vec *o)
{
	t_vec	pc;
	float	u;
	float	v;
	float	k;

	pc = vec_sub(o, &fig->c);
	k = vec_len(&pc);
	pc = vec_sub(p, &fig->c);
	u = ((1 - fig->n.x) * pc.x + fig->n.y * pc.y) / k;
	v = ((1 - fig->n.z) * pc.z + (1 - fig->n.y) * pc.y) / k;
	u -= (int) u;
	v -= (int) v;
	return (uv_pattern_at(u, v));
}

static t_color	cylinder_map(t_cy *fig, t_vec *p, t_vec *o)
{
	t_vec	pc;
	float	u;
	float	v;
	float	k;

	pc = vec_sub(o, &fig->pos);
	k = vec_len(&pc);
	pc = vec_sub(p, &fig->pos);
	u = 1 - (atan2(pc.x, pc.z) / (2 * M_PI) + 0.5);
	v = 5 * vec_scalar_mul(&pc, &fig->norm) / k;
	v -= (int) v;
	return (uv_pattern_at(u, v));
}

t_color	checkerboard(t_obj *fig, t_vec *p, t_vec *o)
{
	if (!ft_strncmp(fig->key, "pl", 3))
		return (planar_map(fig->par, p, o));
	else if (!ft_strncmp(fig->key, "cy", 3))
		return (cylinder_map(fig->par, p, o));
	return (spherical_map(fig->par, p));
}
