/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:08:14 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/03 18:07:38 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

//	Constructor
Fixed::Fixed() : _value(0)
{
	std::cout << "Default constructor called" << std::endl;
}

//	Copy constructor
Fixed::Fixed(const Fixed &src)
{
	std::cout << "Copy constructor called" << std::endl;
	*this = src;
}

//	Copy assignment operator overload
Fixed& Fixed::operator=(const Fixed &rhs)
{
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &rhs)
		this->setRawBits(rhs.getRawBits());
	return (*this);
}

//	Move constructor
Fixed::Fixed(Fixed &&other) noexcept: _value(other._value)
{
	std::cout << "Move constructor called" << std::endl;
	other.setRawBits(0);
}

//	Move assignment operator overload
Fixed& Fixed::operator=(Fixed&& rhs) noexcept
{
	std::cout << "Move assignment operator called" << std::endl;
	if (this != &rhs)
	{
		_value = rhs.getRawBits();
		rhs.setRawBits(0);
	}
	return (*this);
}

Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
}

const int&	Fixed::getRawBits(void) const
{
	std::cout << "getRawBits member function called" << std::endl;
	return (_value);
}

void		Fixed::setRawBits(int raw)
{
	_value = raw;
}
