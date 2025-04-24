/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 22:48:59 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/07 23:20:06 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal(): _type("Random WrongAnimal")
{
	std::cout << WRONGANIMAL << "default constructor called" << std::endl;
}

WrongAnimal::WrongAnimal(std::string type): _type(type)
{
	std::cout << WRONGANIMAL << "constructor called" << std::endl;
}
WrongAnimal::WrongAnimal(const WrongAnimal &src): _type(src._type)
{
	std::cout << WRONGANIMAL << "copy constructor called" << std::endl;
}

WrongAnimal&	WrongAnimal::operator=(const WrongAnimal &rhs)
{
	std::cout << WRONGANIMAL << "copy assignment operator called" << std::endl;
	if (this != &rhs)
		_type = rhs._type;
	return (*this);
}

WrongAnimal::~WrongAnimal()
{
	std::cout << WRONGANIMAL << "destructor called" << std::endl;
}

void	WrongAnimal::makeSound() const
{
	std::cout << WRONGANIMAL << "Moo Meow Bark!" << std::endl;
}

const std::string&	WrongAnimal::getType() const
{
	return (_type);
}
