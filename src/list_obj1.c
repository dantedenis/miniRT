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

t_color	get_color_check(char *str, t_data *data, int line)
{
	t_color		rgb;
	int			len;
	char		**temp;

	temp = ft_split(str, ',');
	len = len_arr(temp);
	if (len != 3)
		error("color conflict in config", data, line);
	rgb = (t_color){ft_atoi(temp[0]), ft_atoi(temp[1]), ft_atoi(temp[2])};
	free_arr(&temp);
	if (rgb.r > 255 || rgb.g > 255 || rgb.b > 255)
		error("color conflict in config", data, line);
	return (rgb);
}

t_vec	get_vector_check(char *str, int check, t_data *data, int line)
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
	data->cam.pos = get_vector_check(lines[1], 0, data, line);
	data->cam.orient = get_vector_check(lines[2], 1, data, line);
	vec_norm(&data->cam.orient);
	data->cam.fov = ft_atof(lines[3]);
	if (data->cam.fov < 0 || data->cam.fov > 180)
		error("init camera (parameters)", data, line);
	if (fabs(data->cam.orient.y) != 1)
		data->cam.up = new_vector(0, 1, 0);
	else
		data->cam.up = new_vector(1, 0, 0);
	data->cam.right = vec_mul(&data->cam.up, &data->cam.orient);
	data->cam.up = vec_mul(&data->cam.orient, &data->cam.right);
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
		new_obj->pos = get_vector_check(lines[i++], 0, data, line);
	new_obj->ratio = ft_atof(lines[i]);
	new_obj->color = get_color_check(lines[i + 1], data, line);
	new_obj->type = ft_strdup(lines[0]);
	if ((new_obj->ratio < 0 || new_obj->ratio > 1) && free_void(new_obj))
		error("init light", data, line);
	light_add(&data->light, new_obj);
}
