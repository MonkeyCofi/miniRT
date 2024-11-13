/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:17:30 by pipolint          #+#    #+#             */
/*   Updated: 2024/11/04 08:41:18 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "minirt.h"

t_minirt	*init_default(t_mlx *mlx);
int			init_mlx(t_mlx *mlx);
void		init_cone(t_minirt *m, int *i);
void		init_cylinder(t_minirt *m, int *i);
void		init_plane(t_minirt *m, int *i);
// t_minirt	*init_minirtaarij(t_minirt *m);
t_minirt*	init_minirt();
void		init_sphere(t_minirt *m, int *i);

#endif