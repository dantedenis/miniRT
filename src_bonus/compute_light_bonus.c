/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_light_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:37:33 by lcoreen           #+#    #+#             */
/*   Updated: 2022/03/23 17:40:17 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	add_intensity(t_vec *a, t_color *b, float k)
{
	a->x += k * b->r / 255;
	a->y += k * b->g / 255;
	a->z += k * b->b / 255;
}

t_vec	reflect_ray(t_vec *N, t_vec *ray)
{
	t_vec	r;

	r = vec_mul_nbr(N, 2 * vec_scalar_mul(N, ray));
	r = vec_sub(&r, ray);
	return (r);
}

static float	specular(t_data *d, t_vec *N, t_vec *V, float k)
{
	t_vec	rt;
	float	t;
	float	ret;

	ret = 0;
	if (d->clst_obj->spec != -1)
	{
		rt = reflect_ray(N, &d->ray);
		t = vec_scalar_mul(&rt, V);
		if (t > 0)
			ret = k * pow(t / (vec_len(&rt) * vec_len(V)), d->clst_obj->spec);
	}
	return (ret);
}

static float	diffusion(t_data *data, t_vec *N, float ratio)
{
	float	t;
	float	ret;

	ret = 0;
	t = vec_scalar_mul(&data->ray, N);
	if (t > 0)
		ret = t * ratio / vec_len(&data->ray);
	return (ret);
}

t_vec	compute_light(t_data *d, t_light *l, t_vec *P, t_vec *N)
{
	t_vec	i;
	t_vec	v;

	v = vec_mul_nbr(&d->ray, -1);
	i = new_vector(0, 0, 0);
	while (l)
	{
		if (!ft_strncmp(l->type, "A", 2))
			add_intensity(&i, &l->color, l->ratio);
		else
		{
			d->ray = vec_sub(&l->pos, P);
			if (trasing(d, P, 0.001, 1))
			{
				l = l->next;
				continue ;
			}
			add_intensity(&i, &l->color, diffusion(d, N, l->ratio));
			add_intensity(&i, &l->color, specular(d, N, &v, l->ratio));
		}
		l = l->next;
	}
	return (i);
}
