/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 18:11:41 by lcoreen           #+#    #+#             */
/*   Updated: 2022/03/21 10:17:55 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minirt_bonus.h"

void	free_arr(char ***arr)
{
	char	**tmp;
	int		i;

	tmp = *arr;
	i = 0;
	while (tmp[i])
	{
		free(tmp[i]);
		++i;
	}
	free(tmp);
	*arr = NULL;
}

void	free_list_obj(t_obj **lst)
{
	t_obj	*tmp;
	t_obj	*next;

	tmp = *lst;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->par);
		free(tmp);
		tmp = next;
	}
	*lst = NULL;
}

int	close_crest(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	clear_lst_light(&data->light);
	free_list_obj(&data->obj);
	exit(0);
}
