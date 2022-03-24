/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:41:49 by bstrong           #+#    #+#             */
/*   Updated: 2022/03/23 18:44:32 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	rotate_cam_x(t_cam *cam)
{
	float	pre_y;

	pre_y = cam->orient.y;
	cam->orient.y = pre_y * cos(cam->alpha) + cam->orient.z * sin(cam->alpha);
	cam->orient.z = -pre_y * sin(cam->alpha) + cam->orient.z * cos(cam->alpha);
}

void	rotate_cam_y(t_cam *cam)
{
	float	pre_x;

	pre_x = cam->orient.x;
	cam->orient.x = pre_x * cos(cam->betta) + cam->orient.z * sin(cam->betta);
	cam->orient.z = -pre_x * sin(cam->betta) + cam->orient.z * cos(cam->betta);
}

void	rotate_cam_z(t_cam *cam)
{
	float	pre_x;
	float	pre_y;

	pre_x = cam->orient.x;
	pre_y = cam->orient.y;
	cam->orient.x = pre_x * cos(cam->gamma) - pre_y * sin(cam->gamma);
	cam->orient.y = pre_x * sin(cam->gamma) + pre_y * cos(cam->gamma);
}
