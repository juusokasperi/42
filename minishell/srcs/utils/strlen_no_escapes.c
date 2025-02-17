/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlen_no_escapes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 20:01:29 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/05 20:04:09 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	Doesn't increment length for characters between \001 and \002
//	Needed for the "exit" printing when user presses ctrl+d in interactive mode.
size_t	strlen_no_escapes(const char *s)
{
	int		i;
	int		escaped;
	size_t	len;

	len = 0;
	escaped = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] == '\001')
			escaped = 1;
		else if (s[i] == '\002')
			escaped = 0;
		else if (!escaped)
			len++;
	}
	return (len);
}
