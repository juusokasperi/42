/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:00:55 by jrinta-           #+#    #+#             */
/*   Updated: 2025/04/16 11:44:38 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

FragTrap::FragTrap(): ClapTrap()
{
	std::cout	<< FRAGTRAP << _name << " default constructor called" << std::endl;
	_hp = 100;
	_energy = 100;
	_damage = 30;
}

FragTrap::FragTrap(std::string name): ClapTrap(name)
{
	std::cout	<< FRAGTRAP << name << " constructor called" << std::endl;
	_hp = 100;
	_energy = 100;
	_damage = 30;
}

FragTrap::~FragTrap()
{
	std::cout	<< FRAGTRAP << _name << " destructor called" << std::endl;
}

FragTrap::FragTrap(FragTrap const &src): ClapTrap(src)
{
	std::cout	<< FRAGTRAP << src._name << " copy constructor called" << std::endl;
}

FragTrap& FragTrap::operator=(FragTrap const &rhs)
{
	std::cout	<< FRAGTRAP << rhs._name << " copy assignment operator called" << std::endl;
	if (this != &rhs)
		ClapTrap::operator=(rhs);
	return (*this);
}

void	FragTrap::highFivesGuys(void)
{
	if (_hp == 0)
		std::cout << FRAGTRAP << _name << " is dead and cannot request a High Five." << std::endl;
	else
		std::cout << FRAGTRAP << _name << " requests a High Five!" << std::endl;
}
