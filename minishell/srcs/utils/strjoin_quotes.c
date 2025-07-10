/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phuocngu <phuocngu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:06:39 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/04 17:19:12 by phuocngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	copy_contents(char *s, char *s1, char *s2);

// If s1 already populated, we need extra space for the whitespace between
// the strings. Otherwise, we just need extra space for quotes and \0
char	*ft_strjoin_quotes(char *s1, char *s2)
{
	char	*s;

	if (!s1 || !s2)
		return (NULL);
	if (*s1)
		s = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 4) * sizeof(char));
	else
		s = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 3) * sizeof(char));
	if (!s)
		return (NULL);
	copy_contents(s, s1, s2);
	ft_free((void **)&s1);
	return (s);
}

static void	copy_contents(char *s, char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i])
		s[j++] = s1[i++];
	if (*s1)
		s[j++] = ' ';
	i = 0;
	s[j++] = '"';
	while (s2[i])
		s[j++] = s2[i++];
	s[j++] = '"';
	s[j] = '\0';
}
