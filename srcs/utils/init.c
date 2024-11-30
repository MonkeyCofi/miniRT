/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:17:00 by pipolint          #+#    #+#             */
/*   Updated: 2024/11/29 21:11:43 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_mlx(t_minirt *m)
{
	m->mlx = calloc_and_check(sizeof(t_mlx), 1, m, MLX_ERR);
	m->mlx->mlx = mlx_init();
	if (!m->mlx->mlx)
	{
		write_err("Couldn't initialize mlx", '\n');
		free_minirt(m);
	}
	m->mlx->win = mlx_new_window(m->mlx->mlx, WIDTH, HEIGHT, "miniRT");
	if (!m->mlx->win)
		free_minirt(m);
	m->mlx->img.img = mlx_new_image(m->mlx->mlx, WIDTH, HEIGHT);
	if (!(m->mlx->img.img))
		free_minirt(m);
	m->mlx->img.img_addr = mlx_get_data_addr(m->mlx->img.img, &m->mlx->img.bpp, \
	&m->mlx->img.line_length, &m->mlx->img.endian);
	m->mlx->img.img_height = HEIGHT;
	m->mlx->img.img_width = WIDTH;
	//return (1);
}

t_minirt	*init_minirt(void)
{
	t_minirt	*m;

	m = calloc_and_check(sizeof(t_minirt), 1, NULL, MRT_ERR);
	m->cam = calloc_and_check(sizeof(t_camera), 1, m, CAM_ERR);
	m->cam->trans = return_point(0, 0, 0);
	m->shapes = calloc_and_check(sizeof(t_shape), 1, m, SHP_ERR);
	m->ambient = calloc_and_check(sizeof(t_ambient), 1, m, AMB_ERR);
	m->lights = calloc_and_check(sizeof(t_light), 1, m, LGT_ERR);
	m->up = return_tuple(0, 1, 0, VECTOR);
	m->ambient->flag = 0;
	m->ambient->ratio = 0;
	m->cam->flag = 0;
	m->object_count = 0;
	m->light_count = 0;
	return (m);
}

void	init_sphere(t_minirt *m, int *i)
{
	t_sphere	*sphere;
	t_mater		*material;
	t_thing		s;

	s.i = *i;
	s.coords = m->shapes[*i]->coords;
	material = m->shapes[*i]->material;
	sphere = create_sphere(m, m->shapes[*i]->r);
	//m->shapes[*i]->shape = sphere;
	free(m->shapes[*i]);
	m->shapes[*i] = create_shape(SPHERE, sphere);
	m->shapes[*i]->material = material;
	if (m->shapes[*i]->material->is_patterned == true)
		create_pattern(material->pattern.color_one,
			m->shapes[*i]->material->pattern.color_two,
			10, &m->shapes[*i]->material->pattern);
	m->shapes[*i]->transform = identity();
	m->shapes[*i]->coords = s.coords;
	transform_shape(m, &s, translate, 0);
	*i += 1;
}

void	init_plane(t_minirt *m, int *i)
{
	t_4dmat	rot;
	t_plane	*plane;
	t_thing	s;
	t_mater	*material;
	t_tuple	orientation;

	s.i = *i;
	s.coords = m->shapes[*i]->coords;
	plane = create_plane(m);
	material = m->shapes[*i]->material;
	orientation = m->shapes[*i]->orientation;
	//m->shapes[*i]->shape = plane;
	free(m->shapes[*i]);
	m->shapes[*i] = create_shape(PLANE, plane);
	m->shapes[*i]->material = material;
	if (m->shapes[*i]->material->is_patterned == true)
		create_pattern(material->pattern.color_one,
			m->shapes[*i]->material->pattern.color_two,
			10, &m->shapes[*i]->material->pattern);
	transform_shape(m, &s, translate, 0);
	rot = get_axis_angle(&orientation);
	m->shapes[*i]->transform = mat4d_mult_fast_static(\
						&m->shapes[*i]->transform, &rot);
	set_inverse_transpose(m->shapes[*i], &m->shapes[*i]->transform);
	*i += 1;
}

void	init_cylinder(t_minirt *m, int *i)
{
	t_cylinder	*cylinder;
	t_thing		s;
	t_tuple		orientation;
	t_mater		*material;
	t_4dmat		rot;

	cylinder = create_cylinder(m);
	s.i = *i;
	s.coords = m->shapes[*i]->coords;
	orientation = m->shapes[*i]->orientation;
	material = m->shapes[*i]->material;
	cylinder->maximum = m->shapes[*i]->h;
	cylinder->radius = m->shapes[*i]->r;
	//m->shapes[*i]->shape = cylinder;
	free(m->shapes[*i]);
	m->shapes[*i] = create_shape(CYLINDER, cylinder);
	m->shapes[*i]->material = material;
	if (m->shapes[*i]->material->is_patterned == true)
		create_pattern(material->pattern.color_one,
			m->shapes[*i]->material->pattern.color_two,
			10, &m->shapes[*i]->material->pattern);
	transform_shape(m, &s, translate, 0);
	rot = get_axis_angle(&orientation);
	m->shapes[*i]->transform = mat4d_mult_fast_static(\
	&m->shapes[*i]->transform, &rot);
	set_inverse_transpose(m->shapes[*i], &m->shapes[*i]->transform);
	*i += 1;
}
