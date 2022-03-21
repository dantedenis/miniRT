/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcoreen <lcoreen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 18:14:36 by lcoreen           #+#    #+#             */
/*   Updated: 2022/03/20 18:53:42 by lcoreen          ###   ########.fr       */
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
	t_vec	up;
	t_vec	right;
}	t_cam;

typedef struct s_light
{
	char			*type;
	t_vec			pos;
	float			ratio;
	t_color			color;
	struct s_light	*next;
}	t_light;

typedef struct s_sph
{
	t_vec			cntr;
	float			radius;
}	t_sph;

typedef struct s_pl
{
	t_vec			n;
	t_vec			c;
}	t_pl;

typedef struct s_cy
{
	t_vec	pos;
	t_vec	norm;
	float	diameter;
	float	height;
	int		part;
}	t_cy;

typedef struct s_obj
{
	void			*par;
	char			*key;
	float			t;
	t_color			color;
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
	t_vec		ray;
	t_obj		*obj;
	t_light		*light;
	t_cam		cam;
}	t_data;

/*
**	COLOR_FUNCTIONS
*/

int		pcolor_from_struct(t_color *color);
int		pcolor(int r, int g, int b);
int		mul_pcolor(t_color *color, t_vec *t);
t_color	*new_color(int r, int g, int b);

void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
void	create_image(t_data *data);

void	free_arr(char ***arr);
void	free_list_obj(t_obj **lst);

int		close_crest(t_data *data);
int		key_hook(int button, t_data *data);

void	help(void);
//void	error(char *msg);

void	draw(t_data *data);
t_obj	*trasing(t_data *data, t_vec *o, float t_min, float t_max);
int		ray_trase(t_data *data, t_vec *o, int x, int y);
t_vec	compute_light(t_data *data, t_light *light, t_vec *P, t_vec *N);
//int		parser(char *str, t_data *data);
int		reader_file(char *file, t_data *data);

t_vec	get_cy_norm(t_cy *cy, t_vec *ray, t_vec *o, float t);
float	intersect_cylinder(t_cy *tmp, t_vec *ray, t_vec *o, float *t2);
float	intersect_sphere(t_sph *tmp, t_vec *ray, t_vec *o, float *t2);
float	intersect_plane(t_pl *tmp, t_vec *ray, t_vec *o, float *t2);

/*
**	VECTOR OPERATIONS
*/

t_vec	new_vector(float x, float y, float z);
t_vec	vec_mul_nbr(t_vec *a, float k);
t_vec	vec_sum(t_vec *a, t_vec *b);
t_vec	vec_sub(t_vec *a, t_vec *b);
float	vec_scalar_mul(t_vec *a, t_vec *b);
float	vec_len(t_vec *a);
void	vec_norm(t_vec *a);
t_vec	vec_copy(t_vec *src);
t_vec	vec_mul(t_vec *a, t_vec *b);
void	print_vec(t_vec *vec, char *name);

/*
**	FIGURE_INIT
*/

// t_sph	*new_sph(t_vec *cntr, float radius, t_color *color);
// void	clear_lst_sph(t_sph	**lst);
// void	sph_add(t_sph **sph, t_sph *new);
// t_plane	*new_plane(t_vec *n, t_vec *coord, t_color *color);
// void	plane_add(t_plane **plane, t_plane *new);
// void	clear_lst_plane(t_plane	**lst);

int		init_plane(char **lines, t_data *data, int line);
int		init_cylinder(char **lines, t_data *data, int line);
int		init_sphere(char **lines, t_data *data, int line);
int		init_ambient(char **lines, t_data *data, int line);
int		init_camera(char **lines, t_data *data, int line);
int		init_light(char **lines, t_data *data, int line);

/*
**	LIGHT_FUNCTIONS
*/

t_light	*new_light(char *type, t_vec *pos, float ratio, t_color *color);
void	light_add(t_light **light, t_light *new);
void	clear_lst_light(t_light	**lst);
void	error(char *msg, t_data *data, int line);

#endif
