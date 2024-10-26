/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:04:36 by jrinta-           #+#    #+#             */
/*   Updated: 2024/10/26 18:04:43 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_putstr(char *str);

int	main(int argc, char **argv)
{
	if (argc != 2)
		ft_putstr("Usage: ./a.out \"String to print\".\n");
	else
		ft_putstr(argv[1]);
	return (0);
}
