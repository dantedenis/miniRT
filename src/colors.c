/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 18:09:38 by lcoreen           #+#    #+#             */
/*   Updated: 2022/03/10 17:06:25 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	pcolor_from_struct(t_color *color)
{
	return (color->b + color->g * 256 + color->r * 256 * 256);
}

int	pcolor(int r, int g, int b)
{
	return (b + g * 256 + r * 256 * 256);
}

t_color	*new_color(int r, int g, int b)
{
	t_color	*ret;

	ret = (t_color *) malloc(sizeof(t_color));
	if (!ret)
		return (NULL);
	ret->r = r;
	ret->g = g;
	ret->b = b;
	return (ret);
}

int	mul_pcolor(t_color *color, t_vec *t)
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
	return (pcolor(r, g, b));
}
