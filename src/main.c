/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 18:11:11 by lcoreen           #+#    #+#             */
/*   Updated: 2022/03/10 17:05:44 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "errors.h"

float	intersect_sphere(t_sph *tmp, t_vec *ray, t_vec *o, float *t2)
{
	float		k1;
	float		k2;
	float		k3;
	float	descr;
	t_vec	*oc;

	oc = vec_sub(o, tmp->cntr);
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

t_sph	*trasing(t_data *data, t_vec *o, float t_min, float t_max)
{
	float	closest;
	t_sph	*closest_sph;
	float	t2;
	float	t1;
	t_sph	*sph;
	
	closest = FLT_MAX;
	closest_sph = NULL;
	sph = data->sph;
	while (sph)
	{
		t1 = intersect_sphere(sph, data->ray, o, &t2);
		if ((t1 > t_min && t1 < t_max) && t1 < closest)
		{
			closest_sph = sph;
			closest_sph->t_close = t1;
		}
		if ((t1 > t_min && t1 < t_max) && t2 < closest)
		{
			closest_sph = sph;
			closest_sph->t_close = t2;
		}
		sph = sph->next;
	}
	return (closest_sph);
}

t_vec	*compute_light(t_data *data, t_light *light, t_vec *P, t_vec *N)
{
	t_vec	*i;
	float	L_dot_N;
	t_sph	*close_sph;
	
	i = new_vector(0, 0, 0);
	while (light)
	{
		if (!ft_strncmp(light->type, "A", 2))
			vec_sum_inplace(i, light->color, light->l_ratio);
		else
		{
			free(data->ray);
			data->ray = vec_sub(light->pos, P);
			close_sph = trasing(data, P, 0.001, 1);
			if (close_sph)
			{
				light = light->next;
				continue ;
			}
			L_dot_N = vec_scalar_mul(data->ray, N);
			if (L_dot_N > 0)
				vec_sum_inplace(i, light->color, light->l_ratio * L_dot_N / vec_len(data->ray));
		}
		light = light->next;
	}
	return (i);
}

int	get_color(t_data *data, t_vec *o)
{
	t_vec	*P;
	t_vec	*N;
	t_vec	*closest_ray;
	t_sph	*closest_sph;
	int		color;

	closest_sph = trasing(data, o, 1, FLT_MAX);
	if (closest_sph == NULL)
		return (0);
	closest_ray = vec_mul_nbr(data->ray, closest_sph->t_close);
	P = vec_sum(closest_ray, o);
	N = vec_sub(P, closest_sph->cntr);
	vec_norm(N);
	free(closest_ray);
	closest_ray = compute_light(data, data->light, P, N);
	free(P);
	free(N);
	color = mul_pcolor(closest_sph->color, closest_ray);
	free(closest_ray);
	return (color);
}

int	ray_trase(t_data *data, t_vec *o, int x, int y)
{
	float	sc_x;
	float	sc_y;
	int		color;
	
	(void) o;
	sc_x = (float) x / data->w;
	sc_y = data->whratio * y / data->h;
	data->ray = new_vector(sc_x, sc_y, 1);
	color = get_color(data, o);
	free(data->ray);
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
	data.sph = NULL;
	sph_add(&data.sph, new_sph(new_vector(0, -1, 3), 1, new_color(255, 0, 0)));
	sph_add(&data.sph, new_sph(new_vector(-2, 0, 4), 1, new_color(0, 255, 0)));
	sph_add(&data.sph, new_sph(new_vector(2, 0, 4), 1, new_color(0, 0, 255)));
	sph_add(&data.sph, new_sph(new_vector(0, -5001, 0), 5000, new_color(255, 255, 0)));
	data.light = NULL;
	light_add(&data.light, new_light("A", NULL, 0.2, new_color(0, 255, 255)));
	light_add(&data.light, new_light("P", new_vector(2, 1, 0), 0.6, new_color(255, 255, 255)));
	light_add(&data.light, new_light("P", new_vector(-2, 1, 3), 0.5, new_color(255, 255, 255)));
	data.win = mlx_new_window(data.mlx, data.w, data.h, "miniRT");
	if (!data.win)
		error(ERROR_WIN);
	draw(&data);
	mlx_hook(data.win, 17, 0, close_crest, &data);
	mlx_key_hook(data.win, key_hook, &data);
	mlx_loop(data.mlx);
	clear_lst_light(&data.light);
	clear_lst_sph(&data.sph);
	return (0);
}
