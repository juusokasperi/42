/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:57:40 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/07 13:55:08 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAGTRAP_HPP
# define FRAGTRAP_HPP

# include "ClapTrap.hpp"

# define FRAGTRAP "\033[91m[FragTrap]\033[0m "

class FragTrap: virtual public ClapTrap {
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
