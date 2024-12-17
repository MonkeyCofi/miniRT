/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 09:27:56 by ahaarij           #+#    #+#             */
/*   Updated: 2024/12/10 19:36:46 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREES_H
# define FREES_H

# include <structs.h>

void	free_shapes(t_minirt *minirt);
void	free_minirt(t_minirt *m, int exit_code);
void	*calloc_and_check(size_t memb_size, size_t nmemb, t_minirt *m, char *s);
int		free_str(char *str);

#endif