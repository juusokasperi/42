/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 13:31:22 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/02 16:12:13 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

# include <iostream>

# define TMAGENTA "\033[95m"
# define TRESET "\033[0m"

class Zombie {
	private:
		std::string name;
	public:
		Zombie();
		~Zombie();
		void	setName( std::string name );
		void	announce( void );
};

Zombie	*zombieHorde( int N, std::string name );

#endif /* ZOMBIE_HPP */
