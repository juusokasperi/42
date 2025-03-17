/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:08:14 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/17 12:55:38 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

/* ************ */
/* Constructors */
/* ************ */

Fixed::Fixed() : _value(0)
{
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const int value): _value(value << _fractionalBits)
{
	std::cout << "Int constructor called" << std::endl;
}

Fixed::Fixed(const float value): _value(static_cast<int>(roundf(value * (1 << _fractionalBits))))
{
	std::cout << "Float constructor called" << std::endl;
}

/* Copy constructor */
Fixed::Fixed(const Fixed &src): _value(src._value)
{
	std::cout << "Copy constructor called" << std::endl;
}

/* **************************** */
/* Assignment operator overload */
/* **************************** */

/* Copy assignment operator */
Fixed& Fixed::operator=(const Fixed &rhs)
{
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &rhs)
		this->_value = rhs._value;
	return (*this);
}

/* Destructor */
Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
}

const int&	Fixed::getRawBits(void) const
{
	std::cout << "getRawBits member function called" << std::endl;
	return (_value);
}

void	Fixed::setRawBits(int raw)
{
	_value = raw;
}

float	Fixed::toFloat(void) const
{
	return (static_cast<float>(_value) / (1 << _fractionalBits));
}

int	Fixed::toInt(void) const
{
	return (_value >> _fractionalBits);
}

/* ****************** */
/* Operator overloads */
/* ****************** */

bool	Fixed::operator>(const Fixed &rhs) const
{
	return (this->_value > rhs._value);
}

bool	Fixed::operator<(const Fixed &rhs) const
{
	return (this->_value < rhs._value);
}

bool	Fixed::operator>=(const Fixed &rhs) const
{
	return (this->_value >= rhs._value);
}

bool	Fixed::operator<=(const Fixed &rhs) const
{
	return (this->_value <= rhs._value);
}

bool	Fixed::operator==(const Fixed &rhs) const
{
	return (this->_value == rhs._value);
}

bool	Fixed::operator!=(const Fixed &rhs) const
{
	return (this->_value != rhs._value);
}

/* ********************* */
/* Arithmetic operations */
/* ********************* */

Fixed	Fixed::operator+(const Fixed &rhs) const
{
	Fixed	dest;

	dest._value = _value + rhs._value;
	return (dest);
}

Fixed	Fixed::operator-(const Fixed &rhs) const
{
	Fixed	dest;

	dest._value = _value - rhs._value;
	return (dest);
}

Fixed	Fixed::operator*(const Fixed &rhs) const
{
	Fixed		dest;
	long long	result;

	result = (static_cast<long long>(_value) * rhs._value) >> _fractionalBits;
	dest._value = static_cast<int>(result);
	return (dest);
}

Fixed	Fixed::operator/(const Fixed &rhs) const
{
	Fixed		dest;
	long long	result;

	try
	{
		if (rhs._value == 0)
			throw ("Division by zero not allowed.");
		result = (static_cast<long long>(_value) << _fractionalBits) / rhs._value;
		dest._value = result;
		return (dest);
	}
	catch (const char *errorMessage)
	{
		std::cerr << "Error: " << errorMessage << std::endl;
		std::exit(EXIT_FAILURE);
	}
}

/* **************************** */
/* Pre/post increment/decrement */
/* **************************** */

Fixed&	Fixed::operator++()
{
	_value++;
	return (*this);
}

Fixed	Fixed::operator++(int)
{
	Fixed	temp(*this);

	_value++;
	return (temp);
}

Fixed&	Fixed::operator--()
{
	_value--;
	return (*this);
}

Fixed	Fixed::operator--(int)
{
	Fixed temp(*this);

	_value--;
	return (temp);
}

Fixed&	Fixed::min(Fixed &a, Fixed &b)
{
	return (a._value <= b._value) ? a : b;
}

const Fixed&	Fixed::min(const Fixed &a, const Fixed &b)
{
	return (a._value <= b._value) ? a : b;
}

Fixed&	Fixed::max(Fixed &a, Fixed &b)
{
	return (a._value >= b._value) ? a : b;
}

const Fixed&	Fixed::max(const Fixed &a, const Fixed &b)
{
	return (a._value >= b._value) ? a : b;
}

std::ostream& operator<<(std::ostream &os, const Fixed& fixed)
{
	os << fixed.toFloat();
	return (os);
}
