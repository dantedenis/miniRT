/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:10:52 by lcoreen           #+#    #+#             */
/*   Updated: 2022/03/15 16:10:52 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"
#include <unistd.h>

static int	free_void(void *data)
{
	free(data);
	return (1);
}

static int	len_arr(char **strings)
{
	int	i;

	i = 0;
	while (*strings++)
		++i;
	return (i);
}

static void	check_dupl(t_data *data, char ch)
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

static t_color	get_color(char *str, t_data *data, int line)
{
	t_color		rgb;
	int			len;
	char		**temp;

	temp = ft_split(str, ',');
	rgb = (t_color){ft_atoi(temp[0]), ft_atoi(temp[1]), ft_atoi(temp[2])};
	len = len_arr(temp);
	free_arr(&temp);
	if (rgb.r > 255 || rgb.g > 255 || rgb.b > 255 || len != 3)
		error("color conflict in config", data, line);
	return (rgb);
}

static t_vec	get_vector(char *str, int check, t_data *data, int line)
{
	t_vec	result;
	int		len;
	char	**temp;

	temp = ft_split(str, ',');
	len = len_arr(temp);
	if (len != 3)
		error("init vector (parameters)", data, line);
	result = (t_vec){ft_atof(temp[0]), ft_atof(temp[1]), ft_atof(temp[2])};
	free_arr(&temp);
	if (check && (result.x < -1 || result.x > 1 || result.y < -1
		|| result.y > 1 || result.z < -1 || result.z > 1))
		error("init vector", data, line);
	return (result);
}

void	init_camera(char **lines, t_data *data, int line)
{
	if (len_arr(lines) != 4)
		error("init camera (parameters)", data, line);
	data->cam.pos = get_vector(lines[1], 0, data, line);
	data->cam.orient = get_vector(lines[2], 1, data, line);
	vec_norm(&data->cam.orient);
	data->cam.fov = ft_atof(lines[3]);
	if (data->cam.orient.y != 1)
		data->cam.up = new_vector(0, 1, 0);
	else
		data->cam.up = new_vector(1, 0, 0);
	data->cam.right = vec_mul(&data->cam.up, &data->cam.orient);
	data->cam.up = vec_mul(&data->cam.orient, &data->cam.right);
	data->cam.alpha = 0.0;
	data->cam.betta = 0.0;
	data->cam.gamma = 0.0;
}

void	init_light(char **lines, t_data *data, int line)
{
	t_light	*new_obj;
	int		i;

	if (!(len_arr(lines) == 3 || len_arr(lines) == 4))
		error("init light (parameters)", data, line);
	i = 1;
	new_obj = (t_light *) ft_calloc(1, sizeof(t_light));
	if (!new_obj)
		error("allocation mem for light (parameters)", data, line);
	if (!ft_strncmp(lines[0], "l", 2) || !ft_strncmp(lines[0], "L", 2))
		new_obj->pos = get_vector(lines[i++], 0, data, line);
	new_obj->ratio = ft_atof(lines[i]);
	new_obj->color = get_color(lines[i + 1], data, line);
	new_obj->type = ft_strdup(lines[0]);
	if ((new_obj->ratio < 0 || new_obj->ratio > 1) && free_void(new_obj))
		error("init light", data, line);
	light_add(&data->light, new_obj);
}

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
	((t_sph*)new_obj->par)->cntr = get_vector(lines[1], 0, data, line);
	((t_sph*)new_obj->par)->radius = ft_atof(lines[2]) / 2.;
	new_obj->color = get_color(lines[3], data, line);
	if (((t_sph*)new_obj->par)->radius <= 0 && free_void(new_obj->par)
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
	((t_pl*)new_obj->par)->c = get_vector(lines[1], 0, data, line);
	((t_pl*)new_obj->par)->n = get_vector(lines[2], 1, data, line);
	new_obj->color = get_color(lines[3], data, line);
	new_obj->spec = ft_atof(lines[4]);
	new_obj->refl = ft_atof(lines[5]);
	vec_norm(&((t_pl*)new_obj->par)->n);
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
	((t_cy*)new_obj->par)->pos = get_vector(lines[1], 0, data, line);
	((t_cy*)new_obj->par)->norm = get_vector(lines[2], 1, data, line);
	((t_cy*)new_obj->par)->diameter = ft_atof(lines[3]);
	((t_cy*)new_obj->par)->height = ft_atof(lines[4]);
	if ((((t_cy*)new_obj->par)->diameter <= 0
			|| ((t_cy*)new_obj->par)->height <= 0)
			&& free_void(new_obj->par) && free_void(new_obj))
		error("init cylinder (parameters)", data, line);
	((t_cy*)new_obj->par)->part = 0;
	new_obj->color = get_color(lines[5], data, line);
	new_obj->spec = ft_atof(lines[6]);
	new_obj->refl = ft_atof(lines[7]);
	vec_norm(&((t_cy*)new_obj->par)->norm);
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
	((t_co*)new_obj->par)->pos = get_vector(lines[1], 0, data, line);
	((t_co*)new_obj->par)->norm = get_vector(lines[2], 1, data, line);
	((t_co*)new_obj->par)->k = tan(ft_atof(lines[3]) * M_PI / 180);
	((t_co*)new_obj->par)->height = ft_atof(lines[4]);
	if (((t_co*)new_obj->par)->height <= 0 && free_void(new_obj->par)
			&& free_void(new_obj))
		error("init cone (parameters)", data, line);
	((t_co*)new_obj->par)->part = 0;	
	new_obj->color = get_color(lines[5], data, line);
	new_obj->spec = ft_atof(lines[6]);
	new_obj->refl = ft_atof(lines[7]);
	vec_norm(&((t_co*)new_obj->par)->norm);
	ft_put(data, new_obj);
}

