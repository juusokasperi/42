/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:20:02 by jrinta-           #+#    #+#             */
/*   Updated: 2025/09/01 19:14:28 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
# define SPAN_HPP

# include <iostream>
# include <vector>
# include <algorithm>
# include <stdint.h> 

class Span {
	private:
		std::vector<int>	_array;
		unsigned int		_max;
	public:
		Span() = delete;
		Span(unsigned int N);
		Span(const Span &src);
		Span& operator=(const Span &rhs);
		Span(Span &&other);
		Span& operator=(Span &&other);
		~Span();

		void		addNumber(int num);
		void		addRange(uint32_t range);
		template <typename it>
		void		addRange(it begin, it end);
		uint32_t	shortestSpan() const;
		uint32_t	longestSpan() const;
};

template <typename it>
void	Span::addRange(it begin, it end)
{
	std::cout << "AddRange called with range of iterators" << std::endl;
	if (_array.size() + std::distance(begin, end) > _max)
		throw std::runtime_error("Array will exceed maximum capacity with range.");
	_array.insert(_array.end(), begin, end);
}

#endif /* SPAN_HPP */
