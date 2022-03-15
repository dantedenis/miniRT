/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 18:11:11 by lcoreen           #+#    #+#             */
/*   Updated: 2022/03/15 17:03:58 by lcoreen          ###   ########.fr       */
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

	(void) argc;
	ft_bzero(&data, sizeof(t_data));
	data.mlx = mlx_init();
	if (!data.mlx)
		error(ERROR_MLX);
	data.w = 800;
	data.h = 600;
	data.whratio = (float) data.h / data.w;
	reader_file(argv[1], &data);
	data.win = mlx_new_window(data.mlx, data.w, data.h, "miniRT");
	if (!data.win)
		error(ERROR_WIN);
	draw(&data);
	mlx_hook(data.win, 17, 0, close_crest, &data);
	mlx_key_hook(data.win, key_hook, &data);
	mlx_loop(data.mlx);
	clear_lst_light(&data.light);
	free_list_obj(&data.obj);
	return (0);
}
// CHANGES: Поменял структуры сферы и плоскости, все общие поля вынес в obj (color, параметр t)
	// 			В структурах остаются только их геометрические параметры
	//			Лист объектов хранит только объекты фигур и их параметры
	//			Лист света (data.light) хранит свет в виде одного типа t_light (для определения типа света используется data.light->type)
	//			Камера в структуре расположена тоже отдельным полем (data.cam)
	//			Изменения в структуре data немного коснулись функций list_obj.c (не сильно :))
	// TODO (from subject):
	// 	• Your program must be able to resize the object’s unique properties: diameter for a
	// sphere and the width and height for a cylinder.
	// • Your program must be able to apply translation and rotation transformation to
	// objects, lights and cameras (except for spheres and lights that cannot be rotated).
	// TODO: Реализовать вращение и перемещение по остальным осям (приорирет пока низкий)
	// TODO: Реализовать зеркальное отражение (бонус)
