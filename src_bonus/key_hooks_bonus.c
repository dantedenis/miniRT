/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 18:11:04 by lcoreen           #+#    #+#             */
/*   Updated: 2022/03/20 15:56:04 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keys.h"
#include "minirt_bonus.h"

static void	rotate_cam(t_cam *cam)
{
	//float	pre_x;
	float	pre_y;
	//float	pre_z;

	//pre_x = cam->orient.x;
	pre_y = cam->orient.y;
	//pre_z = cam->orient.z;
	cam->orient.y = pre_y * cos(cam->alpha) + cam->orient.z * sin(cam->alpha);
	cam->orient.z = -pre_y * sin(cam->alpha) + cam->orient.z * cos(cam->alpha);
	
	//cam->orient.x = pre_x * cos(cam->gamma) - pre_y * sin(cam->gamma);
}

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
	if (button == ESC)
		close_esc(data);
	if (button == KEY_LEFT)
		data->cam.pos.x -= 1;
	if (button == KEY_RIGHT)
		data->cam.pos.x += 1;
	if (button == KEY_UP)
		data->cam.pos.y += 1;
	if (button == KEY_DOWN)
		data->cam.pos.y -= 1;
	if (button == KEY_PLUS)
		data->cam.pos.z += 1;
	if (button == KEY_MINUS)
		data->cam.pos.z -= 1;
	if (button == KEY_Q)
	{
		data->cam.alpha +=0.05;
		rotate_cam(&data->cam);
	}
	if (button == KEY_A)
	{
		data->cam.alpha -=0.05;
		rotate_cam(&data->cam);
	}
	if (button == KEY_W)
	{
		data->cam.betta+=0.05;
		rotate_cam(&data->cam);
	}
	if (button == KEY_S)
	{
		data->cam.betta -=0.05;
		rotate_cam(&data->cam);
	}
	draw(data);
	return (0);
}
