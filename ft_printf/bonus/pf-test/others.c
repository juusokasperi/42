/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:44:13 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/26 11:12:25 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	test_others(void)
{
	int	ret;
	int	ret_ft;

	printf("%s--------------------------------------------------\n", KYEL);
	printf("- TESTING PERCENT, INVALID FLAGS, EMPTY FORMAT ETC -\n");
	printf("--------------------------------------------------%s\n", KNRM);

	printf("%s-- All specifiers --\n%s", KCYN, KNRM);
	printf("%s--------------------\n%s", KCYN, KNRM);
	int	i = 5;
	printf("PF:\n");
	ret = printf("%c\t%s\t%p\t%d\t%i\t%u\t%x\t%X\t%%\n", 'A', "Test", &i, 0x28, 0x28, 50, 50);
	printf("FT:\n");
	ret_ft = ft_printf("%c\t%s\t%p\t%d\t%i\t%u\t%x\t%X\t%%\n", 'A', "Test", &i, 0x28, 0x28, 50, 50);
	cmp(ret, ret_ft);

	printf("%s---------------------------------------------------------------\n%s", KCYN, KNRM);
	printf("%sDifferent tests with invalid percent marks in the middle or end\n%s", KCYN, KNRM);
	printf("%s---------------------------------------------------------------\n%s", KCYN, KNRM);
	ret = printf("PF: %7ysa%7");
	printf("\n");
	ret_ft = ft_printf("FT: %7ysa%7");
	ft_printf("\n");
	cmp(ret, ret_ft);

	ret = printf("PF: %7YX%7ysa%7");
	printf("\n");
	ret_ft = ft_printf("FT: %7YX%7ysa%7");
	ft_printf("\n");
	cmp(ret, ret_ft);

	ret = printf("PF: st%Y", 'A');
	printf("\n");
	ret_ft = ft_printf("FT: st%Y", 'A');
	ft_printf("\n");
	cmp(ret, ret_ft);

	ret = printf("PF: %cY%", 'A');
	printf("\n");
	ret_ft = ft_printf("FT: %cY%", 'A');
	ft_printf("\n");
	cmp(ret, ret_ft);

	ret = printf("PF: %Y");
	printf("\n");
	ret_ft = ft_printf("FT: %Y");
	ft_printf("\n");
	cmp(ret, ret_ft);

	ret = printf("PF: %");
	printf("\n");
	ret_ft = ft_printf("FT: %");
	ft_printf("\n");
	cmp(ret, ret_ft);

	ret = printf("PF: %%");
	printf("\n");
	ret_ft = ft_printf("FT: %%");
	ft_printf("\n");
	cmp(ret, ret_ft);

	ret = printf("PF: %k%%%");
	printf("\n");
	ret_ft = ft_printf("FT: %k%%%");
	ft_printf("\n");
	cmp(ret, ret_ft);

	ret = printf("%%\n");
	ret_ft = ft_printf("%%\n");
	cmp(ret, ret_ft);

	ret = printf("%%");
	printf("\n");
	ret_ft = ft_printf("%%");
	printf("\n");
	cmp(ret, ret_ft);

	ret = printf("FT: %Y%%%%%%%");
	printf("\n");
	ret_ft = ft_printf("PF: %Y%%%%%%%");
	printf("\n");
	cmp(ret, ret_ft);

	ret = printf("FT: %%%%%%%");
	printf("\n");
	ret_ft = ft_printf("PF: %%%%%%%");
	printf("\n");
	cmp(ret, ret_ft);

	//Don't match: should print %+7.5YX%7ysa%7 and return 18
	ret = printf("PF: %+7.5YX%7ysa%7");
	printf("\n");
	ret_ft = ft_printf("FT: %+7.5YX%7ysa%7");
	printf("\n");
	cmp(ret, ret_ft);

	//Don't match: should print	%+.5YX%7ysa%7 and return 17
	ret = printf("PF: %+.5YX%7ysa%7");
	printf("\n");
	ret_ft = ft_printf("FT: %+.5YX%7ysa%7");
	printf("\n");
	cmp(ret, ret_ft);

	ret = printf("");
	ret_ft = ft_printf("");
	cmp(ret, ret_ft);

	ret = printf(0);
	ret_ft = ft_printf(0);
	cmp(ret, ret_ft);

	ret = printf("%k");
	printf("\n");
	ret_ft = ft_printf("%k");
	ft_printf("\n");
	cmp(ret, ret_ft);

	ret = printf("PF: adsa%");
	printf("\n");
	ret_ft = ft_printf("FT: adsa%");
	ft_printf("\n");
	cmp(ret, ret_ft);

	printf("%s-----------------------------------------------------------------------------\n%s", KCYN, KNRM);
	printf("%s--- Closing STDOUT which will result in a write error (printf returns -1) ---\n%s", KCYN, KNRM);
	printf("%s-----------------------------------------------------------------------------\n\n%s", KCYN, KNRM);

	int original_stdout = dup(STDOUT_FILENO);
	fclose(stdout);
	ret = printf("test\n");
	ret_ft = ft_printf("test\n");
	stdout = (FILE *)fdopen(original_stdout, "w");
	cmp(ret, ret_ft);

	printf("%s--------------------\n- OTHER  TEST ENDS -\n--------------------\n%s", KYEL, KNRM);
}
