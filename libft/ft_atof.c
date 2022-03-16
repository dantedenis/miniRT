/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 19:52:38 by bstrong           #+#    #+#             */
/*   Updated: 2022/03/16 19:52:38 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"

float	ft_atof(const char *str)
{
	float	int_part;
	float	dec_part;
	float	sign;
	int		i;

	int_part = 0.0;
	dec_part = 0.0;
	sign = 1.0;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = -1.0;
	while (ft_isdigit(*str))
		int_part = int_part * 10 + (*str++ - '0');
	i = -1;
	if (*str == '.' && *str++)
		while (ft_isdigit(*str))
			dec_part += (pow(10, i--) * (*str++ - '0'));
	return (sign * (int_part + dec_part));
}
