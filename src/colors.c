/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 18:09:38 by lcoreen           #+#    #+#             */
/*   Updated: 2022/03/09 09:30:58 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	pcolor(int r, int g, int b)
{
	return (b + g * 256 + r * 256 * 256);
}

int	mul_pcolor(int r, int g, int b, float i)
{
	r = i * r;
	b = i * r;
	g = i * r;

	if (r > 255)
		r = 255;
	if (b > 255)
		b = 255;
	if (g > 255)
		g = 255;
	return (pcolor(r, g, b));
}
