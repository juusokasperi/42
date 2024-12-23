/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strjoin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:29:07 by jrinta-           #+#    #+#             */
/*   Updated: 2024/11/06 18:38:33 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_strjoin(void)
{
	char str[12] = "TestiString.";
	char str2[8] = "Testing";
	printf("---------------------------\n");
	printf("FT_SUBSTR:\n");
	char *strs_joined = ft_strjoin(str, str2);
	printf("Joining \"%s\" and \"%s\", result is \"%s\"\n", str, str2, strs_joined);
	free(strs_joined);
	strs_joined = ft_strjoin("", "");
	printf("Joining \"%s\" and \"%s\", result is \"%s\"\n", "", "", strs_joined);
	free(strs_joined);
	strs_joined = ft_strjoin("", "String2");
	printf("Joining \"\" and \"String2\", result is \"%s\"\n", strs_joined);
	free(strs_joined);
	strs_joined = ft_strjoin("String1", "");
	printf("Joining \"String1\" and \"\", result is \"%s\"\n", strs_joined);
	free(strs_joined);
	strs_joined = ft_strjoin("\tOne\t", "Two\tThree\tThree.1\nFour");
	printf("Joining \"\tOne\t\" and \"Two\tThree\tThree.1\nFour\", result is:\n\"%s\"\n", strs_joined);
	free(strs_joined);
	printf("---------------------------\n\n");
}
