/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:01:23 by jrinta-           #+#    #+#             */
/*   Updated: 2025/06/04 12:50:53 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

# include <iostream>
# include "AForm.hpp"

class AForm;

class Bureaucrat {
	private:
		const std::string	_name;
		int					_grade;
	public:
		Bureaucrat();
		Bureaucrat(const std::string name, int grade);
		Bureaucrat(const Bureaucrat &src);
		~Bureaucrat();
		Bureaucrat& operator=(const Bureaucrat &rhs) = delete;

		const std::string	&getName() const;
		int					getGrade() const;
		void				incrementGrade();
		void				decrementGrade();
		void				signForm(AForm &form) const;
		void				executeForm(AForm &form) const;

		class GradeTooHighException: public std::exception {
			public:
				virtual const char* what() const noexcept;
		};
		class GradeTooLowException: public std::exception {
			public:
				virtual const char* what() const noexcept;
		};
};

std::ostream& operator<<(std::ostream &os, const Bureaucrat& bureaucrat);

#endif /* BUREAUCRAT_HPP */
