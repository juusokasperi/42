/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:36:43 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/08 16:43:12 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICE_HPP
# define ICE_HPP

# include <iostream>
# include "AMateria.hpp"

# define ICE "\033[0;96m[Ice]\033[0m "

class Ice: public AMateria {
	public:
		Ice();
		Ice(const Ice &src);
		Ice& operator=(const Ice &rhs);
		~Ice();

		virtual AMateria	*clone() const;
		virtual void		use(ICharacter &target);
};

#endif /* ICE_HPP */
