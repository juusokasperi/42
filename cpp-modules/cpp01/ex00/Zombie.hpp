/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 13:31:22 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/02 15:50:04 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

# include <iostream>

class Zombie {
	private:
		std::string name;
	public:
		Zombie( std::string name );
		~Zombie();
		void	announce( void );
};

Zombie	*newZombie( std::string name );
void	randomChump( std::string name );

#endif /* ZOMBIE_HPP */
