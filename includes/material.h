/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:28:19 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/15 12:41:19 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_H
# define MATERIAL_H

# include "structs.h"

t_mater	*create_default_material();
t_mater	*create_material(t_tuple color, float diffuse, float ambient, float specular, float shine);

#endif
