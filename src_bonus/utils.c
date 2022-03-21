/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 18:11:41 by lcoreen           #+#    #+#             */
/*   Updated: 2022/03/18 22:31:08 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minirt_bonus.h"

// double	ft_atof(char *str)
// {
// 	int		sign;
// 	double	res;
// 	int		deg;

// 	sign = 1;
// 	res = 0;
// 	deg = 0;
// 	if (*str == '-' || *str == '+')
// 	{
// 		if (*str == '-')
// 			sign *= -1;
// 		++str;
// 	}
// 	while (*str >= '0' && *str <= '9')
// 		res = res * 10 + *str++ - '0';
// 	if (*str++ == '.')
// 	{
// 		while (*str >= '0' && *str <= '9')
// 		{
// 			res = res * 10 + *str - '0';
// 			++str;
// 			++deg;
// 		}
// 	}
// 	return (res * sign / pow(10, deg));
// }

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
