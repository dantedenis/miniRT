/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 18:14:36 by lcoreen           #+#    #+#             */
/*   Updated: 2022/03/09 09:32:49 by lcoreen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include <math.h>
# include <stdio.h>

//# include "mlx.h"
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
	int	x;
	int	y;
	int	z;
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
	int				color;
	struct s_light	*next;
}	t_light;

typedef struct s_sph
{
	t_vec	cntr;
	float	radius;
	t_color	color;
}	t_sph;

typedef struct s_plane
{
	t_vec	pos;
	t_vec	norm;
	t_color	color;
}	t_pl;

typedef struct s_cylinder
{
	t_vec	pos;
	t_vec	norm;
	float	diameter;
	float	height;
	t_color	color;
}	t_cy;

typedef struct s_ambi
{
	float	ratio;
	t_color	color;
}	t_ambi;

typedef struct s_obj
{
	void			*par;
	char			*key;
	struct s_obj	*next;
}	t_obj;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_img		img;
	int			w;
	int			h;	
	float		whratio;
	t_list		*figs;
	t_light		*light;
	t_obj		*obj;
}	t_data;

int	pcolor(int r, int g, int b);
int	mul_pcolor(int r, int g, int b, float i);


void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
//double	ft_atof(char *str);

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
t_vec	*vec_sum(t_vec *a, t_vec *b);
t_vec	*vec_mul_nbr(t_vec *a, float k);
void	print_vec(t_vec *vec, char *name);

/*
**	FIGURE_INIT
*/

int		init_plane(char **lines, t_data *data);
int		init_cylinder(char **lines, t_data *data);
int		init_sphere(char **lines, t_data *data);
int		init_ambient(char **lines, t_data *data);
int		init_camera(char **lines, t_data *data);
t_sph	*new_sph(float x, float y, float z, float radius, int color);

/*
**
*/

t_light	*new_light(char *type, t_vec *pos, float ratio, int color);
void	light_add(t_light **light, t_light *new);
void	clear_lst_light(t_light	**lst);
#endif
