/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:58:03 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/20 14:31:47 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line_bonus.h"
#include "string.h"
#include "colors.h"
#include <stdio.h>
#include <fcntl.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while ((*s1 || *s2) && n--)
	{
		if (*s1 != *s2)
			return ((unsigned char) *s1 - (unsigned char) *s2);
		s1++;
		s2++;
	}
	return (0);
}

int	test_gnl(int fd)
{
	char *next_line;
	int	lines = 1;
	while (1)
	{
		if ((next_line = get_next_line(fd)))
			printf("%s%d->%s%s", KYEL, lines++, KNRM, next_line);
		if (!next_line)
			break ;
		free(next_line);
	}
	free(next_line);
	return (0);
}

int	test_gnl_bonus_3(int fd_1, int fd_2, int fd_3)
{
	char *next_line;
	char *next_line_2;
	char *next_line_3;
	int	lines = 1;
	int lines_2 = 1;
	int lines_3 = 1;
	while (1)
	{
		if ((next_line = get_next_line(fd_1)))
			printf("%sfd1->%d->%s%s", KYEL, lines++, KNRM, next_line);
		if ((next_line_2 = get_next_line(fd_2)))
			printf("%sfd2->%d->%s%s", KRED, lines_2++, KNRM, next_line_2);
		if ((next_line_3 = get_next_line(fd_3)))
			printf("%sfd3->%d->%s%s", KGRN, lines_3++, KNRM, next_line_3);
		if (!next_line && !next_line_2 && !next_line_3)
			break ;
		free(next_line);
		free(next_line_2);
		free(next_line_3);
	}
	free(next_line);
	free(next_line_2);
	free(next_line_3);
	return (0);
}

int	test_gnl_bonus(int fd_1, int fd_2)
{
	char *next_line;
	char *next_line_2;
	int	lines = 1;
	int lines_2 = 1;
	while (1)
	{
		if ((next_line = get_next_line(fd_1)))
			printf("%sfd1->%d->%s%s", KYEL, lines++, KNRM, next_line);
		if ((next_line_2 = get_next_line(fd_2)))
			printf("%sfd2->%d->%s%s", KRED, lines_2++, KNRM, next_line_2);
		if (!next_line && !next_line_2)
			break ;
		free(next_line);
		free(next_line_2);
	}
	free(next_line);
	free(next_line_2);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("%s------------------------------\n", KYEL);
		printf("-----       Usage:       -----\n%s", KNRM);
		printf("%s------------------------------\n", KYEL);

		printf("%s <file(s)_to_read>\t// Reads the given file, if compiled with bonus works up to 3 files\n", argv[0]);
		printf("%s inv\t\t\t// Attempts to read an invalid file descriptor\n", argv[0]);
		printf("%s inv bonus\t\t// Reads two existing files in addition to an invalid file descriptor\n", argv[0]);
		printf("%s stdin\t\t\t// Reads from std input\n\n", argv[0]);

		printf("%s------------------------------\n", KYEL);
		printf("%s- Some files to try reading: -\n%s", KYEL, KNRM);
		printf("%s------------------------------\n", KYEL);
		printf("test/multiple_long_lines.txt test/multiple_short_lines.txt test/multiple_empty_lines.txt\n");
		printf("test/empty.txt test/giant_line.txt test/giant_line_nl.txt\n");
		printf("%s------------------------------\n%s", KYEL, KNRM);
		return (1);
	}
	if (argc == 2)
	{
		if (ft_strncmp(argv[1], "stdin", 5) == 0 && strlen(argv[1]) == 5)
			return (test_gnl(0));
		else if (ft_strncmp(argv[1], "inv", 3) == 0 && strlen(argv[1]) == 3)
			return (test_gnl(42));
		else
			return (test_gnl(open(argv[1], O_RDONLY)));
	}
	if (argc == 3)
	{
		if (ft_strncmp(argv[1], "inv", 3) == 0&& strlen(argv[1]) == 3
			&& ft_strncmp(argv[2], "bonus", 5) == 0 && strlen(argv[2]) == 5)
			{
				int fd = open("test/multiple_long_lines.txt", O_RDONLY);
				int fd_2 = open("test/multiple_short_lines.txt", O_RDONLY);
				return (test_gnl_bonus_3(fd, fd_2, 42));
			}
		else
		{
			int fd = open(argv[1], O_RDONLY);
			int fd_2 = open(argv[2], O_RDONLY);
			return (test_gnl_bonus(fd, fd_2));
		}
	}
	if (argc == 4)
	{
		int fd = open(argv[1], O_RDONLY);
		int fd_2 = open(argv[2], O_RDONLY);
		int fd_3 = open(argv[3], O_RDONLY);
		return (test_gnl_bonus_3(fd, fd_2, fd_3));
	}
	else
		return (printf("Error.\n"));
}
