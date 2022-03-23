/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 18:11:11 by lcoreen           #+#    #+#             */
/*   Updated: 2022/03/23 19:48:54 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "errors.h"

void	draw(t_data *data)
{
	int	x;
	int	y;
	int	new_x;
	int	new_y;
	int	color;

	y = 0;
	create_image(data);
	while (y < data->h)
	{
		x = 0;
		new_y = data->h / 2 - y;
		while (x < data->w)
		{
			new_x = x - data->w / 2;
			color = ray_trase(data, &data->cam.pos, new_x, new_y);
			my_mlx_pixel_put(&data->img, x, y, color);
			++x;
		}
		++y;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	mlx_destroy_image(data->mlx, data->img.img);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		error(ERROR_ARGS, NULL, -1);
	ft_bzero(&data, sizeof(t_data));
	data.mlx = mlx_init();
	if (!data.mlx)
		error(ERROR_MLX, NULL, -1);
	data.w = 800;
	data.h = 600;
	data.whratio = (float) data.h / data.w;
	data.win = mlx_new_window(data.mlx, data.w, data.h, "miniRT");
	if (!data.win)
		error(ERROR_WIN, NULL, -1);
	reader_file(argv[1], &data);
	draw(&data);
	mlx_hook(data.win, 17, 0, close_crest, &data);
	mlx_key_hook(data.win, key_hook, &data);
	mlx_loop(data.mlx);
	clear_lst_light(&data.light);
	free_list_obj(&data.obj);
	return (0);
}
