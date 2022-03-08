/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_figure.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:11:29 by lcoreen           #+#    #+#             */
/*   Updated: 2022/03/08 16:19:16 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sph	*new_sph(float x, float y, float z, float radius, int color)
{
	t_sph	*ret;

	ret = (t_sph *) malloc(sizeof(t_sph));
	if (!ret)
		return (NULL);
	ret->cntr.x = x;
	ret->cntr.y = y;
	ret->cntr.z = z;
	ret->radius = radius;
	ret->color = color;
	return (ret);
}
