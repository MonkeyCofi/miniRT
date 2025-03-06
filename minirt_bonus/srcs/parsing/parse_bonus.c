/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:22:45 by ahaarij           #+#    #+#             */
/*   Updated: 2024/12/10 20:55:29 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	recognizetexture(t_minirt *m, char *string, t_mater *material, int *clones)
{
	char	**params;

	params = NULL;
	if (clones[5])
		parse_error(m, "Texture: Only spheres can have textures", \
			NULL, 1);
	if (clones[4])
		parse_error(m, "Texture: Texture already exists", \
			NULL, 1);
	params = ft_split_and_check(m, string, '=', 1);
	open_texture(m, material, params);
	clones[4] = 1;
	free_arr(params);
	return (0);
}

int	recognizespecular(t_minirt *m, char *str, t_mater *material, int *clones)
{
	int		i;
	char	**strs;

	i = -1;
	if (clones[1])
		return (write_and_return(m, "Error\nSpecular exists", 1));
	if (ft_strncmp(str, "specular=default", 16) == 0)
	{
		clones[1] = 1;
		return (0);
	}
	strs = ft_split_and_check(m, str, '=', true);
	if (arr_len(strs) != 2 && free_arr(strs))
		return (1);
	while (strs && strs[++i])
	{
		if (i == 0 && ft_strncmp(strs[i], "specular", 8) != 0 && free_arr(strs))
			return (write_and_return(m, "Error\nSpecular: Wrong keyword\n", 1));
		if (i == 1 && check_double(strs[i], &material->specular, false) \
			&& free_arr(strs))
			return (write_and_return(m, "Error\nSpecular: Wrong value\n", 1));
	}
	free_arr(strs);
	clones[1] = 1;
	return (0);
}

int	recognizediffuse(t_minirt *m, char *str, t_mater *material, int *clones)
{
	int		i;
	char	**strs;

	i = -1;
	if (clones[2])
		return (write_and_return(m, ERR_DIF_EX, 1));
	if (ft_strncmp(str, "diffuse=default", 15) == 0)
	{
		clones[2] = 1;
		return (0);
	}
	strs = ft_split_and_check(m, str, '=', true);
	if (arr_len(strs) != 2)
		return (1);
	while (strs && strs[++i])
	{
		if (i == 0 && ft_strncmp(strs[i], "diffuse", 7) != 0)
			return (write_and_return(m, ERR_DIF_INV, 1));
		if (i == 1 && check_double(strs[i], &material->diffuse, false))
			return (write_and_return(m, ERR_DIF_VAL, 1));
	}
	free_arr(strs);
	clones[2] = 1;
	return (0);
}

int	recognizeambient(t_minirt *m, char *str, t_mater *material, int *clones)
{
	int		i;
	char	**strs;

	i = -1;
	if (clones[3])
		return (write_and_return(m, ERR_SHP_AMB_EX, 1));
	if (ft_strncmp(str, "ambient=default", 15) == 0)
	{
		clones[3] = 1;
		return (0);
	}
	strs = ft_split_and_check(m, str, '=', true);
	if (arr_len(strs) != 2)
		return (1);
	while (strs[++i])
	{
		if (i == 0 && ft_strncmp(strs[i], "ambient", 7) != 0)
			return (write_and_return(m, ERR_SHP_AMB_INV, 1));
		if (i == 1 && check_double(strs[i], &material->ambient, false))
			return (write_and_return(m, ERR_SHP_AMB_VAL, 1));
	}
	free_arr(strs);
	clones[3] = 1;
	return (0);
}

int	recognizepattern(t_minirt *m, char *str, t_mater *material, int *clones)
{
	int		i;
	char	**strs;

	i = -1;
	if (clones[0])
		return (write_and_return(m, ERR_PAT_EX, 1));
	strs = ft_split_and_check(m, str, '=', true);
	if (arr_len(strs) != 2 && free_arr(strs))
		return (write_and_return(m, ERR_PAT_PAR, 1));
	while (strs && strs[++i])
	{
		if (i == 0 && ft_strncmp(strs[i], "pattern", 7) != 0 && free_arr(strs))
			return (write_and_return(m, ERR_PAT_INV, 1));
		if (i == 1 && !dovectorcolor(strs[i], \
		&material->pattern.color_two) && free_arr(strs))
			return (write_and_return(m, ERR_PAT_VAL, 1));
	}
	free_arr(strs);
	material->is_patterned = true;
	material->pattern.color_one = material->color;
	clones[0] = 1;
	return (0);
}
