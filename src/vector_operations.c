/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 14:29:48 by lcoreen           #+#    #+#             */
/*   Updated: 2022/03/15 17:24:03 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_vec(t_vec *vec, char *name)
{
	printf("%s: x = %f y = %f z = %f\n", name, vec->x, vec->y, vec->z);
}

t_vec	new_vector(float x, float y, float z)
{
	t_vec	ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	return (ret);
}

t_vec	vec_mul_nbr(t_vec *a, float k)
{
	t_vec	ret;

	ret.x = a->x * k;
	ret.y = a->y * k;
	ret.z = a->z * k;
	return (ret);
}

t_vec	vec_sum(t_vec *a, t_vec *b)
{
	return (new_vector(a->x + b->x, a->y + b->y, a->z + b->z));
}

t_vec	vec_sub(t_vec *a, t_vec *b)
{
	return (new_vector(a->x - b->x, a->y - b->y, a->z - b->z));
}
