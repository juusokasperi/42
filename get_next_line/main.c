/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:58:03 by jrinta-           #+#    #+#             */
/*   Updated: 2024/08/15 21:23:09 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*

Static Linked List

Lue tiedostoa ja lisää listaan niin kauan, että listaan tulee string jossa \n
Kun löytyy \n, luo uusi string \n asti
Siisti lista -> kopioi viimeisesta nodesta kaikki, jotka tulee
\n jalkeen paitsi jos siella on ainostaan \0
Vapauta linked list ja aseta linked listin ekaksi juuri luotu uusi lista

*/

int	main(void)
{
	int		fd;
	char	*next_line;
	int		lines;

	lines = 1;
	fd = open("test.txt", O_RDONLY);
	while (1)
	{
		if ((next_line = get_next_line(fd)))
			printf("%d->%s", lines++, next_line);
		if (!next_line)
			break ;
		free(next_line);
	}
	free(next_line);
	return (0);
}
