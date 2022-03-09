/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 00:12:15 by lcoreen           #+#    #+#             */
/*   Updated: 2022/03/09 13:26:38 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_light	*new_light(char *type, t_vec *pos, float ratio, t_color *color)
{
	t_light	*elem;

	elem = (t_light *) malloc(sizeof(t_light));
	if (elem == NULL)
		return (NULL);
	elem->pos = pos;
	elem->type = type;
	elem->l_ratio = ratio;
	elem->color = color;
	elem->next = NULL;
	return (elem);
}

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
		free(begin->pos);
		free(begin->color);
		free(begin);
		begin = next;
	}
	*lst = 0;
}
