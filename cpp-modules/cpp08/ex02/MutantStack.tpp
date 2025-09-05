/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.tpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:27:05 by jrinta-           #+#    #+#             */
/*   Updated: 2025/09/05 08:52:52 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"

template <typename T>
MutantStack<T>::MutantStack(): std::stack<T>() {}

template <typename T>
MutantStack<T>::~MutantStack() {}

template <typename T>
MutantStack<T>::MutantStack(const MutantStack &src): std::stack<T>(src) {}

template <typename T>
MutantStack<T>& MutantStack<T>::operator=(const MutantStack &rhs)
{
	if (this != &rhs)
		std::stack<T>::operator=(rhs);
	return (*this);
}

template <typename T>
MutantStack<T>::MutantStack(MutantStack &&other): std::stack<T>(std::move(other)) {}

template <typename T>
MutantStack<T>& MutantStack<T>::operator=(MutantStack &&other)
{
	if (this != &other)
		std::stack<T>::operator=(std::move(other));
	return (*this);
}

/*
	Iterators
*/

template<typename T>
typename MutantStack<T>::iterator	MutantStack<T>::begin()
{
	return (std::stack<T>::c.begin());
}

template<typename T>
typename MutantStack<T>::iterator	MutantStack<T>::end()
{
	return (std::stack<T>::c.end());
}

template<typename T>
typename MutantStack<T>::const_iterator	MutantStack<T>::begin() const
{
	return (std::stack<T>::c.begin());
}

template<typename T>
typename MutantStack<T>::const_iterator	MutantStack<T>::end() const
{
	return (std::stack<T>::c.end());
}

template<typename T>
typename MutantStack<T>::reverse_iterator	MutantStack<T>::rbegin()
{
	return (std::stack<T>::c.rbegin());
}

template<typename T>
typename MutantStack<T>::reverse_iterator	MutantStack<T>::rend()
{
	return (std::stack<T>::c.rend());
}

template<typename T>
typename MutantStack<T>::const_reverse_iterator	MutantStack<T>::rbegin() const
{
	return (std::stack<T>::c.rbegin());
}

template<typename T>
typename MutantStack<T>::const_reverse_iterator	MutantStack<T>::rend() const
{
	return (std::stack<T>::c.rend());
}
