/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strchr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:27:54 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/29 14:31:38 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_strchr(void)
{
	char str[] = "Test String With Letter Y";
	char *ptr;

	printf("---------------------------\n");
	printf("FT_STRCHR:\n");
	ptr = ft_strchr(str, 'Y');
	printf("Looking for Y, ptr points to %s\n", ptr);
	ptr = ft_strchr(str, 'L');
	printf("Looking for L, ptr points to %s\n", ptr);
	ptr = ft_strchr(str, 'r');
	printf("Looking for r, ptr points to %s\n", ptr);
	ptr = ft_strchr(str, '\0');
	printf("Looking for '\\0', ptr points to %s\n", ptr);
	ptr = ft_strchr(str, 'X');
	printf("Looking for 'X', ptr points to %s\n", ptr);
	printf("---------------------------\n\n");

}
