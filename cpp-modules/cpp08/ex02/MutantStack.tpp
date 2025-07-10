/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.tpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:27:05 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/28 22:46:39 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"

template <typename T>
MutantStack<T>::MutantStack(): _stack(nullptr), _size(0), _capacity(0)
{
	std::cout << "Default constructor called" << std::endl;
}

template <typename T>
MutantStack<T>::~MutantStack()
{
	std::cout << "Destructor called" << std::endl;
	delete [] _stack;
}

template <typename T>
MutantStack<T>::MutantStack(const MutantStack &src): _size(src._size), _capacity(src._capacity)
{
	std::cout << "Copy constructor called" << std::endl;
	_stack = new T[_capacity];
	std::copy(src._stack, src._stack + _size, _stack);
}

template <typename T>
MutantStack<T>& MutantStack<T>::operator=(const MutantStack &rhs)
{
	std::cout << "Copy assignment called" << std::endl;
	if (this != &rhs)
	{
		delete[] _stack;
		_stack = new T[rhs._capacity];
		std::copy(rhs._stack, rhs._stack + rhs._size, _stack);
		_size = rhs._size;
		_capacity = rhs._capacity;
	}
	return (*this);
}

template <typename T>
MutantStack<T>::MutantStack(MutantStack &&other): _stack(other._stack), _size(other._size), _capacity(other._capacity)
{
	std::cout << "Move constructor called" << std::endl;
	other._stack = nullptr;
	other._size = 0;
	other._capacity = 0;
}

template <typename T>
MutantStack<T>& MutantStack<T>::operator=(MutantStack &&other)
{
	if (this != &other)
	{
		delete[] _stack;
		_stack = other._stack;
		_size = other._size;
		_capacity = other._capacity;
		other._stack = nullptr;
		other._size = 0;
		other._capacity = 0;
	}
	return (*this);
}

/*
	Member functions
*/

template <typename T>
size_t	MutantStack<T>::size() const
{
	return (_size);
}

template <typename T>
bool	MutantStack<T>::empty() const
{
	return (_size == 0 ? true : false);
}

template <typename T>
T&	MutantStack<T>::top()
{
	if (_size == 0)
		throw std::out_of_range("Cannot access top, stack is empty.");
	return (_stack[_size - 1]);
}

template <typename T>
void	MutantStack<T>::push(T N)
{
	if (_size == _capacity)
	{
		if (_capacity == 0)
			_capacity = 1;
		else
			_capacity *= 2;
		T*	tmp = new T[_capacity];
		for	(size_t i = 0; i < _size; ++i)
			tmp[i] = _stack[i];
		delete[] _stack;
		_stack = tmp;
	}
	_stack[_size] = N;
	_size += 1;
}

template <typename T>
void	MutantStack<T>::pop()
{
	_stack[_size - 1] = 0;
	_size -= 1;
}

template <typename T>
void	MutantStack<T>::swap(MutantStack<T> &other)
{
	std::swap(_stack, other._stack);
	std::swap(_size, other._size);
	std::swap(_capacity, other._capacity);
}

template<typename T>
typename MutantStack<T>::iterator	MutantStack<T>::begin() const
{
	return (_stack);
}

template<typename T>
typename MutantStack<T>::iterator	MutantStack<T>::end() const
{
	return (_stack + _size);
}

template<typename T>
MutantStack<T>::operator std::stack<T>() const
{
	std::stack<T>	result;
	for (size_t i = 0; i < _size; ++i)
		result.push(_stack[i]);
	return (result);
}
