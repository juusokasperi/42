/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 19:17:09 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/27 19:36:56 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_display_file.h"

int	ft_display_file(char *str)
{
	char	buffer[1024];
	int		fd;
	int		nb_read;

	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		write(2, "Error opening file.", 19);
		return (0);
	}
	nb_read = -1;
	while (nb_read != 0)
	{
		nb_read = read(fd, buffer, 1024);
		if (nb_read == -1)
			return (0);
		write(1, buffer, nb_read);
	}
	close(fd);
	return (1);
}

int	main(int argc, char **argv)
{
	if (argc == 1)
	{
		write(2, "File name missing.", 18);
		return (1);
	}
	else if (argc > 2)
	{
		write(2, "Too many arguments.", 19);
		return (1);
	}
	ft_display_file(argv[1]);
	return (0);
}
