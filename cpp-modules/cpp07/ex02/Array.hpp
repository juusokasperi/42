/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:08:30 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/26 20:08:35 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
# define ARRAY_HPP

# include <iostream>

template<typename T>
class Array {
	private:
		T*				_array;
		unsigned int	_size;
	public:
		Array();
		Array(unsigned int size);
		Array(const Array &src);
		~Array();
		Array& operator=(const Array &rhs);
		Array(Array&& other);
		Array& operator=(Array &&other);

		T& operator[](unsigned int i);
		const T& operator[](unsigned int i) const;

		unsigned int	size() const;

		class OutOfBounds: public std::exception {
			public:
				const char* what() const noexcept;
		};
};

#endif /* ARRAY_HPP */
