#include "minirt.h"
#include <unistd.h>

void	ft_put(t_data *data, t_obj *obj)
{
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

static t_color	get_color(char *line)
{
	t_color		rgb;
	char	**temp;

	temp = ft_split(line, ',');
	rgb = (t_color){ft_atoi(temp[0]), ft_atoi(temp[1]), ft_atoi(temp[2])};
	free_arr(&temp);
	return (rgb);
}

static t_vec	get_vector(char *line)
{
	t_vec	result;
	char	**str;

	str = ft_split(line, ',');
	result = (t_vec){
		ft_atof(str[0]),
		ft_atof(str[1]),
		ft_atof(str[2]),
	};
	free_arr(&str);
	return (result);
}

int	init_camera(char **lines, t_data *data)
{
	t_vec	pos;
	t_vec	norm;
	float	fov;

	pos = get_vector(lines[1]);
	norm = get_vector(lines[2]);
	fov = ft_atof(lines[3]);
	ft_memcpy(&data->cam, &((t_cam){pos, norm, fov}), sizeof(t_cam));
	return (0);
}


int	init_light(char **lines, t_data *data)
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
		pos = get_vector(lines[i++]);
	ratio = ft_atof(lines[i]);
	color = get_color(lines[i + 1]);
	ft_memcpy(new_obj, &((t_light){0, pos, ratio, color, 0}), sizeof(t_light));
	new_obj->type = ft_strdup(lines[0]);
	light_add(&data->light, new_obj);
	return (0);
}

int	init_sphere(char **lines, t_data *data)
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
	pos = get_vector(lines[1]);
	diameter = ft_atof(lines[2]);
	color = get_color(lines[3]);
	ft_memcpy(new_obj->par, &((t_sph){pos, diameter / 2}), sizeof(t_sph));
	ft_memcpy(&new_obj->color, &color, sizeof(t_color));
	ft_put(data, new_obj);
	return (0);
}

int	init_plane(char **lines, t_data *data)
{
	t_obj	*new_obj;
	float	d;
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
	coord = get_vector(lines[1]);
	norm = get_vector(lines[2]);
	vec_norm(&norm);
	color = get_color(lines[3]);
	ft_memcpy(new_obj->par, &((t_pl){norm, coord}), sizeof(t_pl));
	ft_memcpy(&new_obj->color, &color, sizeof(t_color));
	ft_put(data, new_obj);
	//printf("%s %f %f %f %f %d,%d,%d\n", new_obj->key,((t_sph *)new_obj->par)->cntr.x, ((t_sph *)new_obj->par)->cntr.y, ((t_sph *)new_obj->par)->cntr.z, ((t_sph *)new_obj->par)->radius, ((t_sph *)new_obj->par)->color.x, ((t_sph *)new_obj->par)->color.y, ((t_sph *)new_obj->par)->color.z);
	return (0);
}

int	init_cylinder(char **lines, t_data *data)
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
	pos = get_vector(lines[1]);
	norm = get_vector(lines[2]);
	vec_norm(&norm);
	color = get_color(lines[5]);
	ft_memcpy(new_obj->par, &((t_cy){pos, norm, ft_atof(lines[3]), ft_atof(lines[4]), 0}), sizeof(t_cy));
	ft_memcpy(&new_obj->color, &color, sizeof(t_color));
	ft_put(data, new_obj);
	return (0);
}
