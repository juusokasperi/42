/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:00:55 by jrinta-           #+#    #+#             */
/*   Updated: 2025/04/16 11:48:45 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap()
	: ClapTrap("Unnamed_clap_name"), FragTrap("Unnamed"), ScavTrap("Unnamed"), _name("Unnamed")
{
	std::cout	<< DIAMONDTRAP << _name << " default constructor called" << std::endl;
	FragTrap::_hp = 100;
	ScavTrap::_energy = 50;
	FragTrap::_damage = 30;
}

DiamondTrap::DiamondTrap(std::string name)
	: ClapTrap(name + "_clap_name"), FragTrap(name), ScavTrap(name), _name(name)
{
	std::cout	<< DIAMONDTRAP << name << " constructor called" << std::endl;
	FragTrap::_hp = 100;
	ScavTrap::_energy = 50;
	FragTrap::_damage = 30;
}

DiamondTrap::~DiamondTrap()
{
	std::cout	<< DIAMONDTRAP << _name << " destructor called" << std::endl;
}

DiamondTrap::DiamondTrap(DiamondTrap const &src)
	: ClapTrap(src), FragTrap(src), ScavTrap(src), _name(src._name)
{
	std::cout	<< DIAMONDTRAP << src._name << " copy constructor called" << std::endl;
	_hp = src._hp;
	_energy = src._energy;
	_damage = src._damage;
}

DiamondTrap& DiamondTrap::operator=(DiamondTrap const &rhs)
{
	std::cout	<< DIAMONDTRAP << rhs._name << " copy assignment operator called" << std::endl;
	if (this != &rhs)
	{
		ClapTrap::operator=(rhs);
		FragTrap::operator=(rhs);
		ScavTrap::operator=(rhs);
		_name = rhs._name;
		_hp = rhs._hp;
		_energy = rhs._energy;
		_damage = rhs._damage;
	}
	return (*this);
}

void	DiamondTrap::whoAmI(void)
{
	std::cout	<< DIAMONDTRAP << "Name is: \"" << _name << "\" "
				<< "and ClapTrap name is: \"" << ClapTrap::_name
				<< "\"" << std::endl;
}
