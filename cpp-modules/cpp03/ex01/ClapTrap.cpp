/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:03:51 by jrinta-           #+#    #+#             */
/*   Updated: 2025/04/16 11:40:29 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap(): _name("Unnamed"), _hp(10), _energy(10), _damage(0)
{
	std::cout	<< CLAPTRAP << _name << " default constructor has been called" << std::endl;
}

ClapTrap::ClapTrap(std::string const name): _name(name), _hp(10),
								_energy(10), _damage(0)
{
	std::cout	<< CLAPTRAP << _name << " constructor has been called" << std::endl;
}

ClapTrap::ClapTrap(ClapTrap const &src): _name(src._name), _hp(src._hp),
								_energy(src._energy), _damage(src._damage)
{
	std::cout	<< CLAPTRAP << _name << " copy constructor has been called" << std::endl;
}

ClapTrap& ClapTrap::operator=(const ClapTrap &rhs)
{
	std::cout	<< CLAPTRAP << _name << " copy assignment operator has been called" << std::endl;
	if (this != &rhs)
	{
		_name = rhs._name;
		_hp = rhs._hp;
		_energy = rhs._energy;
		_damage = rhs._damage;
	}
	return (*this);
}

ClapTrap::~ClapTrap()
{
	std::cout	<< CLAPTRAP << _name << " destructor has been called" << std::endl;
}

void	ClapTrap::beRepaired(unsigned int amount)
{
	if (_energy == 0)
		std::cout	<< CLAPTRAP << _name << " has no energy to repair itself." << std::endl;
	else
	{
		_energy -= 1;
		_hp += amount;
		std::cout	<< CLAPTRAP << _name << " repairs themselves and has now "
					<< _hp << " hit points!" << std::endl;
	}
}

void	ClapTrap::takeDamage(unsigned int amount)
{
	if (_hp == 0)
	{
		std::cout << CLAPTRAP << _name << " is already dead!" << std::endl;
		return ;
	}
	if (amount > _hp)
		_hp = 0;
	else
		_hp -= amount;
	if (_hp == 0)
		std::cout	<< CLAPTRAP << _name << " takes " << amount
					<< " amount of damage, and is now dead." << std::endl;
	else
		std::cout	<< CLAPTRAP << _name << " takes " << amount
					<< " amount of damage, and has now " << _hp
					<< " hp left." << std::endl;
}

void	ClapTrap::attack(const std::string& target)
{
	if (_hp == 0)
		std::cout	<< CLAPTRAP << _name << " is dead and thus, cannot attack." << std::endl;
	else if (_energy == 0)
		std::cout	<< CLAPTRAP << _name << " has no energy to attack." << std::endl;
	else
	{
		_energy -= 1;
		std::cout	<< CLAPTRAP << _name << " attacks " << target
				<< ", causing " << _damage << " points of damage!" << std::endl;
	}
}
