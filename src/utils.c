/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 18:11:41 by lcoreen           #+#    #+#             */
/*   Updated: 2022/03/08 16:17:48 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minirt.h"

double	ft_atof(char *str)
{
	int		sign;
	double	res;
	int		deg;

	sign = 1;
	res = 0;
	deg = 0;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		++str;
	}
	while (*str >= '0' && *str <= '9')
		res = res * 10 + *str++ - '0';
	if (*str++ == '.')
	{
		while (*str >= '0' && *str <= '9')
		{
			res = res * 10 + *str - '0';
			++str;
			++deg;
		}
	}
	return (res * sign / pow(10, deg));
}

int	close_crest(void *param)
{
	t_data	*tmp;

	tmp = (t_data *) param;
	mlx_destroy_window(tmp->mlx, tmp->win);
	ft_lstclear(&tmp->figs, free);
	exit(0);
}
