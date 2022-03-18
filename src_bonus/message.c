/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 18:11:24 by lcoreen           #+#    #+#             */
/*   Updated: 2022/03/16 21:45:11 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minirt_bonus.h"
#include "errors.h"

void	help(void)
{
	printf("qqq\n");
}

void	error(char *msg)
{
	printf("%s", msg);
	exit(1);
}
