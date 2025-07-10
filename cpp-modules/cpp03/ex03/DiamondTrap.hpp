/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:36:16 by jrinta-           #+#    #+#             */
/*   Updated: 2025/04/16 11:44:51 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIAMONDTRAP_HPP
# define DIAMONDTRAP_HPP

# include "FragTrap.hpp"
# include "ScavTrap.hpp"

# define DIAMONDTRAP "\033[0;97m[DiamondTrap]\033[0m "

class DiamondTrap: public FragTrap, public ScavTrap {
	private:
		std::string _name;

	public:
		DiamondTrap();
		DiamondTrap(std::string name);
		DiamondTrap(const DiamondTrap &src);
		~DiamondTrap();
		DiamondTrap& operator=(const DiamondTrap &rhs);

		using	ScavTrap::attack;
		void	whoAmI(void);
};

#endif /* DIAMONDTRAP_HPP */
