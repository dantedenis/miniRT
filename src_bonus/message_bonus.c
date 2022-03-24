/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 18:11:24 by lcoreen           #+#    #+#             */
/*   Updated: 2022/03/23 17:48:46 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minirt_bonus.h"
#include "errors.h"

void	help(void)
{
	printf("qqq\n");
}

void	error(char *msg, t_data *data, int line)
{
	if (line != -1)
		printf(ERRORS_T, msg, *data->name_cfg, line);
	else
		printf("%s\n", msg);
	close_crest(data);
}

int	free_void(void *data)
{
	free(data);
	return (1);
}

int	len_arr(char **strings)
{
	int	i;

	i = 0;
	while (*strings++)
		++i;
	return (i);
}
