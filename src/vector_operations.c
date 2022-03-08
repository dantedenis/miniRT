/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 14:29:48 by lcoreen           #+#    #+#             */
/*   Updated: 2022/03/08 14:41:09 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	*new_vector(float x, float y, float z)
{
	t_vec	*ret;

	ret = (t_vec *) malloc(sizeof(t_vec));
	if (!ret)
		return (NULL);
	ret->x = x;
	ret->y = y;
	ret->z = z;
	return (ret);
}

t_vec	*vec_sub(t_vec *a, t_vec *b)
{
	t_vec	*res;

	res = new_vector(a->x - b->x, a->y - b->y, a->z - b->z);
	if (!res)
		return (NULL);
	return (res);
}

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

