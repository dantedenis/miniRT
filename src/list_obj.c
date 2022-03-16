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

#include "minirt.h"
#include <unistd.h>

static void	check_dupl(t_data *data, char ch)
{
	t_obj	*temp;

	temp = data->obj;
	while (temp)
	{
		if (*temp->key == ch)
			error("duplicate in *.rt", data, -1);
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
	char		**temp;

	temp = ft_split(str, ',');
	rgb = (t_color){ft_atoi(temp[0]), ft_atoi(temp[1]), ft_atoi(temp[2])};
	free_arr(&temp);
	if (rgb.r > 255 || rgb.g > 255 || rgb.b > 255)
		error("error color in config *.rt", data, line);
	return (rgb);
}

static t_vec	get_vector(char *str, int check, t_data *data, int line)
{
	t_vec	result;
	char	**temp;

	temp = ft_split(str, ',');
	result = (t_vec){
		ft_atof(temp[0]),
		ft_atof(temp[1]),
		ft_atof(temp[2]),
	};
	free_arr(&temp);
	if (check && (result.x < -1 || result.x > 1 || result.y < -1
		|| result.y > 1 || result.z < -1 || result.z > 1))
		error("error init normilaze vector", data, line);
	return (result);
}

int	init_camera(char **lines, t_data *data, int line)
{
	t_vec	pos;
	t_vec	norm;
	float	fov;
	t_vec	up;
	t_vec	right;

	pos = get_vector(lines[1], 0, data, line);
	norm = get_vector(lines[2], 1, data, line);
	vec_norm(&norm);
	fov = ft_atof(lines[3]);
	if (norm.y != 1)
		up = new_vector(0, 1, 0);
	else
		up = new_vector(1, 0, 0);
	right = vec_mul(&up, &norm);
	up = vec_mul(&norm, &right);
	ft_memcpy(&data->cam, &((t_cam){pos, norm, fov, up, right}), sizeof(t_cam));
	return (0);
}

int	init_light(char **lines, t_data *data, int line)
{
	t_light	*new_obj;
	t_vec	pos;
	t_color	color;
	float	ratio;
	int		i;

	i = 1;
	ft_bzero(&pos, sizeof(t_vec));
	new_obj = (t_light *) ft_calloc(1, sizeof(t_light));
	if (!new_obj)
		return (1);
	if (!ft_strncmp(lines[0], "L", 2))
		pos = get_vector(lines[i++], 0, data, line);
	ratio = ft_atof(lines[i]);
	color = get_color(lines[i + 1], data, line);
	if (ratio < 0 || ratio > 1)
		error("eror init light", data, line);
	ft_memcpy(new_obj, &((t_light){0, pos, ratio, color, 0}), sizeof(t_light));
	new_obj->type = ft_strdup(lines[0]);
	light_add(&data->light, new_obj);
	return (0);
}

int	init_sphere(char **lines, t_data *data, int line)
{
	t_obj	*new_obj;
	t_vec	pos;
	float	diameter;
	t_color	color;

	new_obj = (t_obj *) ft_calloc(1, sizeof(t_obj));
	if (!new_obj)
		return (1);
	new_obj->par = malloc(sizeof(t_sph));
	if (!new_obj->par)
	{
		free(new_obj);
		return (1);
	}
	new_obj->key = ft_strdup(lines[0]);
	new_obj->next = NULL;
	pos = get_vector(lines[1], 0, data, line);
	diameter = ft_atof(lines[2]);
	color = get_color(lines[3], data, line);
	if (diameter <= 0)
		error("error inir sphere", data, line);
	ft_memcpy(new_obj->par, &((t_sph){pos, diameter / 2}), sizeof(t_sph));
	ft_memcpy(&new_obj->color, &color, sizeof(t_color));
	ft_put(data, new_obj);
	return (0);
}

int	init_plane(char **lines, t_data *data, int line)
{
	t_obj	*new_obj;
	//float	d;
	t_vec	coord;
	t_vec	norm;
	t_color	color;

	new_obj = (t_obj *) ft_calloc(1, sizeof(t_obj));
	if (!new_obj)
		return (1);
	new_obj->par = malloc(sizeof(t_pl));
	if (!new_obj->par)
	{
		free(new_obj);
		return (1);
	}
	new_obj->key = ft_strdup(lines[0]);
	new_obj->next = NULL;
	coord = get_vector(lines[1], 0, data, line);
	norm = get_vector(lines[2], 1, data, line);
	vec_norm(&norm);
	color = get_color(lines[3], data, line);
	ft_memcpy(new_obj->par, &((t_pl){norm, coord}), sizeof(t_pl));
	ft_memcpy(&new_obj->color, &color, sizeof(t_color));
	ft_put(data, new_obj);
	return (0);
}

int	init_cylinder(char **lines, t_data *data, int line)
{
	t_obj	*new_obj;
	t_vec	pos;
	t_vec	norm;
	t_color	color;

	new_obj = (t_obj *) ft_calloc(1, sizeof(t_obj));
	if (!new_obj)
		return (1);
	new_obj->par = malloc(sizeof(t_cy));
	if (!new_obj->par)
	{
		free(new_obj);
		return (1);
	}
	new_obj->key = ft_strdup(lines[0]);
	new_obj->next = NULL;
	pos = get_vector(lines[1], 0, data, line);
	norm = get_vector(lines[2], 1, data, line);
	vec_norm(&norm);
	color = get_color(lines[5], data, line);
	ft_memcpy(new_obj->par, &((t_cy){pos, norm, ft_atof(lines[3]),
			ft_atof(lines[4]), 0}), sizeof(t_cy));
	ft_memcpy(&new_obj->color, &color, sizeof(t_color));
	ft_put(data, new_obj);
	return (0);
}
