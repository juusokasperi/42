/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:25:27 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/27 15:24:27 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

Span::Span(unsigned int N): _max(N)
{
	std::cout << "Default constructor called" << std::endl;
	_array.reserve(_max);
}

Span::Span(const Span &src): _array(src._array), _max(src._max)
{
	std::cout << "Copy constructor called" << std::endl;
}

Span&	Span::operator=(const Span &rhs)
{
	std::cout << "Copy assignment called" << std::endl;
	if (this != &rhs)
	{
		_array = rhs._array;
		_max = rhs._max;
	}
	return (*this);
}

Span::Span(Span &&other): _array(std::move(other._array)), _max(other._max)
{
	std::cout << "Move constructor called" << std::endl;
	_max = other._max;
}

Span&	Span::operator=(Span &&other)
{
	std::cout << "Move assignment called" << std::endl;
	if (this != &other)
	{
		_array = std::move(other._array);
		_max = other._max;
		other._max = 0;
	}
	return (*this);
}

Span::~Span()
{
	std::cout << "Destructor called" << std::endl;
}

void	Span::addNumber(int num)
{
	std::cout << "AddNumber called" << std::endl;
	if (_array.size() >= _max)
		throw std::runtime_error("Array at maximum capacity.");
	_array.push_back(num);
}

void	Span::addRange(uint32_t range)
{
	std::cout << "AddRange called with range integer" << std::endl;
	if (_array.size() + range > _max)
		throw std::runtime_error("Array will exceed maximum capacity with range.");
	for	(uint32_t i = 1; i <= range; ++i)
		_array.push_back(i);
}

uint32_t	Span::shortestSpan() const
{
	std::cout << "ShortestSpan called" << std::endl;
	if (_array.size() < 2)
		throw std::runtime_error("Array must have at least 2 values to determine span.");
	std::vector<int> sorted_array = _array;
	std::sort(sorted_array.begin(), sorted_array.end());
	uint32_t shortestSpan = std::abs(sorted_array[1] - sorted_array[0]);
	for (size_t i = 1; i < sorted_array.size() - 1; ++i)
	{
		uint32_t diff = std::abs(sorted_array[i + i] - sorted_array[i]);
		if (diff < shortestSpan)
			shortestSpan = diff;
	}
	return (shortestSpan);
}

uint32_t	Span::longestSpan() const
{
	std::cout << "LongestSpan called" << std::endl;
	if (_array.size() < 2)
		throw std::runtime_error("Array must have at least 2 values to determine span.");
	auto min_it = std::min_element(_array.begin(), _array.end());
	auto max_it = std::max_element(_array.begin(), _array.end());
	return static_cast<uint32_t>(*max_it - *min_it);
}
