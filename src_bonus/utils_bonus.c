/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 18:11:41 by lcoreen           #+#    #+#             */
/*   Updated: 2022/03/23 19:10:41 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"
#include "errors.h"

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
	if (data)
	{
		mlx_destroy_window(data->mlx, data->win);
		clear_lst_light(&data->light);
		free_list_obj(&data->obj);
	}
	exit(0);
}

void	ft_put(t_data *data, t_obj *obj)
{
	if (ft_isupper(*obj->key))
		check_dupl(data, *obj->key);
	if (data->obj)
	{
		obj->next = data->obj;
		data->obj = obj;
	}
	else
	{
		data->obj = obj;
		obj->next = NULL;
	}
}

void	check_dupl(t_data *data, char ch)
{
	t_obj	*temp;

	temp = data->obj;
	while (temp)
	{
		if (*temp->key == ch)
			error("duplicate in config", data, -1);
		temp = temp->next;
	}
}
