/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:30:07 by jrinta-           #+#    #+#             */
/*   Updated: 2025/04/16 11:36:57 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

int	main(void)
{
	ClapTrap joe("Joe");
	ClapTrap james("James");
	ClapTrap unnamed;

	unnamed = joe;
	for (int i = 0; i < 11; i++)
	{
		joe.attack("Test Robot");
		james.takeDamage(1);
	}
	james.beRepaired(10);
	james.takeDamage(10);
	return (0);
}
