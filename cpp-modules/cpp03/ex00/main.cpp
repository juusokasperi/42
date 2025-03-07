/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:30:07 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/06 11:38:15 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

int	main(void)
{
	ClapTrap joe("Joe");
	ClapTrap james("James");

	for (int i = 0; i < 11; i++)
	{
		joe.attack("Test Robot");
		james.takeDamage(1);
	}
	james.beRepaired(10);
	james.takeDamage(10);
	return (0);
}
