/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:59:10 by jrinta-           #+#    #+#             */
/*   Updated: 2025/04/13 16:15:53 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP

# include <iostream>

class ClapTrap {
	private:
		std::string		_name;
		unsigned int	_hp;
		unsigned int	_energy;
		unsigned int	_damage;
		ClapTrap();
	public:
		ClapTrap();
		ClapTrap(std::string const name);
		ClapTrap(ClapTrap const &src);
		ClapTrap& operator=(const ClapTrap &rhs);
		~ClapTrap();

		void	attack(const std::string& target);
		void	takeDamage(unsigned int amount);
		void	beRepaired(unsigned int amount);
};

#endif /* CLAPTRAP_HPP */
