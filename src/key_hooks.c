/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 18:11:04 by lcoreen           #+#    #+#             */
/*   Updated: 2022/03/19 23:37:16 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keys.h"
#include "minirt.h"

static int	close_esc(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	clear_lst_light(&data->light);
	free_list_obj(&data->obj);
	exit(0);
	return (0);
}

int	key_hook(int button, t_data *data)
{
	//if (button == ESC)
	//	close_esc(data);
	//if (button == KEY_5)
	//	data->cam.pos.x += 3;
	//if (button == KEY_6)
	//	data->cam.pos.x -= 3;
	//data->cam.orient.x +=10;
	//data->cam.fov +=3;
	//draw(data);
	return (0);
}
