/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:27:03 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/30 10:29:52 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_shapes(t_minirt *minirt);

void	print_4d_points(double points[4][4])
{
	int	i;
	int	j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			printf("%.3f ", points[i][j]);
		printf("\n");
	}
}

t_minirt *init_minirtaarij(t_minirt *m)
{
	m->cam = ft_calloc(1, sizeof(t_camera));
	m->shapes = ft_calloc(1, (sizeof(t_shape)));
	m->ambient = ft_calloc(1, sizeof(t_ambient));
	m->lights = ft_calloc(1, (sizeof(t_light)));
	m->up = return_tuple_pointer(0, 1, 0, VECTOR);
	m->ambient->flag = 0;
	m->cam->flag = 0;
	m->object_count = 0;
	m->light_count = 0;
	
	return (m);
}

t_minirt *init_sphere(t_minirt *m, int *i)
{
	t_sphere *sphere = create_sphere(0, 0, 0, m->shapes[*i]->r);
	t_tuple *coords = m->shapes[*i]->coords;
	t_tuple *color = m->shapes[*i]->material->color;
	// sphere->material->is_patterned = m->shapes[*i]->material->is_patterned;
	// if(sphere->material->is_patterned == true)
		// sphere->material->pattern = create_pattern(m->shapes[*i]->material->pattern.color_one,
												// m->shapes[*i]->material->pattern.color_two,
												// m->shapes[*i]->material->pattern.pattern_scale);
	m->shapes[*i] = create_shape(SPHERE, sphere);
	m->shapes[*i]->coords = coords;
	m->shapes[*i]->material->color = color;
	transform_shape(m, *i, translate, 0, coords);
	
	*i += 1;
	return (m);
}

t_minirt *init_plane(t_minirt *m, int *i)
{
	t_plane *plane = create_plane();
	t_tuple *coords = m->shapes[*i]->coords;
	t_tuple *color = m->shapes[*i]->material->color;
	// sphere->material->is_patterned = m->shapes[*i]->material->is_patterned;
	// if(sphere->material->is_patterned == true)
		// sphere->material->pattern = create_pattern(m->shapes[*i]->material->pattern.color_one,
												// m->shapes[*i]->material->pattern.color_two,
												// m->shapes[*i]->material->pattern.pattern_scale);
	m->shapes[*i] = create_shape(PLANE, plane);
	m->shapes[*i]->coords = coords;
	m->shapes[*i]->material->color = color;
	transform_shape(m, *i, translate, 0, coords);
	// transform_shape(m, *i, rotate_x, m->shapes[*i]->orientation.x, )
	*i += 1;
	return(m);
}

t_minirt *init_cylinder(t_minirt *m, int *i)
{
	t_cylinder *cylinder = create_cylinder(return_point(0, 0, 0));
	t_tuple *coords = m->shapes[*i]->coords;
	t_tuple *color = m->shapes[*i]->material->color;
	cylinder->maximum = m->shapes[*i]->h;
	cylinder->minimum = 0;
	cylinder->radius = m->shapes[*i]->r;
	cylinder->is_closed = 1;
	m->shapes[*i] = create_shape(CYLINDER, cylinder);
	m->shapes[*i]->coords = coords;
	m->shapes[*i]->material->color = color;
	transform_shape(m, *i, translate, 0, coords);
	*i += 1;
	return (m);
}

t_minirt *parse_objects(t_minirt *m)
{
	int i = 0;
	while(i < m->object_count)
	{
		if(m->shapes[i]->type == SPHERE)
			m = init_sphere(m, &i);
		else if(m->shapes[i]->type == PLANE)
			m = init_plane(m, &i);
		else if(m->shapes[i]->type == CYLINDER)
			m = init_cylinder(m, &i);
		// else if(m->shapes[i]->type == CONE)
		// 	m = init_cone(m, &i);
	}
	return (m);
}

// t_minirt *init_light(t_minirt *m, int *i)
// {
// 	m->lights[*i] = ft_calloc(1, sizeof(t_light));
// 	return (m);
// }

// t_minirt *parse_lights(t_minirt *m)
// {
// 	int i = 0;
// 	m->lights = ft_calloc(m->light_count, sizeof(t_light));
// 	if(!m->lights)
// 		return (NULL);
// 	while(i < m->light_count)
// 	{
// 		m = init_light(m, &i);
// 		i++;
// 	}
// 	return (m);
// }

int	main(int ac, char **av)
{
	t_mlx mlx;
	t_minirt	*m;
	t_hook_params	*hooks;
	if(ac == 2)
	{
		hooks = ft_calloc(1, sizeof(t_hook_params));
		m = ft_calloc(1, sizeof(t_minirt));
		m = init_minirtaarij(m);
		if(fileopen(av[1], m) == 0)
		{
			init_mlx(&mlx);
			if (m->object_count > 0)
				m = parse_objects(m);
			// if(m->light_count > 0)
			// 	m = parse_lights(m);
			m->cam = return_camera_ptr(WIDTH, HEIGHT, DEG_RAD(m->cam->fov), NULL);
			m->cam->view_matrix = view_transform(m->to, m->from, m->up);
			threaded_render(&mlx, m, m->cam);
			// threaded_render(&mlx, m->cam, m);
			hooks->m = m;
			hooks->mlx = &mlx;
			hooks->original_from = return_point(m->from->x, m->from->y, m->from->z);
			hooks->original_to = return_point(m->to->x, m->to->y, m->to->z);
			hooks->original_up = return_vector(m->up->x, m->up->y, m->up->z);
			mlx_hook(mlx.win, 2, 1L << 0, get_key_pressed, hooks);
			mlx_hook(mlx.win, 17, 1L << 2, closert, m);
			mlx_loop(&mlx.mlx);
		}
	}
}
//int main(int ac, char **av)
//{
//	if (ac != 2)
//		return (1);
//	t_ppm	*ppm = create_ppm(av[1]);
//	write_to_ppm(ppm);
//	(void)ac;
//	(void)ppm;
//}