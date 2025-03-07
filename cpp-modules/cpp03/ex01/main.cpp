/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:30:07 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/07 13:32:11 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

int	main(void)
{
	ClapTrap	joe("Joe");
	ClapTrap	james("James");
	ScavTrap	ash("Wrong Name");
	ScavTrap	tmp("Mary");
	ScavTrap	mary = tmp;
	ScavTrap	don("Don");

	ash = ScavTrap("Ash");
	for (int i = 0; i < 11; i++)
	{
		joe.attack("Test Robot");
		ash.attack("Test Robot 2");
		mary.takeDamage(10);
	}
	james.beRepaired(10);
	don.guardGate();
	return (0);
}
