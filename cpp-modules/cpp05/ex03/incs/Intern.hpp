/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:12:50 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/18 20:31:55 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERN_HPP
# define INTERN_HPP

# include "AForm.hpp"
# include "PresidentialPardonForm.hpp"
# include "RobotomyRequestForm.hpp"
# include "ShrubberyCreationForm.hpp"

class Intern {
	public:
		Intern();
		Intern(const Intern &src);
		Intern& operator=(const Intern &rhs);
		~Intern();

		AForm*	makeForm(const std::string name, const std::string target);
		AForm*	makeRobotomy(const std::string target) const;
		AForm*	makeShrubbery(const std::string target) const;
		AForm*	makePardon(const std::string target) const;

		class WrongFormException: public std::exception {
			public:
				virtual const char* what() const noexcept;
		};
};

typedef AForm*	(Intern::*FormFunc)(const std::string target) const;

#endif
