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

#include "minirt.h"

static int	init_obj(char **strings, t_data *data, int line)
{
	if (!ft_strncmp(strings[0], "A", 2))
		return (init_light(strings, data, line));
	if (!ft_strncmp(strings[0], "C", 2) || !ft_strncmp(strings[0], "c", 2))
		return (init_camera(strings, data, line));
	if (!ft_strncmp(*strings, "L", 2) || !ft_strncmp(*strings, "l", 2))
		return (init_light(strings, data, line));
	if (!ft_strncmp(*strings, "sp", 3))
		return (init_sphere(strings, data, line));
	if (!ft_strncmp(*strings, "pl", 3))
		return (init_plane(strings, data, line));
	if (!ft_strncmp(*strings, "cy", 3))
		return (init_cylinder(strings, data, line));
	return (1);
}

static void	prepare_str(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_isprint(str[i]))
			str[i] = ' ';
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

	fd = open(file, O_RDONLY);
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
