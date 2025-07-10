/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:43:50 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/02 15:50:28 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int	main(void)
{
	Zombie	*jake;
	Zombie	*bill;

	jake = newZombie("Jake");
	bill = newZombie("Bill");
	randomChump("Anna");
	randomChump("Joe");
	jake->announce();
	bill->announce();
	delete (jake);
	delete (bill);
	return (0);
}
