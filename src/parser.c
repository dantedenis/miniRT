#include "minirt.h"

static int init_obj(char **lines, t_data *data)
{
	if (!ft_strncmp(lines[0], "A", 2) || !ft_strncmp(lines[0], "a", 2))
		return (init_light(lines, data));
	if (!ft_strncmp(lines[0], "C", 2) || !ft_strncmp(lines[0], "c", 2))
		return (init_camera(lines, data));
	if (!ft_strncmp(*lines, "L", 2) || !ft_strncmp(*lines, "l", 2))
		return (init_light(lines, data));
	if (!ft_strncmp(*lines, "SP", 3) || !ft_strncmp(*lines, "sp", 3))
		return (init_sphere(lines, data));
	if (!ft_strncmp(*lines, "PL", 3) || !ft_strncmp(*lines, "pl", 3))
		return (init_plane(lines, data));
	// if (!ft_strncmp(*lines, "CY", 3) || !ft_strncmp(*lines, "cy", 3))
	// 	return (init_cylinder(lines, data));
	return (1);
}

int	parser(char *str, t_data *data)
{
	char **lines = ft_split(str, ' ');
	init_obj(lines, data);
	free_arr(&lines);
	return (0);
}
