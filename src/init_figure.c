/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_figure.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:11:29 by lcoreen           #+#    #+#             */
/*   Updated: 2022/03/11 22:26:55 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sph	*new_sph(t_vec *cntr, float radius, t_color *color)
{
	t_sph	*ret;

	ret = (t_sph *) malloc(sizeof(t_sph));
	if (!ret)
		return (NULL);
	ret->cntr = cntr;
	ret->radius = radius;
	ret->color = color;
	ret->next = NULL;
	return (ret);
}

void	sph_add(t_sph **sph, t_sph *new)
{
	new->next = *sph;
	*sph = new;
}

void	clear_lst_sph(t_sph	**lst)
{
	t_sph	*next;
	t_sph	*begin;

	begin = *lst;
	while (begin)
	{
		next = begin->next;
		free(begin->cntr);
		free(begin->color);
		free(begin);
		begin = next;
	}
	*lst = 0;
}

t_plane	*new_plane(t_vec *n, t_vec *coord, t_color *color)
{
	t_plane	*ret;

	ret = (t_plane *) malloc(sizeof(t_plane));
	if (!ret)
		return (NULL);
	ret->n = n;
	ret->d = vec_scalar_mul(coord, n);
	ret->color = color;
	ret->next = NULL;
	free(coord);
	return (ret);
}

t_plane	plane_add(t_plane **plane, t_plane *new)
{
	new->next = *plane;
	*plane = new;
}

void	clear_lst_plane(t_plane	**lst)
{
	t_plane	*next;
	t_plane	*begin;

	begin = *lst;
	while (begin)
	{
		next = begin->next;
		free(begin->n);
		free(begin->color);
		free(begin);
		begin = next;
	}
	*lst = 0;
}
