/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:22:46 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/28 21:18:20 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PPM_H
# define PPM_H

# include "minirt.h"

void	*parse_line(char *line, char check, t_ppm *ppm);
void	read_ppm_header(int fd, t_ppm *ppm);
t_ppm	*create_ppm(char *filename);
void	write_to_ppm(t_ppm *ppm);

#endif