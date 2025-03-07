/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 23:04:07 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/07 23:21:37 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog(): Animal("Dog")
{
	std::cout << DOG << "default constructor called" << std::endl;
}

Dog::Dog(Dog const &src): Animal(src)
{
	std::cout << DOG << "copy constructor called" << std::endl;
}

Dog&	Dog::operator=(Dog const &rhs)
{
	std::cout << DOG << "copy assignment operator called" << std::endl;
	if (this != &rhs)
		Animal::operator=(rhs);
	return (*this);
}

Dog::~Dog()
{
	std::cout << DOG << "destructor called" << std::endl;
}

void	Dog::makeSound() const
{
	std::cout << DOG << "BARK!!!!!!" << std::endl;
}
