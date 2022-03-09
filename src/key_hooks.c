/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 18:11:04 by lcoreen           #+#    #+#             */
/*   Updated: 2022/03/09 13:16:05 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keys.h"
#include "minirt.h"

static int	close_esc(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	clear_lst_sph(&data->sph);
	clear_lst_light(&data->light);
	exit(0);
	return (0);
}

int	key_hook(int button, t_data *data)
{
	if (button == ESC)
		close_esc(data);
	return (0);
}
