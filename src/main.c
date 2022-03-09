/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 18:11:11 by lcoreen           #+#    #+#             */
/*   Updated: 2022/03/09 09:31:25 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "errors.h"

float	compute_light(t_light *light, t_vec *P, t_vec *N)
{
	float	i;
	t_vec	*L;
	float	L_dot_N;
	
	i = 0;
	while (light)
	{
		if (!ft_strncmp(light->type, "A", 2))
			i += light->l_ratio;
		else
		{
			L = vec_sub(light->pos, P);
			L_dot_N = vec_scalar_mul(L, N);
			if (L_dot_N > 0)
				i += light->l_ratio * L_dot_N / vec_len(L);
			free(L);
		}
		light = light->next;
	}
	return (i);
}

float	intersect_sphere(t_sph *tmp, t_vec *ray, t_vec	*o, float *t2)
{
	float		k1;
	float		k2;
	float		k3;
	float	descr;
	t_vec	*oc;

	oc = vec_sub(o, &tmp->cntr);
	k1 = vec_scalar_mul(ray, ray);
	k2 = 2 * vec_scalar_mul(ray, oc);
	k3 = vec_scalar_mul(oc, oc) - pow(tmp->radius, 2);
	descr = pow(k2, 2) - 4 * k1 * k3;
	free(oc);
	if (descr < 0)
	{
		*t2 = FLT_MAX;
		return (FLT_MAX);
	}
	*t2 = (-k2 - sqrt(descr)) / (2 * k1);
	return ((-k2 + sqrt(descr)) / (2 * k1));
}

int	get_color(t_data *data, t_vec *ray, t_vec *o, float t_min)
{
	float	closest;
	t_list	*closest_fig;
	float	t2;
	float	t1;
	t_list	*figs;
	t_vec	*P;
	t_vec	*N;
	t_vec	*closest_ray;

	closest = FLT_MAX;
	closest_fig = NULL;
	figs = data->figs;
	while (figs)
	{
		t1 = intersect_sphere((t_sph *) figs->content, ray, o, &t2);
		if ((t1 > t_min && t1 < FLT_MAX) && t1 < closest)
		{
			closest = t1;
			closest_fig = figs;
		}
		if ((t1 > t_min && t1 < FLT_MAX) && t2 < closest)
		{
			closest = t2;
			closest_fig = figs;
		}
		figs = figs->next;
	}
	if (closest_fig == NULL)
		return (0);
	closest_ray = vec_mul_nbr(ray, closest);
	P = vec_sum(closest_ray, o);
	N = vec_sub(P, &((t_sph *) closest_fig->content)->cntr);
	vec_norm(N);
	float	i = 1;
	i = compute_light(data->light, P, N);
	free(closest_ray);
	free(P);
	free(N);
	return (((t_sph *) closest_fig->content)->color * i);
	return (mul_pcolor())
}

int	ray_trase(t_data *data, t_vec *o, int x, int y)
{
	float	sc_x;
	float	sc_y;
	t_vec	*ray;
	int		color;
	
	(void) o;
	sc_x = (float) x / data->w;
	sc_y = data->whratio * y / data->h;
	ray = new_vector(sc_x, sc_y, 1);
	color = get_color(data, ray, o, 1);
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
	t_vec	*o;

	y = 0;
	data->img.img = mlx_new_image(data->mlx, data->w, data->h);
	if (!data->img.img)
		error(ERROR_IMG);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
			&data->img.line_length, &data->img.endian);
	o = new_vector(0, 0, 0);
	while (y < data->h)
	{
		x = 0;
		new_y = data->h / 2 - y;
		while (x < data->w)
		{
			new_x = x - data->w / 2;
			color = ray_trase(data, o, new_x, new_y);
			my_mlx_pixel_put(&data->img, x, y, color);
			++x;
		}
		++y;
	}
	free(o);
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
	data.light = NULL;
	light_add(&data.light, new_light(ft_strdup("A"), NULL, 0.2, 0));
	light_add(&data.light, new_light(ft_strdup("P"), new_vector(2, 1, 0), 0.6, 0));
	data.win = mlx_new_window(data.mlx, data.w, data.h, "miniRT");
	if (!data.win)
		error(ERROR_WIN);
	draw(&data);
	mlx_hook(data.win, 17, 0, close_crest, &data);
	mlx_key_hook(data.win, key_hook, &data);
	mlx_loop(data.mlx);
	ft_lstclear(&data.figs, free);
	clear_lst_light(&data.light);
	return (0);
}
