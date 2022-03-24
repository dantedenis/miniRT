/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:38:32 by lcoreen           #+#    #+#             */
/*   Updated: 2022/03/24 11:57:11 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

static float	solve_cy(t_cy *tmp, t_vec *ray, t_vec *o, float *t2)
{
	t_vec	oc;
	float	a;
	float	b;
	float	c;
	float	descr;

	oc = vec_sub(o, &tmp->pos);
	a = vec_scalar_mul(ray, ray) - pow(vec_scalar_mul(ray, &tmp->norm), 2);
	b = 2 * (vec_scalar_mul(ray, &oc) - vec_scalar_mul(ray, &tmp->norm)
			* vec_scalar_mul(&oc, &tmp->norm));
	c = vec_scalar_mul(&oc, &oc) - pow(vec_scalar_mul(&oc, &tmp->norm), 2)
		- (pow(tmp->diameter / 2, 2));
	descr = pow(b, 2) - 4 * a * c;
	if (descr < 0)
	{
		*t2 = FLT_MAX;
		return (FLT_MAX);
	}
	*t2 = (-b - sqrt(descr)) / (2 * a);
	return ((-b + sqrt(descr)) / (2 * a));
}

static float	solve_cy_cap(t_cy *tmp, t_pl *plane, t_vec *ray, t_vec *o)
{
	t_vec	pc;
	float	t;

	t = intersect_plane(plane, ray, o, NULL);
	if (t < FLT_MAX)
	{
		pc = vec_mul_nbr(ray, t);
		pc = vec_sum(&pc, o);
		pc = vec_sub(&pc, &plane->c);
		if (vec_len(&pc) <= tmp->diameter / 2)
			return (t);
	}
	return (FLT_MAX);
}

static float	solve_cy_caps(t_cy *tmp, t_vec *ray, t_vec *o)
{
	t_pl	plane;
	float	t;

	plane.c = tmp->pos;
	plane.n = vec_mul_nbr(&tmp->norm, -1);
	t = solve_cy_cap(tmp, &plane, ray, o);
	if (t < FLT_MAX)
	{
		tmp->part = -1;
		return (t);
	}
	plane.c = vec_mul_nbr(&tmp->norm, tmp->height);
	plane.c = vec_sum(&tmp->pos, &plane.c);
	plane.n = tmp->norm;
	t = solve_cy_cap(tmp, &plane, ray, o);
	if (t < FLT_MAX)
	{
		tmp->part = 1;
		return (t);
	}
	return (FLT_MAX);
}

float	intersect_cylinder(t_cy *tmp, t_vec *ray, t_vec *o, float *t2)
{
	float	t;
	t_vec	oc;
	float	m;

	tmp->part = 0;
	t = solve_cy(tmp, ray, o, t2);
	if (t == FLT_MAX)
		return (FLT_MAX);
	if (*t2 < t)
		t = *t2;
	oc = vec_sub(o, &tmp->pos);
	m = vec_scalar_mul(&oc, &tmp->norm) + t * vec_scalar_mul(ray, &tmp->norm);
	if (m <= 0 || m >= tmp->height)
	{
		*t2 = FLT_MAX;
		t = solve_cy_caps(tmp, ray, o);
	}
	return (t);
}
