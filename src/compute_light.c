/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:37:33 by lcoreen           #+#    #+#             */
/*   Updated: 2022/03/15 17:02:21 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	add_intensity(t_vec *a, t_color *b, float k)
{
	a->x += k * b->r / 255;
	a->y += k * b->g / 255;
	a->z += k * b->b / 255;
}

t_vec	compute_light(t_data *d, t_light *l, t_vec *P, t_vec *N)
{
	t_vec	i;
	float	t;
	t_obj	*close_obj;

	i = new_vector(0, 0, 0);
	while (l)
	{
		if (!ft_strncmp(l->type, "A", 2))
			add_intensity(&i, &l->color, l->ratio);
		else
		{
			d->ray = vec_sub(&l->pos, P);
			close_obj = trasing(d, P, 0.001, 1);
			if (close_obj)
			{
				l = l->next;
				continue ;
			}
			t = vec_scalar_mul(&d->ray, N);
			if (t > 0)
				add_intensity(&i, &l->color, l->ratio * t / vec_len(&d->ray));
		}
		l = l->next;
	}
	return (i);
}
