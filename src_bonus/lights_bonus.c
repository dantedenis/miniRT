/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 00:12:15 by lcoreen           #+#    #+#             */
/*   Updated: 2022/03/16 21:44:55 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

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
