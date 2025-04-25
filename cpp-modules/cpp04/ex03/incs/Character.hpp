/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:58:59 by jrinta-           #+#    #+#             */
/*   Updated: 2025/04/25 09:37:25 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHARACTER_HPP
# define CHARACTER_HPP

# include "ICharacter.hpp"
# include <iostream>

# define CHARACTER "\033[0;34m[Character]\033[0m "

class Character: public ICharacter {
	private:
		AMateria*	_inventory[4];
		AMateria*	_dropped[50];
		std::string	_name;
		int			_droppedIndex;
		void		drop(AMateria *m);
	public:
		Character();
		Character(std::string name);
		Character(const Character &src);
		Character& operator=(const Character &rhs);
		~Character();

		std::string const	&getName() const;
		void				equip(AMateria *m);
		void				unequip(int idx);
		void				use(int idx, ICharacter &target);
};

#endif /* CHARACTER HPP */
