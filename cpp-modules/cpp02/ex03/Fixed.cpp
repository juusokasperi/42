/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:08:14 by jrinta-           #+#    #+#             */
/*   Updated: 2025/04/14 16:24:55 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

/* ************ */
/* Constructors */
/* ************ */

Fixed::Fixed() : _value(0)
{
//	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const int value)
{
//	std::cout << "Int constructor called" << std::endl;
	if (value > FIXED_INT_MAX || value < FIXED_INT_MIN)
		throw std::overflow_error("Int value out of range.");
	_value = value << _fractionalBits;
}

Fixed::Fixed(const float value)
{
//	std::cout << "Float constructor called" << std::endl;
	if (value > FIXED_FLOAT_MAX || value < FIXED_FLOAT_MIN)
		throw std::overflow_error("Float value out of range.");
	_value = static_cast<int>(roundf(value * (1 << _fractionalBits)));
}

/* Copy constructor */
Fixed::Fixed(const Fixed &src): _value(src._value)
{
//	std::cout << "Copy constructor called" << std::endl;
}

/* **************************** */
/* Assignment operator overload */
/* **************************** */

/* Copy assignment operator */
Fixed& Fixed::operator=(const Fixed &rhs)
{
//	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &rhs)
		this->_value = rhs._value;
	return (*this);
}

/* Destructor */
Fixed::~Fixed()
{
//	std::cout << "Destructor called" << std::endl;
}

int	Fixed::getRawBits(void) const
{
//	std::cout << "getRawBits member function called" << std::endl;
	return (_value);
}

void	Fixed::setRawBits(int raw)
{
//	std::cout << "setRawBits member function called" << std::endl;
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

	if ((_value > 0 && rhs._value > std::numeric_limits<int>::max() - _value)
		|| (_value < 0 && rhs._value < std::numeric_limits<int>::min() - _value))
		throw std::overflow_error("Addition overflow.");
	dest._value = _value + rhs._value;
	return (dest);
}

Fixed	Fixed::operator-(const Fixed &rhs) const
{
	Fixed	dest;

	if ((_value < 0 && rhs._value > std::numeric_limits<int>::max() + _value)
		|| (_value > 0 && rhs._value < std::numeric_limits<int>::min() + _value))
		throw std::overflow_error("Substraction overflow.");
	dest._value = _value - rhs._value;
	return (dest);
}

static bool multiplicationOverflows(int l, int r)
{
	if (l > 0 && r > 0 && l > std::numeric_limits<long long>::max() / r)
		return (true);
	if (l < 0 && r < 0 && l < std::numeric_limits<long long>::max() / r)
		return (true);
	if (l < 0 & r > 0 && l < std::numeric_limits<long long>::min() / r)
		return (true);
	if (l > 0 && r < 0 && r < std::numeric_limits<long long>::min() / l)
		return (true);
	return (false);
}

Fixed	Fixed::operator*(const Fixed &rhs) const
{
	Fixed		dest;
	long long	result;

	if (_value == 0 || rhs._value == 0)
		dest._value = 0;
	else {
		if (multiplicationOverflows(_value, rhs._value))
			throw std::overflow_error("Multiplication overflow.");
		result = (static_cast<long long>(_value) * rhs._value) >> _fractionalBits;
		if (result > std::numeric_limits<int>::max() || result < std::numeric_limits<int>::min())
			throw std::overflow_error("Multiplication overflow.");
		dest._value = static_cast<int>(result);
	}
	return (dest);
}

Fixed	Fixed::operator/(const Fixed &rhs) const
{
	Fixed		dest;
	long long	result;

	if (rhs._value == 0)
		throw std::runtime_error("Division by zero not allowed.");
	if (_value == std::numeric_limits<int>::min() && rhs._value == -1)
		throw std::overflow_error("Division overflow.");
	if (_value != 0 && std::abs(static_cast<long long>(_value)) > (std::numeric_limits<long long>::max() >> _fractionalBits))
		throw std::overflow_error("Left shift overflow in division.");
	result = (static_cast<long long>(_value) << _fractionalBits) / rhs._value;
	if (result > std::numeric_limits<int>::max() || result < std::numeric_limits<int>::min())
		throw std::overflow_error("Division result overflow.");
	dest._value = result;
	return (dest);
}

/* **************************** */
/* Pre/post increment/decrement */
/* **************************** */

Fixed&	Fixed::operator++()
{
	if (_value >= (FIXED_INT_MAX << _fractionalBits))
		throw std::overflow_error("Increment results in an overflow.");
	_value++;
	return (*this);
}

Fixed	Fixed::operator++(int)
{
	Fixed	temp(*this);

	if (_value >= (FIXED_INT_MAX << _fractionalBits))
		throw std::overflow_error("Increment results in an overflow.");
	_value++;
	return (temp);
}

Fixed&	Fixed::operator--()
{
	if (_value <= (FIXED_INT_MIN * (1 << _fractionalBits)))
		throw std::overflow_error("Decrement results in an overflow.");
	_value--;
	return (*this);
}

Fixed	Fixed::operator--(int)
{
	Fixed temp(*this);

	if (_value <= (FIXED_INT_MIN * (1 << _fractionalBits)))
		throw std::overflow_error("Decrement results in an overflow.");
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
