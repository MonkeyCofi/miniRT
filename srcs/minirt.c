/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:27:03 by pipolint          #+#    #+#             */
/*   Updated: 2024/11/20 02:46:55 by ahaarij          ###   ########.fr       */
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
			init_sphere(m, &i);
		else if(m->shapes[i]->type == PLANE)
			init_plane(m, &i);
		else if(m->shapes[i]->type == CYLINDER)
			init_cylinder(m, &i);
		else if(m->shapes[i]->type == CONE)
			init_cone(m, &i);
	}
	return (m);
}

int	test(int mouse_button, int mouse_x, int mouse_y, t_minirt *m)
{
	t_ray			ray;
	t_intersects	intersect;
	t_intersection*	i;
	t_inter_comp	inter;

	ray = ray_per_pixel(m->cam, mouse_x, mouse_y);
	intersect = intersect_enivornment(m, &ray);
	i = best_hit(&intersect);
	inter = precompute_intersect(m, &intersect, i, &ray);
	if (mouse_button == 1)
		m->hooks.shape_or_cam = inter.obj;
	(void)mouse_button;
	(void)inter;
	return (1);
}

int	main(int ac, char **av)
{
	t_hook_params	*hooks;
	t_minirt		*m;

	if(ac == 1){
t_4dmat rot = axis_angle(return_vector(0, 1, 0), M_PI / 2);
t_tuple vec = {{1, 0, 0, 0}}; // Directional vector, w = 0
t_tuple result;
matrix_cross(&result, &vec, rot);
printf("Result: (%f, %f, %f, %f)\n", result.x, result.y, result.z, result.w);
	}
	if(ac == 2)
	{
		hooks = ft_calloc(1, sizeof(t_hook_params));
		m = init_minirt();
		if(fileopen(av[1], m) == 1)
			return (1);
		if (m->object_count > 0)
			m = parse_objects(m);
		m->cam = return_camera_ptr(WIDTH, HEIGHT, DEG_RAD(m->cam->fov));
		m->cam->trans = m->from;
		m->forward = m->to;
		print_tuple_points(&m->left);
		m->cam->view_matrix = view_transform_test(&m->left, &m->from, &m->up, &m->cam->trans, &m->forward);
// t_4dmat	view_transform_test(t_tuple *from, t_tuple *cam, t_minirt *m)
		// m->cam->view_matrix = view_transform_test(&m->from, &m->cam->trans, m);
		m->ppm = create_ppm("42_logo.ppm");
		m->hooks = *hooks;
		hooks->m = m;
		hooks->mlx = m->mlx;
		hooks->original_from = return_point(m->from.x, m->from.y, m->from.z);
		hooks->original_to = return_point(m->to.x, m->to.y, m->to.z);
		hooks->original_up = return_vector(m->up.x, m->up.y, m->up.z);
		mlx_hook(m->mlx->win, 2, 1L << 0, get_key_pressed, hooks);
		mlx_hook(m->mlx->win, 17, 1L << 2, closert, m);
		// mlx_mouse_hook(m->mlx->win, test, m);
		threaded_render(m->mlx, m);
		mlx_loop(m->mlx->mlx);
	}
}
