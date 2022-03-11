/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 18:14:36 by lcoreen           #+#    #+#             */
/*   Updated: 2022/03/10 17:12:08 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include <math.h>
# include <stdio.h>

# include "mlx.h"
# include "libft.h"
# define FLT_MAX 3.402823e+38

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

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_cam
{
	t_vec	pos;
	t_vec	orient;
	float	fov;
}	t_cam;

typedef struct s_light
{
	char			*type;
	t_vec			*pos;
	float			l_ratio;
	t_color			*color;
	struct s_light	*next;
}	t_light;

typedef struct s_sph
{
	t_vec			*cntr;
	float			radius;
	t_color			*color;
	struct s_sph	*next;
	float			t_close;
}	t_sph;


typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_img		img;
	int			w;
	int			h;	
	float		whratio;
	t_vec		*ray;
	t_sph		*sph;
	t_light		*light;
}	t_data;

/*
**	COLOR_FUNCTIONS
*/

int	pcolor_from_struct(t_color *color);
int	pcolor(int r, int g, int b);
int	mul_pcolor(t_color *color, t_vec *t);
t_color	*new_color(int r, int g, int b);


void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
double	ft_atof(char *str);

int		close_crest(t_data *data);
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
t_vec	*vec_sum(t_vec *a, t_vec *b);
void	vec_sum_inplace(t_vec *a, t_color *b, float k);
t_vec	*vec_mul_nbr(t_vec *a, float k);
void	print_vec(t_vec *vec, char *name);

/*
**	FIGURE_INIT
*/

t_sph	*new_sph(t_vec *cntr, float radius, t_color *color);
void	clear_lst_sph(t_sph	**lst);
void	sph_add(t_sph **sph, t_sph *new);

/*
**	LIGHT_FUNCTIONS
*/

t_light	*new_light(char *type, t_vec *pos, float ratio, t_color *color);
void	light_add(t_light **light, t_light *new);
void	clear_lst_light(t_light	**lst);

#endif
