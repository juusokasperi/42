/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 23:37:30 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/08 01:03:54 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_HPP
# define BRAIN_HPP

# include <iostream>

# define BRAIN "\033[0;93m[BRAIN]\033[0m "

class Brain {
	private:
		std::string _ideas[100];
	public:
		Brain();
		Brain(const Brain &src);
		Brain& operator=(const Brain &rhs);
		~Brain();

		void	setIdea(int i, std::string idea);
		const std::string&	getIdea(int i) const;
};

#endif /* BRAIN_HPP */
