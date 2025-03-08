/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 23:04:07 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/08 01:01:48 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat(): Animal("Cat")
{
	std::cout << CAT << "default constructor called" << std::endl;
	_brain = new Brain();
}

Cat::Cat(Cat const &src): Animal(src)
{
	std::cout << CAT << "copy constructor called" << std::endl;
	_brain = new Brain(*src._brain);
}

Cat&	Cat::operator=(Cat const &rhs)
{
	std::cout << CAT << "copy assignment operator called" << std::endl;
	if (this != &rhs)
	{
		Animal::operator=(rhs);
		delete (_brain);
		_brain = new Brain(*rhs._brain);
	}
	return (*this);
}

Cat::~Cat()
{
	std::cout << CAT << "destructor called" << std::endl;
	delete(_brain);
}

void	Cat::makeSound() const
{
	std::cout << CAT << "Meow :)" << std::endl;
}

Brain*	Cat::getBrain() const
{
	return (this->_brain);
}
