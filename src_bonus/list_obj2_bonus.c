/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_obj2_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 19:14:04 by bstrong           #+#    #+#             */
/*   Updated: 2022/03/23 22:06:02 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	init_sphere(char **lines, t_data *data, int line)
{
	t_obj	*new_obj;

	if (len_arr(lines) != 6)
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
	new_obj->checker = !ft_strncmp(lines[3], "check", 6);
	if (!new_obj->checker)
		new_obj->color = get_color_check(lines[3], data, line);
	if (((t_sph *)new_obj->par)->radius <= 0 && free_void(new_obj->par)
		&& free_void(new_obj))
		error("init sphere (parameters)", data, line);
	new_obj->spec = ft_atof(lines[4]);
	new_obj->refl = ft_atof(lines[5]);
	ft_put(data, new_obj);
}

void	init_plane(char **lines, t_data *data, int line)
{
	t_obj	*new_obj;

	if (len_arr(lines) != 6)
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
	new_obj->checker = !ft_strncmp(lines[3], "check", 6);
	if (!new_obj->checker)
		new_obj->color = get_color_check(lines[3], data, line);
	new_obj->spec = ft_atof(lines[4]);
	new_obj->refl = ft_atof(lines[5]);
	vec_norm(&((t_pl *)new_obj->par)->n);
	ft_put(data, new_obj);
}

void	init_cylinder(char **lines, t_data *data, int line)
{
	t_obj	*new_obj;

	if (len_arr(lines) != 8)
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
	new_obj->checker = !ft_strncmp(lines[5], "check", 6);
	if (!new_obj->checker)
		new_obj->color = get_color_check(lines[5], data, line);
	new_obj->spec = ft_atof(lines[6]);
	new_obj->refl = ft_atof(lines[7]);
	vec_norm(&((t_cy *)new_obj->par)->norm);
	ft_put(data, new_obj);
}

void	init_cone(char **lines, t_data *data, int line)
{
	t_obj	*new_obj;

	if (len_arr(lines) != 8)
		error("init cone (parameters)", data, line);
	new_obj = (t_obj *) ft_calloc(1, sizeof(t_obj));
	if (!new_obj)
		error("allocation  mem for cone", data, line);
	new_obj->par = malloc(sizeof(t_co));
	if (!new_obj->par && free_void(new_obj))
		error("allocation  mem for cone", data, line);
	new_obj->key = "co";
	((t_co *)new_obj->par)->pos = get_vector_check(lines[1], 0, data, line);
	((t_co *)new_obj->par)->norm = get_vector_check(lines[2], 1, data, line);
	((t_co *)new_obj->par)->k = tan(ft_atof(lines[3]) * M_PI / 180);
	((t_co *)new_obj->par)->height = ft_atof(lines[4]);
	if (((t_co *)new_obj->par)->height <= 0 && free_void(new_obj->par)
		&& free_void(new_obj))
		error("init cone (parameters)", data, line);
	((t_co *)new_obj->par)->part = 0;
	new_obj->checker = !ft_strncmp(lines[3], "check", 6);
	if (new_obj->checker)
		error("Cone havent checkerboard color distribution :(", data, -1);
	new_obj->color = get_color_check(lines[5], data, line);
	new_obj->spec = ft_atof(lines[6]);
	new_obj->refl = ft_atof(lines[7]);
	vec_norm(&((t_co *)new_obj->par)->norm);
	ft_put(data, new_obj);
}
