/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:23:45 by lcoreen           #+#    #+#             */
/*   Updated: 2022/03/15 17:24:59 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	vec_scalar_mul(t_vec *a, t_vec *b)
{
	float	res;

	res = a->x * b->x + a->y * b->y + a->z * b->z;
	return (res);
}

float	vec_len(t_vec *a)
{
	float	res;

	res = sqrt(pow(a->x, 2) + pow(a->y, 2) + pow(a->z, 2));
	return (res);
}

void	vec_norm(t_vec *a)
{
	float	len;

	len = vec_len(a);
	a->x /= len;
	a->y /= len;
	a->z /= len;
}

t_vec	vec_copy(t_vec *src)
{
	return (new_vector(src->x, src->y, src->z));
}

t_vec	vec_mul(t_vec *a, t_vec *b)
{
	t_vec	ret;

	ret.x = a->y * b->z - a->z * b->y;
	ret.y = a->z * b->x - a->x * b->z;
	ret.z = a->x * b->y - a->y * b->x;
	return (ret);
}
