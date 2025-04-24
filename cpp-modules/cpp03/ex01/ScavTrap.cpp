/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:00:55 by jrinta-           #+#    #+#             */
/*   Updated: 2025/04/16 11:42:48 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

ScavTrap::ScavTrap(): ClapTrap()
{
	std::cout	<< SCAVTRAP << _name << " default constructor called" << std::endl;
	_hp = 100;
	_energy = 50;
	_damage = 20;
}

ScavTrap::ScavTrap(std::string name): ClapTrap(name)
{
	std::cout	<< SCAVTRAP << name << " constructor called" << std::endl;
	_hp = 100;
	_energy = 50;
	_damage = 20;
}

ScavTrap::~ScavTrap()
{
	std::cout	<< SCAVTRAP << _name << " destructor called" << std::endl;
}

ScavTrap::ScavTrap(ScavTrap const &src): ClapTrap(src)
{
	std::cout	<< SCAVTRAP << src._name << " copy constructor called" << std::endl;
}

ScavTrap& ScavTrap::operator=(ScavTrap const &rhs)
{
	std::cout	<< SCAVTRAP << rhs._name << " copy assignment operator called" << std::endl;
	if (this != &rhs)
		ClapTrap::operator=(rhs);
	return (*this);
}

void	ScavTrap::attack(const std::string &target)
{
	if (_hp == 0)
		std::cout	<< SCAVTRAP << _name << " is dead and thus, cannot attack." << std::endl;
	else if (_energy == 0)
		std::cout	<< SCAVTRAP << _name << " has no energy to attack." << std::endl;
	else
	{
		_energy -= 1;
		std::cout	<< SCAVTRAP << _name << " attacks " << target
					<< ", causing " << _damage << " points of damage!" << std::endl;
	}
}

void	ScavTrap::guardGate()
{
	if (_hp == 0)
		std::cout	<< SCAVTRAP << _name << " is dead and cannot guard the gate." << std::endl;
	else
		std::cout	<< SCAVTRAP << _name << " is now in [Gate Keeper Mode]" << std::endl;
}
