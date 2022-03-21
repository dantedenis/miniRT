/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 21:49:43 by lcoreen           #+#    #+#             */
/*   Updated: 2022/03/19 11:13:31 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_color	uv_pattern_at(float u, float v)
{
	int	u2;
	int	v2;

	u2 = u * 16;
	v2 = v * 8;
	if ((u2 + v2) % 2 == 0)
		return (new_color(255, 255, 255));
	else
		return (new_color(0, 0, 0));
}

t_color	spherical_map(t_sph *fig, t_vec *p)
{
	t_vec	pc;
	float	u;
	float	v;

	pc = vec_sub(p, &fig->cntr);
	u = 1 - (atan2(pc.x, pc.z) / (2 * M_PI) + 0.5);
	v = 1 - acos(pc.y / fig->radius) / M_PI;
	return (uv_pattern_at(u, v));
}

t_color	planar_map(t_pl *fig, t_vec *p)
{
	t_vec	pc;
	float	u;
	float	v;
	//float	k;

	pc = vec_sub(p, &fig->c);
	print_vec(&pc, "pc");
	u = pc.x - (int) pc.x;
	v = pc.z - (int) pc.z;
	return (uv_pattern_at(u, v));
}

t_color	cylinder_map(t_cy *fig, t_vec *p)
{
	t_vec	pc;
	float	u;
	float	v;

	pc = vec_sub(p, &fig->pos);
	u = 1 - (atan2(pc.x, pc.z) / (2 * M_PI) + 0.5);
	v = 1 - acos(pc.y / fig->diameter * 2) / M_PI;
	return (uv_pattern_at(u, v));
}
