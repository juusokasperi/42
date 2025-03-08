/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 13:51:51 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/08 16:45:21 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIASOURCE_HPP
# define MATERIASOURCE_HPP

# include "IMateriaSource.hpp"
# include <iostream>

# define MSOURCE "\033[0;92m[MateriaSource]\033[0m "

class MateriaSource: public IMateriaSource {
	private:
		AMateria*	_materias[4];
	public:
		MateriaSource();
		MateriaSource(const MateriaSource &src);
		MateriaSource& operator=(const MateriaSource &rhs);
		~MateriaSource();

		void		learnMateria(AMateria*);
		AMateria*	createMateria(std::string const &type);
};

#endif /* MATERIASOURCE_HPP */
