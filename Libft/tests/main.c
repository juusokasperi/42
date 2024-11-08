/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 10:37:22 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/08 12:12:55 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	main(int argc, char **argv)
{
	if (argc > 2)
	{
		printf("Usage: \"%s\" or \"%s bonus\" or \"%s function_name\"\n", argv[0], argv[0], argv[0]);
		return (1);
	}
	if (argc == 1)
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
		test_putnbrfd();
		test_putcharfd();
		return (0);
	}
	if (ft_strncmp(argv[1], "isalpha", ft_strlen("isalpha")) == 0)
		test_isalpha();
	if (ft_strncmp(argv[1], "isdigit", ft_strlen("isdigit")) == 0)
		test_isdigit();
	if (ft_strncmp(argv[1], "isalnum", ft_strlen("isalnum")) == 0)
		test_isalnum();
	if (ft_strncmp(argv[1], "isascii", ft_strlen("isascii")) == 0)
		test_isascii();
	if (ft_strncmp(argv[1], "isprint", ft_strlen("isprint")) == 0)
		test_isprint();
	if (ft_strncmp(argv[1], "strlen", ft_strlen("strlen")) == 0)
		test_strlen();
	if (ft_strncmp(argv[1], "memset", ft_strlen("memset")) == 0)
		test_memset();
	if (ft_strncmp(argv[1], "bzero", ft_strlen("bzero")) == 0)
		test_bzero();
	if (ft_strncmp(argv[1], "memcpy", ft_strlen("memcpy")) == 0)
		test_memcpy();
	if (ft_strncmp(argv[1], "memmove", ft_strlen("memmove")) == 0)
		test_memmove();
	if (ft_strncmp(argv[1], "strlcpy", ft_strlen("strlcpy")) == 0)
		test_strlcpy();
	if (ft_strncmp(argv[1], "strlcat", ft_strlen("strlcat")) == 0)
		test_strlcat();
	if (ft_strncmp(argv[1], "toupper", ft_strlen("toupper")) == 0)
		test_toupper();
	if (ft_strncmp(argv[1], "tolower", ft_strlen("tolower")) == 0)
		test_tolower();
	if (ft_strncmp(argv[1], "strchr", ft_strlen("strchr")) == 0)
		test_strchr();
	if (ft_strncmp(argv[1], "strrchr", ft_strlen("strrchr")) == 0)
		test_strrchr();
	if (ft_strncmp(argv[1], "strncmp", ft_strlen("strncmp")) == 0)
		test_strncmp();
	if (ft_strncmp(argv[1], "memchr", ft_strlen("memchr")) == 0)
		test_memchr();
	if (ft_strncmp(argv[1], "memcmp", ft_strlen("memcmp")) == 0)
		test_memcmp();
	if (ft_strncmp(argv[1], "strnstr", ft_strlen("strnstr")) == 0)
		test_strnstr();
	if (ft_strncmp(argv[1], "atoi", ft_strlen("atoi")) == 0)
		test_atoi();
	if (ft_strncmp(argv[1], "calloc", ft_strlen("calloc")) == 0)
		test_calloc();
	if (ft_strncmp(argv[1], "strdup", ft_strlen("strdup")) == 0)
		test_strdup();
	if (ft_strncmp(argv[1], "substr", ft_strlen("substr")) == 0)
		test_substr();
	if (ft_strncmp(argv[1], "strjoin", ft_strlen("strjoin")) == 0)
		test_strjoin();
	if (ft_strncmp(argv[1], "strtrim", ft_strlen("strncmp")) == 0)
		test_strtrim();
	if (ft_strncmp(argv[1], "split", ft_strlen("split")) == 0)
		test_split();
	if (ft_strncmp(argv[1], "itoa", ft_strlen("itoa")) == 0)
		test_itoa();
	if (ft_strncmp(argv[1], "strmapi", ft_strlen("strmapi")) == 0)
		test_strmapi();
	if (ft_strncmp(argv[1], "striteri", ft_strlen("striteri")) == 0)
		test_striteri();
	if (ft_strncmp(argv[1], "lstnew", ft_strlen("lstnew")) == 0)
		test_lstnew();
	if (ft_strncmp(argv[1], "lstaddfront", ft_strlen("lstaddfront")) == 0)
		test_lstaddfront();
	if (ft_strncmp(argv[1], "lstsize", ft_strlen("lstsize")) == 0)
		test_lstsize();
	if (ft_strncmp(argv[1], "lstlast", ft_strlen("lstlast")) == 0)
		test_lstlast();
	if (ft_strncmp(argv[1], "lstaddback", ft_strlen("lstaddback")) == 0)
		test_lstaddback();
	if (ft_strncmp(argv[1], "lstdelone", ft_strlen("lstdelone")) == 0)
		test_lstdelone();
	if (ft_strncmp(argv[1], "lstclear", ft_strlen("lstclear")) == 0)
		test_lstclear();
	if (ft_strncmp(argv[1], "lstiter", ft_strlen("lstiter")) == 0)
		test_lstiter();
	if (ft_strncmp(argv[1], "lstmap", ft_strlen("lstmap")) == 0)
		test_lstmap();
	if (ft_strncmp(argv[1], "putnbrfd", ft_strlen("putnbrfd")) == 0)
		test_putnbrfd();
	if (ft_strncmp(argv[1], "putcharfd", ft_strlen("putcharfd")) == 0)
		test_putcharfd();
	if (ft_strncmp(argv[1], "putendlfd", ft_strlen("putendlfd")) == 0)
		test_putendlfd();
	if (ft_strncmp(argv[1], "bonus", 5) == 0)
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
