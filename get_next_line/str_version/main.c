/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:58:03 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/17 19:26:44 by juusorinta       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include "string.h"
#include <stdio.h>
#include <fcntl.h>

int	main(int argc, char **argv)
{
	int		fd;
	int		fd_2;
	char	*next_line;
	char	*next_line_2;
	int		lines;
	int		lines_2;

	if (argc < 2)
		return (printf("Usage: ./test <m or b or i (for stdin)> or ./test <file(s) to read>\n"));
	if (argv[1][0] == 'i' && strlen(argv[1]) == 1)
	{
		(void)lines_2;
		(void)next_line_2;
		lines = 1;
		while (1)
		{
			if ((next_line = get_next_line(0)))
				printf("%d->%s", lines++, next_line);
			if (!next_line)
				break ;
			free(next_line);
		}
		free(next_line);
		return (0);
	}
	if (argv[1][0] == 'm' && strlen(argv[1]) == 1)
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
	if (argv[1][0] == 'b' && strlen(argv[1]) == 1)
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
	if (argc == 2) {
		lines = 1;
		fd = open(argv[1], O_RDONLY);
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
	if (argc == 3) {
		lines = 1;
		lines_2 = 1;
		fd = open(argv[1], O_RDONLY);
		fd_2 = open(argv[2], O_RDONLY);
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
