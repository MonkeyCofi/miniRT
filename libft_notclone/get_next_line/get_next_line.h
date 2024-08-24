/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 19:35:11 by pipolint          #+#    #+#             */
/*   Updated: 2023/12/21 15:12:50 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# ifndef OPEN_NAX
#  define OPEN_MAX 10240
# endif

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# include "../libft.h"

char	*get_next_line(int fd);

char	*ft_newlinejoin(char *res, char *buffer);

#endif