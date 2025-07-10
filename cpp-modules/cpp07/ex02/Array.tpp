/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.tpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:26:31 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/27 12:21:24 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"

template<typename T>
Array<T>::Array(): _array(new T[1]), _size(1)
{
	std::cout << "void constructor called" << std::endl;
}

template<typename T>
Array<T>::Array(unsigned int size): _array(new T[size]), _size(size)
{
	std::cout << "constructor called w size " << size << std::endl;
}

template<typename T>
Array<T>::Array(const Array &src): _array(new T[src._size]), _size(src._size)
{
	std::cout << "copy constructor called" << std::endl;

	for (unsigned int i = 0; i < _size; i++)
		_array[i] = src._array[i];
}

template<typename T>
Array<T>::Array(Array&& other)
{
	std::cout << "move constructor called" << std::endl;
	_array = other._array;
	_size = other._size;
	other._array = nullptr;
	other._size = 0;
}

template<typename T>
Array<T>& Array<T>::operator=(Array&& other)
{
	std::cout << "move assignment called" << std::endl;
	if (this != &other)
	{
		delete[] _array;
		_array = other._array;
		_size = other._size;
		other._array = nullptr;
		other._size = 0;
	}
	return (*this);
}

template<typename T>
Array<T>& Array<T>::operator=(const Array &rhs)
{
	std::cout << "copy assignment called" << std::endl;
	if (this != &rhs)
	{
		delete[] (_array);
		_array = new T[rhs._size];
		_size = rhs._size;
		for (unsigned int i = 0; i < _size; i++)
			_array[i] = rhs._array[i];
	}
	return (*this);
}

template<typename T>
Array<T>::~Array()
{
	delete[] (_array);
}

template<typename T>
const T&	Array<T>::operator[](unsigned int i) const
{
	if (i >= _size)
		throw (OutOfBounds());
	return (_array[i]);
}

template<typename T>
T&	Array<T>::operator[](unsigned int i)
{
	if (i >= _size)
		throw (OutOfBounds());
	return (_array[i]);
}

template<typename T>
unsigned int	Array<T>::size(void) const
{
	return (_size);
}

template<typename T>
const char *Array<T>::OutOfBounds::what() const noexcept
{
	return "Index out of bounds";
}
