/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:57:40 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/07 13:33:28 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAGTRAP_HPP
# define FRAGTRAP_HPP

# include "ClapTrap.hpp"

# define FRAGTRAP "\033[98m[FragTrap]\033[0m "

class FragTrap: public ClapTrap {
	private:
		FragTrap();
	public:
		FragTrap(std::string name);
		FragTrap(FragTrap const &src);
		~FragTrap();
		FragTrap& operator=(FragTrap const &rhs);

		void	highFivesGuys(void);
};

#endif /* FRAGTRAP_HPP */
