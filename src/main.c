/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 18:11:11 by lcoreen           #+#    #+#             */
/*   Updated: 2022/03/08 17:39:06 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "errors.h"

float	intersect_sphere(t_list *fig, t_vec *ray, float	*t2)
{
	float		k1;
	float		k2;
	float		k3;
	t_sph	*tmp;
	float	descr;

	tmp = (t_sph *) fig->content;
	k1 = vec_scalar_mul(ray, ray);
	k2 = 2 * vec_scalar_mul(ray, &tmp->cntr);
	k3 = vec_scalar_mul(&tmp->cntr, &tmp->cntr) - pow(tmp->radius, 2);
	descr = pow(k2, 2) - 4 * k1 * k3;
	if (descr < 0)
	{
		*t2 = INT32_MAX;
		return (INT32_MAX);
	}
	*t2 = (-k2 - sqrt(descr)) / (2 * k1);
	return ((-k2 + sqrt(descr)) / (2 * k1));
}

int	get_color(t_list *figs, t_vec *ray, float t_min, float t_max)
{
	float	closest;
	t_list	*closest_fig;
	float	t2;
	float	t1;

	(void) t_min;
	(void) t_max;
	closest = INT32_MAX;
	closest_fig = NULL;
	while (figs)
	{
		t1 = intersect_sphere(figs, ray, &t2);
		if (t1 < closest)
		{
			closest = t1;
			closest_fig = figs;
		}
		if (t2 < closest)
		{
			closest = t2;
			closest_fig = figs;
		}
		figs = figs->next;
	}
	if (closest_fig == NULL)
		return (0);
	return (((t_sph *) closest_fig->content)->color);
}

int	ray_trase(t_data *data, int x, int y)
{
	float	sc_x;
	float	sc_y;
	t_vec	*ray;
	int		color;
	
	sc_x = (float) x / data->w;
	sc_y = data->whratio * y / data->h;
	ray = new_vector(sc_x, sc_y, 1);
	color = get_color(data->figs, ray, 1, INT32_MAX);
	free(ray);
	return (color);
}

void	draw(t_data *data)
{
	int	x;
	int	y;
	int	new_x;
	int	new_y;
	int	color;

	y = 0;
	data->img.img = mlx_new_image(data->mlx, data->w, data->h);
	if (!data->img.img)
		error(ERROR_IMG);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
			&data->img.line_length, &data->img.endian);
	while (y < data->h)
	{
		x = 0;
		new_y = data->h / 2 - y;
		while (x < data->w)
		{
			new_x = x - data->w / 2;
			color = ray_trase(data, new_x, new_y);
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

	(void) argv;
	(void) argc;
	data.mlx = mlx_init();
	if (!data.mlx)
		error(ERROR_MLX);
	data.w = 800;
	data.h = 600;
	data.whratio = (float) data.h / data.w;
	data.figs = NULL;
	ft_lstadd_back(&data.figs, ft_lstnew(new_sph(0, -1, 3, 1, pcolor(255, 0, 0))));
	ft_lstadd_back(&data.figs, ft_lstnew(new_sph(2, 0, 4, 1, pcolor(0, 255, 0))));
	ft_lstadd_back(&data.figs, ft_lstnew(new_sph(-2, 0, 4, 1, pcolor(0, 0, 255))));
	data.win = mlx_new_window(data.mlx, data.w, data.h, "miniRT");
	if (!data.win)
		error(ERROR_WIN);
	draw(&data);
	mlx_hook(data.win, 17, 0, close_crest, &data);
	mlx_hook(data.win, 2, 0, key_hook, &data);
	mlx_loop(data.mlx);
	ft_lstclear(&data.figs, free);
	return (0);
}
