/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_vector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phuocngu <phuocngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 22:20:19 by phuocngu          #+#    #+#             */
/*   Updated: 2025/05/16 14:20:49 by phuocngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static bool	validate_vector_components(char **parts, char *str)
{
	if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3])
	{
		printf("Error\nVector needs exactly 3 components: %s\n", str);
		free_split(parts);
		return (false);
	}
	return (true);
}

bool	parse_vector(char *str, t_vector *vec)
{
	char	**parts;
	bool	result;

	if (!str || !vec)
		return (false);
	parts = ft_split(str, ',');
	if (!validate_vector_components(parts, str))
		return (false);
	result = true;
	result &= parse_float(parts[0], &vec->x);
	result &= parse_float(parts[1], &vec->y);
	result &= parse_float(parts[2], &vec->z);
	free_split(parts);
	if (!result)
		return (false);
	return (true);
}

bool	parse_normalized_vector(char *str, t_vector *vec)
{
	if (!parse_vector(str, vec))
		return (false);
	if (vec->x == 0 && vec->y == 0 && vec->z == 0)
	{
		printf("Error\nNormalized vector cannot have all zero components: %s\n",
			str);
		return (false);
	}
	vector_normalize(vec);
	return (true);
}
