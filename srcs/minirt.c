/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:27:03 by pipolint          #+#    #+#             */
/*   Updated: 2024/11/08 15:30:43 by pipolint         ###   ########.fr       */
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
		else if(m->shapes[i]->type == CONE)
			m = init_cone(m, &i);
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
	t_hook_params	*hooks;
	t_minirt		*m;
	t_mlx 			mlx;
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
			m->cam = return_camera_ptr(WIDTH, HEIGHT, DEG_RAD(m->cam->fov));
			m->cam->trans = m->from;
			m->cam->view_matrix = view_transform_test(&m->to, &m->from, &m->up, &m->cam->trans);
			//render(&mlx, m->cam, m);
			threaded_render(&mlx, m);
			hooks->m = m;
			hooks->mlx = &mlx;
			hooks->original_from = return_point(m->from.x, m->from.y, m->from.z);
			hooks->original_to = return_point(m->to.x, m->to.y, m->to.z);
			hooks->original_up = return_vector(m->up.x, m->up.y, m->up.z);
			mlx_hook(mlx.win, 2, 1L << 0, get_key_pressed, hooks);
			mlx_hook(mlx.win, 17, 1L << 2, closert, m);
			mlx_loop(&mlx.mlx);
		}
	}
}

//int	main(void)
//{
//	//t_hook_params	*hooks;
//	t_minirt		*m;
//	t_mlx 			mlx;

//	init_mlx(&mlx);
//	m = ft_calloc(1, sizeof(t_minirt));
//	m->cam = return_camera_ptr(WIDTH, HEIGHT, DEG_RAD(90));
//	m->mlx = &mlx;
//	m->to = return_point(0, 0, 1);
//	m->from = return_point(0, 0, -2);
//	m->up = return_vector(0, 1, 0);
//	m->cam->view_matrix = view_transform_test(&m->to, &m->from, &m->up);
//	m->light_count = 1;
//	m->lights = ft_calloc(m->light_count, sizeof(t_light *));
//	m->lights[0] = ft_calloc(1, sizeof(t_light));
//	m->lights[0]->position = return_point(1, 2, 0);
//	m->lights[0]->intensity = return_colorf(1, 1, 1);
//	//t_plane	*plane = create_plane();
//	t_sphere *sphere = create_sphere(0, 0, 0, 1);
//	m->object_count = 1;
//	m->shapes = ft_calloc(m->object_count, sizeof(t_shape *));
//	m->shapes[0] = create_shape(SPHERE, sphere);
//	transform_shape(m, 0, rotate_x, 0, return_tuple_pointer(0, 0, 0, POINT));
//	render(&mlx, m->cam, m);
//	//threaded_render(&mlx, m);
//	//transform_shape(m, 0, rotate_x, 0, return_tuple_pointer(0, 0, 0, POINT));
//	//transform_shape(m, 0, translate, 0, return_tuple_pointer(0, 0, 0, POINT));
//	mlx_loop(&mlx.mlx);
//}
