/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 18:14:36 by lcoreen           #+#    #+#             */
/*   Updated: 2022/03/08 17:02:25 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include <math.h>
# include <stdio.h>

# include "mlx.h"
# include "libft.h"

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_vec
{
	float	x;
	float	y;
	float	z;
}	t_vec;

typedef struct s_cam
{
	t_vec	pos;
	t_vec	orient;
	float	fov;
}	t_cam;

typedef struct s_alight
{
	float	l_ratio;
	int		color;
}	t_alight;

typedef struct s_light
{
	t_vec	pos;
	float	l_ratio;
	int		color;
}	t_light;

typedef struct s_sph
{
	t_vec	cntr;
	float	radius;
	int		color;
}	t_sph;


typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_img		img;
	int			w;
	int			h;	
	float		whratio;
	t_list		*figs;
}	t_data;

int	pcolor(int r, int g, int b);

void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
double	ft_atof(char *str);

int		close_crest(void *param);
int		key_hook(int button, t_data *data);

void	help(void);
void	error(char *msg);

/*
**	VECTOR OPERATIONS
*/

t_vec	*new_vector(float x, float y, float z);
t_vec	*vec_sub(t_vec *a, t_vec *b);
float	vec_scalar_mul(t_vec *a, t_vec *b);
float	vec_len(t_vec *a);
void	vec_norm(t_vec *a);

/*
**	FIGURE_INIT
*/

t_sph	*new_sph(float x, float y, float z, float radius, int color);

#endif
