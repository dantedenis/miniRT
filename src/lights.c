/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 00:12:15 by lcoreen           #+#    #+#             */
/*   Updated: 2022/03/13 21:05:40 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// t_light	*new_light(char *type, t_vec *pos, float ratio, t_color *color)
// {
// 	t_light	*elem;

// 	elem = (t_light *) malloc(sizeof(t_light));
// 	if (elem == NULL)
// 		return (NULL);
// 	elem->pos = pos;
// 	elem->type = type;
// 	elem->ratio = ratio;
// 	elem->color = color;
// 	elem->next = NULL;
// 	return (elem);
// }

void	light_add(t_light **light, t_light *new)
{
	new->next = *light;
	*light = new;
}

void	clear_lst_light(t_light	**lst)
{
	t_light	*next;
	t_light	*begin;

	begin = *lst;
	while (begin)
	{
		next = begin->next;
		free(begin->type);
		free(begin);
		begin = next;
	}
	*lst = 0;
}

void	add_intensity(t_vec *a, t_color *b, float k)
{
	a->x += k * b->r / 255;
	a->y += k * b->g / 255;
	a->z += k * b->b / 255;
}
