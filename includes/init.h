/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:17:30 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/05 13:04:15 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "structs.h"

//t_minirt	*init_minirt(t_mlx *mlx);

t_minirt	*init_minirt(t_mlx *mlx, int num_of_spheres, int num_of_lights);
t_minirt	*init_default(t_mlx *mlx);
int			init_mlx(t_mlx *mlx);

#endif