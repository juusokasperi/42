/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:36:02 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/28 22:45:26 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

# include <iostream>

template<typename T>
class MutantStack {
	private:
		T*		_stack;
		size_t	_size;
		size_t	_capacity;
	public:
		typedef T* iterator;

		MutantStack();
		~MutantStack();
		MutantStack(const MutantStack &src);
		MutantStack& operator=(const MutantStack &rhs);
		MutantStack(MutantStack &&other);
		MutantStack& operator=(MutantStack &&other);

		operator	std::stack<T>() const;

		size_t		size() const;
		bool		empty() const;
		T&			top();
		void		push(T N);
		void		pop();
		void		swap(MutantStack &other);

		iterator	begin() const;
		iterator	end() const;
};

#endif /* MUTANTSTACK_HPP */
