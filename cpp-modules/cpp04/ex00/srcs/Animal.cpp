/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 22:48:59 by jrinta-           #+#    #+#             */
/*   Updated: 2025/04/24 13:07:44 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal(): _type("Random Animal")
{
	std::cout << ANIMAL << "default constructor called" << std::endl;
}

Animal::Animal(std::string type): _type(type)
{
	std::cout << ANIMAL << "constructor called" << std::endl;
}

Animal::Animal(const Animal &src): _type(src._type)
{
	std::cout << ANIMAL << "copy constructor called" << std::endl;
}

Animal&	Animal::operator=(const Animal &rhs)
{
	std::cout << ANIMAL << "copy assignment operator called" << std::endl;
	if (this != &rhs)
		_type = rhs._type;
	return (*this);
}

Animal::~Animal()
{
	std::cout << ANIMAL << "destructor called" << std::endl;
}

void	Animal::makeSound() const
{
	std::cout << ANIMAL << "Moo Meow Bark!" << std::endl;
}

const std::string&	Animal::getType() const
{
	return (_type);
}
