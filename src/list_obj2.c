/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_obj2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 19:37:21 by bstrong           #+#    #+#             */
/*   Updated: 2022/03/23 22:04:07 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_sphere(char **lines, t_data *data, int line)
{
	t_obj	*new_obj;

	if (len_arr(lines) != 4)
		error("init sphere (parameters)", data, line);
	new_obj = (t_obj *) ft_calloc(1, sizeof(t_obj));
	if (!new_obj)
		error("allocation mem for sphere", data, line);
	new_obj->par = malloc(sizeof(t_sph));
	if (!new_obj->par && free_void(new_obj))
		error("allocation mem for sphere", data, line);
	new_obj->key = "sp";
	((t_sph *)new_obj->par)->cntr = get_vector_check(lines[1], 0, data, line);
	((t_sph *)new_obj->par)->radius = ft_atof(lines[2]) / 2.;
	new_obj->color = get_color_check(lines[3], data, line);
	if (((t_sph *)new_obj->par)->radius <= 0 && free_void(new_obj->par)
		&& free_void(new_obj))
		error("init sphere (parameters)", data, line);
	ft_put(data, new_obj);
}

void	init_plane(char **lines, t_data *data, int line)
{
	t_obj	*new_obj;

	if (len_arr(lines) != 4)
		error("init plane (parameters)", data, line);
	new_obj = (t_obj *) ft_calloc(1, sizeof(t_obj));
	if (!new_obj)
		error("allocation mem for plane", data, line);
	new_obj->par = malloc(sizeof(t_pl));
	if (!new_obj->par && free_void(new_obj))
		error("allocation mem for plane", data, line);
	new_obj->key = "pl";
	((t_pl *)new_obj->par)->c = get_vector_check(lines[1], 0, data, line);
	((t_pl *)new_obj->par)->n = get_vector_check(lines[2], 1, data, line);
	new_obj->color = get_color_check(lines[3], data, line);
	vec_norm(&((t_pl *)new_obj->par)->n);
	ft_put(data, new_obj);
}

void	init_cylinder(char **lines, t_data *data, int line)
{
	t_obj	*new_obj;

	if (len_arr(lines) != 6)
		error("init cylinder (parameters)", data, line);
	new_obj = (t_obj *) ft_calloc(1, sizeof(t_obj));
	if (!new_obj)
		error("allocation mem for cylinder", data, line);
	new_obj->par = malloc(sizeof(t_cy));
	if (!new_obj->par && free_void(new_obj))
		error("allocation mem for cylinder", data, line);
	new_obj->key = "cy";
	((t_cy *)new_obj->par)->pos = get_vector_check(lines[1], 0, data, line);
	((t_cy *)new_obj->par)->norm = get_vector_check(lines[2], 1, data, line);
	((t_cy *)new_obj->par)->diameter = ft_atof(lines[3]);
	((t_cy *)new_obj->par)->height = ft_atof(lines[4]);
	if ((((t_cy *)new_obj->par)->diameter <= 0
			|| ((t_cy *)new_obj->par)->height <= 0)
		&& free_void(new_obj->par) && free_void(new_obj))
		error("init cylinder (parameters)", data, line);
	((t_cy *)new_obj->par)->part = 0;
	new_obj->color = get_color_check(lines[5], data, line);
	vec_norm(&((t_cy *)new_obj->par)->norm);
	ft_put(data, new_obj);
}
