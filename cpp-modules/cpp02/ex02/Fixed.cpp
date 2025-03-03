/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:08:14 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/03 23:54:12 by jrinta-          ###   ########.fr       */
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
Fixed::Fixed(const Fixed &src)
{
	std::cout << "Copy constructor called" << std::endl;
	*this = src;
}

/* Move constructor */
Fixed::Fixed(Fixed &&other) noexcept: _value(other._value)
{
	std::cout << "Move constructor called" << std::endl;
	other._value = 0;
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

/* Move assignment operator */
Fixed& Fixed::operator=(Fixed&& rhs) noexcept
{
	std::cout << "Move assignment operator called" << std::endl;
	if (this != &rhs)
	{
		_value = rhs._value;
		rhs._value = 0;
	}
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

	dest.setRawBits(_value + rhs.getRawBits());
	return (dest);
}

Fixed	Fixed::operator-(const Fixed &rhs) const
{
	Fixed	dest;

	dest.setRawBits(_value - rhs.getRawBits());
	return (dest);
}

Fixed	Fixed::operator*(const Fixed &rhs) const
{
	Fixed		dest;
	long long	result;

	result = (static_cast<long long>(_value) * rhs.getRawBits()) >> _fractionalBits;
	dest.setRawBits(static_cast<int>(result));
	return (dest);
}

Fixed	Fixed::operator/(const Fixed &rhs) const
{
	Fixed		dest;
	long long	result;

	if (rhs.getRawBits() == 0)
	{
		std::cerr << "Error: Division by zero" << std::endl;
		dest.setRawBits(0);
		return (dest);
	}
	result = (static_cast<long long>(_value) << _fractionalBits) / rhs.getRawBits();
	dest.setRawBits(result);
	return (dest);
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
	return (a.getRawBits() <= b.getRawBits()) ? a : b;
}

const Fixed&	Fixed::min(const Fixed &a, const Fixed &b)
{
	return (a.getRawBits() <= b.getRawBits()) ? a : b;
}

Fixed&	Fixed::max(Fixed &a, Fixed &b)
{
	return (a.getRawBits() >= b.getRawBits()) ? a : b;
}

const Fixed&	Fixed::max(const Fixed &a, const Fixed &b)
{
	return (a.getRawBits() >= b.getRawBits()) ? a : b;
}

std::ostream& operator<<(std::ostream &os, const Fixed& fixed)
{
	os << fixed.toFloat();
	return (os);
}
