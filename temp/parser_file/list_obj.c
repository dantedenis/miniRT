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
	free(temp); //////------>TODO: frea array;
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
	free(str); //////------>TODO: frea array;
	return (result);
}

int	init_ambient(char **lines, t_data *data)
{
	t_obj	*new_obj;
	float	ratio;
	t_color		color;

	new_obj = (t_obj *)malloc(sizeof(t_obj));
	if (!new_obj)
		return (1);
	new_obj->key = ft_strdup(lines[0]);
	ratio = ft_atof(lines[1]);
	color = get_color(lines[2]);
	new_obj->par = malloc(sizeof(t_ambi));
	ft_memcpy(new_obj->par, &((t_ambi){ratio, color}), sizeof(t_ambi));
	//printf("%s %f %d,%d,%d\n", new_obj->key,((t_ambi *)new_obj->par)->ratio, ((t_ambi *)new_obj->par)->color.x, ((t_ambi *)new_obj->par)->color.y, ((t_ambi *)new_obj->par)->color.z);
	ft_put(data, new_obj);
	free(lines); ///////----->TODO: frea array;
	return (0);
}

int	init_camera(char **lines, t_data *data)
{
	t_obj	*new_obj;
	t_vec	pos;
	t_vec	norm;
	float	fov;

	new_obj = (t_obj *) malloc(sizeof(t_obj));
	if (!new_obj)
		return (1);
	new_obj->par = malloc(sizeof(t_cam));
	if (!new_obj->par) //TODO: clear allocation upper
		return (1);
	new_obj->key = ft_strdup(lines[0]);
	pos = get_vector(lines[1]);
	norm = get_vector(lines[2]);
	fov = ft_atof(lines[3]);
	ft_memcpy(new_obj->par, &((t_cam){pos, norm, fov}), sizeof(t_cam));
	ft_put(data, new_obj);
	free(lines); ///////----->TODO: frea array;
	return (0);
}

/*
int	init_light(char **lines, t_data *data)
{
	return (0);
}
*/

int	init_sphere(char **lines, t_data *data)
{
	t_obj	*new_obj;
	t_vec	pos;
	float	diameter;
	t_color	color;

	new_obj = (t_obj *) malloc(sizeof(t_obj));
	if (!new_obj)
		return (1);
	new_obj->par = malloc(sizeof(t_sph));
	if (!new_obj->par) //TODO: clear allocation upper
		return (1);
	new_obj->key = ft_strdup(lines[0]);
	pos = get_vector(lines[1]);
	diameter = ft_atof(lines[2]);
	color = get_color(lines[3]);
	ft_memcpy(new_obj->par, &((t_sph){pos, diameter / 2, color}), sizeof(t_sph));
	ft_put(data, new_obj);
	//printf("%s %f %f %f %f %d,%d,%d\n", new_obj->key,((t_sph *)new_obj->par)->cntr.x, ((t_sph *)new_obj->par)->cntr.y, ((t_sph *)new_obj->par)->cntr.z, ((t_sph *)new_obj->par)->radius, ((t_sph *)new_obj->par)->color.x, ((t_sph *)new_obj->par)->color.y, ((t_sph *)new_obj->par)->color.z);
	free(lines); ///////----->TODO: frea array;
	return (0);
}

int	init_plane(char **lines, t_data *data)
{
	t_obj	*new_obj;
	t_vec	pos;
	t_vec	norm;
	t_color	color;

	new_obj = (t_obj *) malloc(sizeof(t_obj));
	if (!new_obj)
		return (1);
	new_obj->par = malloc(sizeof(t_pl));
	if (!new_obj->par) //TODO: clear allocation upper
		return (1);
	new_obj->key = ft_strdup(lines[0]);
	pos = get_vector(lines[1]);
	norm = get_vector(lines[2]);
	color = get_color(lines[3]);
	ft_memcpy(new_obj->par, &((t_pl){pos, norm, color}), sizeof(t_pl));
	ft_put(data, new_obj);
	//printf("%s %f %f %f %f %d,%d,%d\n", new_obj->key,((t_sph *)new_obj->par)->cntr.x, ((t_sph *)new_obj->par)->cntr.y, ((t_sph *)new_obj->par)->cntr.z, ((t_sph *)new_obj->par)->radius, ((t_sph *)new_obj->par)->color.x, ((t_sph *)new_obj->par)->color.y, ((t_sph *)new_obj->par)->color.z);
	free(lines); ///////----->TODO: frea array;
	return (0);
}

int	init_cylinder(char **lines, t_data *data)
{
	t_obj	*new_obj;
	t_vec	pos;
	t_vec	norm;
	t_color	color;

	new_obj = (t_obj *) malloc(sizeof(t_obj));
	if (!new_obj)
		return (1);
	new_obj->par = malloc(sizeof(t_cy));
	if (!new_obj->par) //TODO: clear allocation upper
		return (1);
	new_obj->key = ft_strdup(lines[0]);
	pos = get_vector(lines[1]);
	norm = get_vector(lines[2]);
	color = get_color(lines[5]);
	ft_memcpy(new_obj->par, &((t_cy){pos, norm, ft_atof(lines[3]), ft_atof(lines[4]), color}), sizeof(t_cy));
	ft_put(data, new_obj);
	//printf("%s %f %f %f %f %d,%d,%d\n", new_obj->key,((t_sph *)new_obj->par)->cntr.x, ((t_sph *)new_obj->par)->cntr.y, ((t_sph *)new_obj->par)->cntr.z, ((t_sph *)new_obj->par)->radius, ((t_sph *)new_obj->par)->color.x, ((t_sph *)new_obj->par)->color.y, ((t_sph *)new_obj->par)->color.z);
	free(lines); ///////----->TODO: frea array;
	return (0);
}