/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:57:40 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/07 13:45:45 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCAVTRAP_HPP
# define SCAVTRAP_HPP

# include "ClapTrap.hpp"

# define SCAVTRAP "\033[95m[ScavTrap]\033[0m "

class ScavTrap: virtual public ClapTrap {
	private:
		ScavTrap();
	public:
		ScavTrap(std::string name);
		ScavTrap(ScavTrap const &src);
		~ScavTrap();
		ScavTrap& operator=(ScavTrap const &rhs);

		void	attack(const std::string &target);
		void	guardGate();
};

#endif /* SCAVTRAP_HPP */
