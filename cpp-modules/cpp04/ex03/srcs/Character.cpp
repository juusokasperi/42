/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 13:03:08 by jrinta-           #+#    #+#             */
/*   Updated: 2025/04/13 16:55:37 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"

Character::Character(std::string name): _name(name), _droppedIndex(0)
{
	for (int i = 0; i < 4; i++)
	{
		_inventory[i] = NULL;
		_dropped[i] = NULL;
	}
	std::cout << CHARACTER << _name << " created." << std::endl;
}

Character::Character(const Character &src): _name(src._name), _droppedIndex(src._droppedIndex)
{
	for (int i = 0; i < 4; i++)
	{
		if (src._inventory[i])
			_inventory[i] = src._inventory[i]->clone();
		else
			_inventory[i] = NULL;
		if (src._dropped[i])
			_dropped[i] = src._dropped[i]->clone();
		else
			_dropped[i] = NULL;
	}
	std::cout << CHARACTER << _name << " copy constructor called" << std::endl;
}

Character&	Character::operator=(const Character &rhs)
{
	if (this != &rhs)
	{
		for (int i = 0; i < 4; i++)
		{
			delete (_inventory[i]);
			delete (_dropped[i]);
			_dropped[i] = NULL;
			_inventory[i] = NULL;
		}
		_name = rhs._name;
		_droppedIndex = rhs._droppedIndex;
		for (int i = 0; i < 4; i++)
		{
			if (rhs._inventory[i])
				_inventory[i] = rhs._inventory[i]->clone();
			else
				_inventory[i] = NULL;
			if (rhs._dropped[i])
				_dropped[i] = rhs._dropped[i]->clone();
			else
				_dropped[i] = NULL;
		}
	}
	std::cout << CHARACTER << _name << "copy assignment operator" << std::endl;
	return (*this);
}

Character::~Character()
{
	for (int i = 0; i < 4; i++)
	{
		delete (_inventory[i]);
		delete (_dropped[i]);
	}
	std::cout << CHARACTER << _name << " deconstructor called" << std::endl;
}

const std::string&	Character::getName() const
{
	return (_name);
}

void	Character::equip(AMateria *m)
{
	for (int i = 0; i < 4; i++)
	{
		if (_inventory[i] == NULL)
		{
			_inventory[i] = m;
			std::cout << CHARACTER << _name << " equipped " << m->getType() << std::endl;
			return ;
		}
	}
	std::cout << CHARACTER << _name << "'s inventory appears to be full." << std::endl;
}

void	Character::unequip(int idx)
{
	if (idx < 0 || idx > 3)
		std::cout << CHARACTER << "Invalid index number, inventory has slots 0-3" << std::endl;
	else if (_inventory[idx] == NULL)
		std::cout << CHARACTER << "Selected inventory slot is already empty and thus cannot be unequipped." << std::endl;
	else
	{
		drop(_inventory[idx]);
		_inventory[idx] = NULL;
		std::cout << CHARACTER << _name << "'s inventory slot " << idx << " unequipped." << std::endl;
	}
}

void	Character::drop(AMateria *m)
{
	if (_dropped[_droppedIndex] != NULL)
		delete (_dropped[_droppedIndex]);
	_dropped[_droppedIndex] = m;
	_droppedIndex += 1 % 4;
	std::cout << CHARACTER << _name << " dropped " << m->getType() << " on the floor" << std::endl;
}

void	Character::use(int idx, ICharacter &target)
{
	if (idx < 0 || idx > 3)
		std::cout << CHARACTER << "Selected inventory index is out of bounds (0-3)." << std::endl;
	else if (_inventory[idx])
		_inventory[idx]->use(target);
	else
		std::cout << CHARACTER << "Selected inventory index is empty." << std::endl;
}
