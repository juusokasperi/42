/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAnimal.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 22:48:59 by jrinta-           #+#    #+#             */
/*   Updated: 2025/04/13 16:42:20 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AAnimal.hpp"

AAnimal::AAnimal(): _type("Random Animal")
{
	std::cout << AANIMAL << "default constructor called" << std::endl;
}

AAnimal::AAnimal(std::string type): _type(type)
{
	std::cout << AANIMAL << "constructor called" << std::endl;
}
AAnimal::AAnimal(const AAnimal &src): _type(src._type)
{
	std::cout << AANIMAL << "copy constructor called" << std::endl;
}

AAnimal&	AAnimal::operator=(const AAnimal &rhs)
{
	std::cout << AANIMAL << "copy assignment operator called" << std::endl;
	if (this != &rhs)
		_type = rhs._type;
	return (*this);
}

AAnimal::~AAnimal()
{
	std::cout << AANIMAL << "destructor called" << std::endl;
}

void	AAnimal::makeSound() const
{
	std::cout << AANIMAL << "Moo Meow Bark!" << std::endl;
}

const std::string&	AAnimal::getType() const
{
	return (_type);
}
