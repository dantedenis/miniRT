/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:39:35 by lcoreen           #+#    #+#             */
/*   Updated: 2022/03/15 16:39:44 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
