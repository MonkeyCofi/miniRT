/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:17:30 by pipolint          #+#    #+#             */
/*   Updated: 2024/11/29 18:41:10 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "minirt.h"

t_minirt	*init_default(t_mlx *mlx);
void		init_mlx(t_minirt *m);
void		init_cone(t_minirt *m, int *i);
void		init_cylinder(t_minirt *m, int *i);
void		init_plane(t_minirt *m, int *i);
t_minirt	*init_minirt(void);
void		init_sphere(t_minirt *m, int *i);

#endif