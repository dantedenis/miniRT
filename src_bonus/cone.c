/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 12:36:42 by lcoreen           #+#    #+#             */
/*   Updated: 2022/03/18 15:56:57 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static float	solve_cone(t_co *tmp, t_vec *ray, t_vec *o, float *t2)
{
	t_vec	oc;
	float	a;
	float	b;
	float	c;
	float	t;

	t = 1 + pow(tmp->k, 2);
	oc = vec_sub(o, &tmp->pos);
	a = vec_scalar_mul(ray, ray) - t * pow(vec_scalar_mul(ray, &tmp->norm), 2);
	b = 2 * (vec_scalar_mul(ray, &oc) - t * vec_scalar_mul(ray, &tmp->norm)
			* vec_scalar_mul(&oc, &tmp->norm));
	c = vec_scalar_mul(&oc, &oc) - t * pow(vec_scalar_mul(&oc, &tmp->norm), 2);
	t = pow(b, 2) - 4 * a * c;
	if (t < 0)
	{
		*t2 = FLT_MAX;
		return (FLT_MAX);
	}
	*t2 = (-b - sqrt(t)) / (2 * a);
	return ((-b + sqrt(t)) / (2 * a));
}

static float	solve_co_cap(t_co *tmp, t_vec *ray, t_vec *o)
{
	t_pl	plane;
	float	t;
	t_vec	pc;

	plane.c = vec_mul_nbr(&tmp->norm, tmp->height);
	plane.c = vec_sum(&tmp->pos, &plane.c);
	plane.n = tmp->norm;
	t = intersect_plane(&plane, ray, o, NULL);
	if (t < FLT_MAX)
	{
		pc = vec_mul_nbr(ray, t);
		pc = vec_sum(&pc, o);
		pc = vec_sub(&pc, &plane.c);
		if (vec_len(&pc) <= tmp->height * tmp->k)
		{
			tmp->part = 1;
			return (t);
		}
	}
	return (FLT_MAX);
}

float	intersect_cone(t_co *tmp, t_vec *ray, t_vec *o, float *t2)
{
	float	t;
	t_vec	oc;
	float	m;

	tmp->part = 0;
	t = solve_cone(tmp, ray, o, t2);
	if (*t2 > 0 && *t2 < t)
		t = *t2;
	oc = vec_sub(o, &tmp->pos);
	m = vec_scalar_mul(&oc, &tmp->norm) + t * vec_scalar_mul(ray, &tmp->norm);
	if (m <= 0 || m >= tmp->height)
	{
		*t2 = FLT_MAX;
		t = solve_co_cap(tmp, ray, o);
	}
	return (t);
}
