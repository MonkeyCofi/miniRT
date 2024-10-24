/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:28:19 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/24 17:53:30 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_H
# define MATERIAL_H

# include "structs.h"

t_mater	*create_default_material();
t_mater	*create_material(t_tuple color, double diffuse, double ambient, double specular, double shine);

#endif
