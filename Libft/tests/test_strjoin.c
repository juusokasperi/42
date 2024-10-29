/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strjoin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:29:07 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/29 15:35:34 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_strjoin(void)
{
	char str[12] = "TestiString.";
	char str2[8] = "Testing";
	char *strs_joined = ft_strjoin(str, str2);
	printf("---------------------------\n");
	printf("FT_SUBSTR:\n");
	printf("Joining \"%s\" and \"%s\", result is \"%s\"\n", str, str2, strs_joined);
	printf("---------------------------\n\n");
	free(strs_joined);
}
