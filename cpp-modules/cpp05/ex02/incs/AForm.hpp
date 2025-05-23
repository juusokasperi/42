/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 20:20:48 by jrinta-           #+#    #+#             */
/*   Updated: 2025/05/23 18:24:35 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AFORM_HPP
# define AFORM_HPP

# include <iostream>
# include "Bureaucrat.hpp"

class Bureaucrat;

class AForm {
	private:
		const std::string	_name;
		const int			_gradeToSign;
		const int			_gradeToExecute;
		bool				_isSigned;
	public:
		AForm();
		AForm(const std::string name, const int gradeToSign, const int gradeToExecute);
		AForm(const AForm &source);
		AForm& operator=(const AForm &rhs) = delete;
		virtual ~AForm();

		const std::string	&getName() const;
		bool				getIsSigned() const;
		int					getGradeToSign() const;
		int					getGradeToExecute() const;
		void				beSigned(const Bureaucrat &bureaucrat);

		virtual void		execute(Bureaucrat const &executor) const = 0;
		bool				isExecutable(Bureaucrat const &executor) const;

		class GradeTooHighException: public std::exception {
			public:
				virtual const char* what() const noexcept;
		};
		class GradeTooLowException: public std::exception {
			public:
				virtual const char* what() const noexcept;
		};
		class FormAlreadySignedException: public std::exception {
			public:
				virtual const char *what() const noexcept;
		};
		class FormNotSignedException: public std::exception {
			public:
				virtual const char *what() const noexcept;
		};
};

std::ostream& operator<<(std::ostream &os, const AForm& form);

#endif /* AFORM_HPP*/
