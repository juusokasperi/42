/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:58:03 by jrinta-           #+#    #+#             */
/*   Updated: 2024/08/15 21:49:33 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/*

Static Linked List

Lue tiedostoa ja lisää listaan niin kauan, että listaan tulee string jossa \n
Kun löytyy \n, luo uusi string \n asti
Siisti lista -> kopioi viimeisesta nodesta kaikki, jotka tulee
\n jalkeen paitsi jos siella on ainostaan \0
Vapauta linked list ja aseta linked listin ekaksi juuri luotu uusi lista

*/

int	main(int argc, char **argv)
{
	int		fd;
	int		fd_2;
	char	*next_line;
	char	*next_line_2;
	int		lines;
	int		lines_2;

	if (argc != 2 || argv[1][1] || !(argv[1][0] != 'm' || argv[1][0] != 'b'))
		return (printf("Usage: ./test <m or b>\n"));
	if (argv[1][0] == 'm')
	{
		(void)lines_2;
		(void)next_line_2;
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
	if (argv[1][0] == 'b')
	{
		lines = 1;
		lines_2 = 1;
		fd = open("test.txt", O_RDONLY);
		fd_2 = open("test2.txt", O_RDONLY);
		while (1)
		{
			if ((next_line = get_next_line(fd)))
				printf("fd1->%d->%s", lines++, next_line);
			if ((next_line_2 = get_next_line(fd_2)))
				printf("fd2->%d->%s", lines_2++, next_line_2);
			if (!next_line && !next_line_2)
				break ;
			free(next_line);
			free(next_line_2);
		}
		free(next_line);
		free(next_line_2);
		return (0);
	}
}
