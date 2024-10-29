/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strncmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:34:38 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/29 14:35:50 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_strncmp(void)
{
	char strncmp1[20] = "TestiString.";
	char strncmp2[20] = "TestiBring.";
	printf("---------------------------\n");
	printf("FT_STRNCMP:\n");
	printf("\"%s\" and \"%s\" to strncmp, length of 5 and 10\n", strncmp1, strncmp2);
	printf("%i\n", ft_strncmp(strncmp1, strncmp2, 5));
	printf("%i\n", ft_strncmp(strncmp1, strncmp2, 10));
	printf("---------------------------\n\n");
}
