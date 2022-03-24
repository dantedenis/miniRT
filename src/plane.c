/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:40:23 by lcoreen           #+#    #+#             */
/*   Updated: 2022/03/15 16:40:32 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
