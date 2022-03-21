/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_norm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 15:53:12 by lcoreen           #+#    #+#             */
/*   Updated: 2022/03/18 16:52:37 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static t_vec	get_co_norm(t_co *co, t_vec *ray, t_vec *o, float t)
{
	t_vec	oc;
	t_vec	tmp;
	float	k;

	if (!co->part)
	{
		k = 1 + pow(co->k, 2);
		oc = vec_sub(o, &co->pos);
		tmp = vec_mul_nbr(&co->norm, k * vec_scalar_mul(ray, &co->norm));
		tmp = vec_sub(ray, &tmp);
		tmp = vec_mul_nbr(&tmp, t);
		tmp = vec_sum(&tmp, &oc);
		oc = vec_mul_nbr(&co->norm, k * vec_scalar_mul(&oc, &co->norm));
		tmp = vec_sub(&tmp, &oc);
		return (tmp);
	}
	else
		return (co->norm);
}

static t_vec	get_cy_norm(t_cy *cy, t_vec *ray, t_vec *o, float t)
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

t_vec	get_norm(t_data *data, t_vec *o, t_vec *p)
{
	t_vec	n;
	t_obj	*tmp;

	tmp = data->clst_obj;
	if (!ft_strncmp(tmp->key, "sp", 3))
		n = vec_sub(p, &((t_sph *) tmp->par)->cntr);
	else if (!ft_strncmp(tmp->key, "cy", 3))
		n = get_cy_norm(tmp->par, &data->ray, o, tmp->t);
	else if (!ft_strncmp(tmp->key, "co", 3))
		n = get_co_norm(tmp->par, &data->ray, o, tmp->t);
	else
		n = ((t_pl *) tmp->par)->n;
	vec_norm(&n);
	return (n);
}
