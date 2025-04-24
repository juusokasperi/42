/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 23:04:07 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/08 01:04:35 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog(): Animal("Dog")
{
	std::cout << DOG << "default constructor called" << std::endl;
	_brain = new Brain();
}

Dog::Dog(Dog const &src): Animal(src)
{
	std::cout << DOG << "copy constructor called" << std::endl;
	_brain = new Brain(*src._brain);
}

Dog&	Dog::operator=(Dog const &rhs)
{
	std::cout << DOG << "copy assignment operator called" << std::endl;
	if (this != &rhs)
	{
		Animal::operator=(rhs);
		delete (_brain);
		_brain = new Brain(*rhs._brain);
	}
	return (*this);
}

Dog::~Dog()
{
	std::cout << DOG << "destructor called" << std::endl;
	delete(_brain);
}

void	Dog::makeSound() const
{
	std::cout << DOG << "BARK!!!!!!" << std::endl;
}

Brain*	Dog::getBrain() const
{
	return (this->_brain);
}
