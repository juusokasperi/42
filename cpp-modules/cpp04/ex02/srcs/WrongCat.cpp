/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 23:04:07 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/07 23:21:31 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"

WrongCat::WrongCat(): WrongAnimal("WrongCat")
{
	std::cout << WRONGCAT << "default constructor called" << std::endl;
}

WrongCat::WrongCat(WrongCat const &src): WrongAnimal(src)
{
	std::cout << WRONGCAT << "copy constructor called" << std::endl;
}

WrongCat&	WrongCat::operator=(WrongCat const &rhs)
{
	std::cout << WRONGCAT << "copy assignment operator called" << std::endl;
	if (this != &rhs)
		WrongAnimal::operator=(rhs);
	return (*this);
}

WrongCat::~WrongCat()
{
	std::cout << WRONGCAT << "destructor called" << std::endl;
}

void	WrongCat::makeSound() const
{
	std::cout << WRONGCAT << "Meow :)" << std::endl;
}
