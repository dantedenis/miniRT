/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:41:49 by bstrong           #+#    #+#             */
/*   Updated: 2022/03/24 21:18:53 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static double deg2rad(float deg)
{
	return deg / 57.29578;
}

void	rotate_cam_x(t_cam *cam)
{
	float	pre_y;

	pre_y = cam->orient.y;
	cam->orient.y = pre_y * cos(deg2rad(cam->alpha)) + cam->orient.z * sin(deg2rad(cam->alpha));
	cam->orient.z = -pre_y * sin(deg2rad(cam->alpha)) + cam->orient.z * cos(deg2rad(cam->alpha));
	if (fabs(cam->orient.y) != 1)
		cam->up = new_vector(0, 1, 0);
	else
		cam->up = new_vector(1, 0, 0);
	cam->right = vec_mul(&cam->up, &cam->orient);
	cam->up = vec_mul(&cam->orient, &cam->right);
	vec_norm(&cam->orient);
}

void	rotate_cam_y(t_cam *cam)
{
	float	pre_x;

	pre_x = cam->orient.x;
	cam->orient.x = pre_x * cos(deg2rad(cam->betta)) + cam->orient.z * sin(deg2rad(cam->betta));
	cam->orient.z = -pre_x * sin(deg2rad(cam->betta)) + cam->orient.z * cos(deg2rad(cam->betta));
	if (fabs(cam->orient.y) != 1)
		cam->up = new_vector(0, 1, 0);
	else
		cam->up = new_vector(1, 0, 0);
	cam->right = vec_mul(&cam->up, &cam->orient);
	cam->up = vec_mul(&cam->orient, &cam->right);
	vec_norm(&cam->orient);
}

void	rotate_cam_z(t_cam *cam)
{
	float	pre_x;
	float	pre_y;

	pre_x = cam->orient.x;
	pre_y = cam->orient.y;
	cam->orient.x = pre_x * cos(cam->gamma) - pre_y * sin(cam->gamma);
	cam->orient.y = pre_x * sin(cam->gamma) + pre_y * cos(cam->gamma);
	if (fabs(cam->orient.y) != 1)
		cam->up = new_vector(0, 1, 0);
	else
		cam->up = new_vector(1, 0, 0);
	cam->right = vec_mul(&cam->up, &cam->orient);
	cam->up = vec_mul(&cam->orient, &cam->right);
	vec_norm(&cam->orient);
}
