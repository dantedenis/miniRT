#include "minirt.h"

static int init_obj(char **lines, t_data *data)
{
	if (!ft_strncmp(lines[0], "A", 2) || !ft_strncmp(lines[0], "a", 2))
		return (init_ambient(lines, data));
	if (!ft_strncmp(lines[0], "C", 2) || !ft_strncmp(lines[0], "c", 2))
		return (init_camera(lines, data));
	/*if (!ft_strncmp(*lines, "L", 2) || !ft_strncmp(*lines, "l", 2))
		return (init_light(lines, data));*/
	if (!ft_strncmp(*lines, "SP", 3) || !ft_strncmp(*lines, "sp", 3))
		return (init_sphere(lines, data));
	if (!ft_strncmp(*lines, "PL", 3) || !ft_strncmp(*lines, "pl", 3))
		return (init_plane(lines, data));
	if (!ft_strncmp(*lines, "CY", 3) || !ft_strncmp(*lines, "cy", 3))
		return (init_cylinder(lines, data));
	return (1);
}

static int	parser(char *str, t_data *data)
{
	char **lines = ft_split(str, ' ');
	init_obj(lines, data);
	return 0;
}

int main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	t_data data;
	ft_bzero(&data, sizeof(t_data));
	//char *str[2] = {"C -50.0,0,20 0,0,1 70", "A 0.2 255,255,255"};
	parser("C -50.0,0,20 0,0,1 70", &data);
	parser("A 0.2 255,255,255", &data);
	parser("sp 0.0,0.0,20.6  12.6 10,0,255", &data);
	parser("pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,255", &data);
	parser("cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255", &data);
/*
	t_ambi *ambi = (t_ambi *)data.obj->par;
	t_obj	*temp = data.obj;
	int i = 0;
	while(i < 2)
	{
		++i;
		parser(str[i], &data);
	}*/
	return (0);
}