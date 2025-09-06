/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:25:27 by jrinta-           #+#    #+#             */
/*   Updated: 2025/09/05 09:43:50 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

Span::Span(unsigned int N): _max(N) { _array.reserve(_max); }
Span::Span(const Span &src): _array(src._array), _max(src._max) {}

Span&	Span::operator=(const Span &rhs)
{
	if (this != &rhs)
	{
		_array = rhs._array;
		_max = rhs._max;
	}
	return (*this);
}

Span::Span(Span &&other): _array(std::move(other._array)), _max(other._max) { _max = other._max; }

Span&	Span::operator=(Span &&other)
{
	if (this != &other)
	{
		_array = std::move(other._array);
		_max = other._max;
		other._max = 0;
	}
	return (*this);
}

Span::~Span() {}

void	Span::addNumber(int num)
{
	if (_array.size() >= _max)
		throw ArrayCapacityFullException();
	_array.push_back(num);
}

void	Span::addRange(uint32_t range)
{
	if (_array.size() + range > _max)
		throw ArrayRangeExceedsCapacityException();
	for	(uint32_t i = 1; i <= range; ++i)
		_array.push_back(i);
}

uint32_t	Span::shortestSpan() const
{
	if (_array.size() < 2)
		throw NotEnoughElementsException();
	std::vector<int> sorted_array = _array;
	std::sort(sorted_array.begin(), sorted_array.end());
	std::vector<int> spans(sorted_array.size() - 1);
	std::adjacent_difference(sorted_array.begin(), sorted_array.end(), spans.begin());
	std::vector<int>::iterator minimumSpanIt = std::min_element(spans.begin() + 1, spans.end());
	return static_cast<uint32_t>(std::abs(*minimumSpanIt));
}

uint32_t	Span::longestSpan() const
{
	if (_array.size() < 2)
		throw NotEnoughElementsException();
	auto min_it = std::min_element(_array.begin(), _array.end());
	auto max_it = std::max_element(_array.begin(), _array.end());
	return static_cast<uint32_t>(*max_it - *min_it);
}

const char *Span::NotEnoughElementsException::what() const noexcept
{
	return ("Array must have at least 2 values to determine span.");
}

const char *Span::ArrayCapacityFullException::what() const noexcept
{
	return ("Array at maximum capacity.");
}

const char *Span::ArrayRangeExceedsCapacityException::what() const noexcept
{
	return ("Array will exceed maximum capacity with supplied range.");
}