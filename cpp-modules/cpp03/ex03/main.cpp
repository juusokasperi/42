/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:30:07 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/07 13:49:56 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

int	main(void)
{
	DiamondTrap	bill("Bill");

	for (int i = 0; i < 11; i++)
	{
		bill.attack("Test Robot");
		bill.takeDamage(10);
	}
	bill.highFivesGuys();
	bill.beRepaired(10);
	bill.guardGate();
	bill.whoAmI();
	return (0);
}
