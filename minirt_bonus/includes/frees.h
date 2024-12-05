/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 09:27:56 by ahaarij           #+#    #+#             */
/*   Updated: 2024/11/27 09:27:57 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREES_H
# define FREES_H

# include <structs.h>

void	free_shapes(t_minirt *minirt);
void	free_things(t_minirt *minirt);
void	free_minirt(t_minirt *m);
void	*calloc_and_check(size_t memb_size, size_t nmemb, t_minirt *m, char *s);

#endif