/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:27:03 by pipolint          #+#    #+#             */
/*   Updated: 2024/11/27 18:53:11 by pipolint         ###   ########.fr       */
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

	if (ac != 2)
	{
		write(2, "Usage: ./minirt [SCENE_FILE]\n", 29);
		return (1);
	}
	hooks = ft_calloc(1, sizeof(t_hook_params));
	m = init_minirt();
	if(fileopen(av[1], m) == 1)
		return (1);
	if (m->object_count > 0)
		m = parse_objects(m);
	m->cam = return_camera_ptr(WIDTH, HEIGHT, DEG_RAD(m->cam->fov));
	m->cam->trans = m->from;
	m->forward = m->to;
	m->cam->view_matrix = view_transform_test(&m->left, &m->from, &m->up, &m->cam->trans, &m->forward);
	m->ppm = create_ppm("test.ppm");
	m->xpm.img = mlx_xpm_file_to_image(m->mlx->mlx, "brick_normal.xpm", &m->xpm_width, &m->xpm_height);
	m->xpm.img_addr = mlx_get_data_addr(m->xpm.img, &m->xpm.bpp, &m->xpm.line_length, &m->xpm.endian);
	fill_colors(m);
	m->hooks = *hooks;
	hooks->m = m;
	hooks->mlx = m->mlx;
	hooks->original_from = return_point(m->from.x, m->from.y, m->from.z);
	hooks->original_to = return_point(m->to.x, m->to.y, m->to.z);
	hooks->original_up = return_vector(m->up.x, m->up.y, m->up.z);
	mlx_hook(m->mlx->win, 2, 1L << 0, get_key_pressed, hooks);
	mlx_hook(m->mlx->win, 17, 1L << 2, closert, m);
	//render(m->mlx, m->cam, m);
	threaded_render(m->mlx, m);
	mlx_loop(m->mlx->mlx);
}
