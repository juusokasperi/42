/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strrchr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:27:54 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/29 14:34:13 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_strrchr(void)
{
	char str[] = "Test String With Letter Y";
	char *ptr;

	printf("---------------------------\n");
	printf("FT_STRRCHR:\n");
	ptr = ft_strrchr(str, 'Y');
	printf("Looking for Y, ptr points to %s\n", ptr);
	ptr = ft_strrchr(str, 'L');
	printf("Looking for L, ptr points to %s\n", ptr);
	ptr = ft_strrchr(str, 'r');
	printf("Looking for r, ptr points to %s\n", ptr);
	ptr = ft_strrchr(str, 'i');
	printf("Looking for i, ptr points to %s\n", ptr);
	ptr = ft_strrchr(str, '\0');
	printf("Looking for '\\0', ptr points to %s\n", ptr);
	ptr = ft_strrchr(str, 'X');
	printf("Looking for 'X', ptr points to %s\n", ptr);
	printf("---------------------------\n\n");

}
