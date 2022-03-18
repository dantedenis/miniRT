/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 18:09:38 by lcoreen           #+#    #+#             */
/*   Updated: 2022/03/18 15:51:25 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	pcolor(t_color *color)
{
	return (color->b + color->g * 256 + color->r * 256 * 256);
}

t_color	new_color(int r, int g, int b)
{
	t_color	ret;

	ret.r = r;
	ret.g = g;
	ret.b = b;
	return (ret);
}

t_color	color_mul_vec(t_color *color, t_vec *t)
{
	int	r;
	int	g;
	int	b;

	r = color->r * t->x;
	g = color->g * t->y;
	b = color->b * t->z;
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return (new_color(r, g, b));
}

t_color	color_sum(t_color *a, t_color *c)
{
	int	r;
	int	g;
	int	b;

	r = a->r + c->r;
	g = a->g + c->g;
	b = a->b + c->b;
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return (new_color(r, g, b));
}

void	color_mul_nbr(t_color *color, float t)
{
	color->b *= t;
	color->g *= t;
	color->r *= t;
}
