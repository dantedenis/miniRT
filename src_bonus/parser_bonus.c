/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:13:18 by lcoreen           #+#    #+#             */
/*   Updated: 2022/03/15 16:13:18 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static int	init_obj(char **lines, t_data *data, int line)
{
	if (!ft_strncmp(*lines, "A", 2))
		init_light(lines, data, line);
	else if (!ft_strncmp(*lines, "C", 2) || !ft_strncmp(*lines, "c", 2))
		init_camera(lines, data, line);
	else if (!ft_strncmp(*lines, "L", 2) || !ft_strncmp(*lines, "l", 2))
		init_light(lines, data, line);
	else if (!ft_strncmp(*lines, "sp", 3))
		init_sphere(lines, data, line);
	else if (!ft_strncmp(*lines, "pl", 3))
		init_plane(lines, data, line);
	else if (!ft_strncmp(*lines, "cy", 3))
		init_cylinder(lines, data, line);
	else if (!ft_strncmp(*lines, "co", 3))
		init_cone(lines, data, line);
	else
		printf("Warning: object is not\
		 supoprted, [%s] in line -> %d", *data->name_cfg, line);
	return (0);
}

static void	prepare_str(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_isprint(str[i]))
			str[i] = ' ';
}

static int	check_format_file(char *file)
{
	int	len;

	len = ft_strlen(file) - 3;
	if (len < 0 || ft_strncmp(file + len, ".rt", 4))
		return (1);
	return (0);
}

static int	parser(char *str, t_data *data, int line)
{
	int		result;
	char	**strings;

	prepare_str(str);
	strings = ft_split(str, ' ');
	result = init_obj(strings, data, line);
	free_arr(&strings);
	return (result);
}

int	reader_file(char *file, t_data *data)
{
	int		fd;
	char	*temp;
	int		line;

	if (check_format_file(file))
		error("format file is not supported", data, -1);
	fd = open(file, O_RDONLY);
	data->name_cfg = &file;
	if (fd > 0 && data)
	{
		line = 0;
		while (1)
		{
			++line;
			temp = get_next_line(fd);
			if (!temp)
				break ;
			parser(temp, data, line);
			free(temp);
		}
		return (close(fd));
	}
	return (1);
}
