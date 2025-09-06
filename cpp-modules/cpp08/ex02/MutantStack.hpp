/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:36:02 by jrinta-           #+#    #+#             */
/*   Updated: 2025/09/05 08:42:14 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

# include <iostream>
# include <stack>

template<typename T>
class MutantStack: public std::stack<T> {
	private:
	public:
		MutantStack();
		~MutantStack();
		MutantStack(const MutantStack &src);
		MutantStack& operator=(const MutantStack &rhs);
		MutantStack(MutantStack &&other);
		MutantStack& operator=(MutantStack &&other);

		typedef typename std::stack<T>::container_type::iterator iterator;
		typedef typename std::stack<T>::container_type::const_iterator const_iterator;
		typedef typename std::stack<T>::container_type::reverse_iterator reverse_iterator;
		typedef typename std::stack<T>::container_type::const_reverse_iterator const_reverse_iterator;
		
		iterator	begin();
		iterator	end();
		
		const_iterator begin() const;
		const_iterator end() const;
		
		reverse_iterator rbegin();
		reverse_iterator rend();
		
		const_reverse_iterator rbegin() const;
		const_reverse_iterator rend() const;
};

# include "MutantStack.tpp"

#endif /* MUTANTSTACK_HPP */
