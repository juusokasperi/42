/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 10:37:22 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/30 17:04:38 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	main(int argc, char **argv)
{
	if (argc > 2)
	{
		printf("Usage: \"%s\" or \"%s bonus\"\n", argv[0], argv[0]);
		return (1);
	}
	else if (argc == 1)
	{
	test_isalpha();
	test_isdigit();
	test_isalnum();
	test_strlen();
	test_memset();
	test_bzero();
	test_memcpy();
	test_memmove();
	test_strlcpy();
	test_strlcat();
	test_toupper();
	test_tolower();
	test_strchr();
	test_strrchr();
	test_strncmp();
	test_memchr();
	test_memcmp();
	test_strnstr();
	test_atoi();
	test_calloc();
	test_strdup();
	test_substr();
	test_strjoin();
	test_strtrim();
	test_split();
	test_itoa();
	test_strmapi();
	test_striteri();
	}
	else if (argc == 2 && ft_strlen(argv[1]) == 5
		&& ft_strncmp(argv[1], "bonus", 5) == 0)
	{
		printf("---------------------------\n");
		printf("---------- BONUS ----------\n\n");
		test_lstnew();
		test_lstaddfront();
		test_lstsize();
		test_lstlast();
		test_lstaddback();
		test_lstdelone();
		test_lstclear();
		test_lstiter();
		test_lstmap();
	}
	return (0);
}
