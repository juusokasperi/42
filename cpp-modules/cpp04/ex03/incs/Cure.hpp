/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:36:43 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/08 16:43:54 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CURE_HPP
# define CURE_HPP

# include <iostream>
# include "AMateria.hpp"

# define CURE "\033[0;33m[Cure]\033[0m "

class Cure: public AMateria {
	public:
		Cure();
		Cure(const Cure &src);
		Cure& operator=(const Cure &rhs);
		~Cure();

		virtual AMateria	*clone() const;
		virtual void		use(ICharacter &target);
};

#endif /* CURE_HPP */
