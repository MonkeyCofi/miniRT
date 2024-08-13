#include "minirt.h"

void	set_vector_points(t_vector *v, double x, double y, double z)
{
	v->x = x;
	v->y = y;
	v->z = z;
}

t_camera	init_cam(t_mlx *mlx)
{
	t_camera	cam;

	ft_bzero(&cam, sizeof(t_camera));
	cam.asp = ((double)WIDTH / HEIGHT);
	cam.vh = HEIGHT * 2;
	cam.vw = WIDTH * 2;
	set_vector_points(&cam.camera, 0, 0, 0);
	set_vector_points(&cam.v_horiz, cam.vh, 0, 0);
	set_vector_points(&cam.v_vert, 0, cam.vw, 0);
	cam.delta_vh = cam.vh / HEIGHT;
	cam.delta_vw = cam.vw / WIDTH;
	(void)mlx;
	return (cam);
}
