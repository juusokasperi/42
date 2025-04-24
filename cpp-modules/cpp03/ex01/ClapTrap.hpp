/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:59:10 by jrinta-           #+#    #+#             */
/*   Updated: 2025/04/16 11:40:03 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP

# include <iostream>

# define CLAPTRAP "\033[93m[ClapTrap]\033[0m "

class ClapTrap {
	protected:
		std::string		_name;
		unsigned int	_hp;
		unsigned int	_energy;
		unsigned int	_damage;
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
