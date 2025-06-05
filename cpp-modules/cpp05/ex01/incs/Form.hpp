/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 20:20:48 by jrinta-           #+#    #+#             */
/*   Updated: 2025/06/05 13:49:18 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
# define FORM_HPP

# include <iostream>
# include "Bureaucrat.hpp"

class Bureaucrat;

class Form {
	private:
		const std::string	_name;
		const int			_gradeToSign;
		const int			_gradeToExecute;
		bool				_isSigned;
	public:
		Form();
		Form(const std::string name, const int gradeToSign, const int gradeToExecute);
		Form(const Form &source);
		Form& operator=(const Form &rhs) = delete;
		~Form();

		const std::string	&getName() const;
		bool				getIsSigned() const;
		int					getGradeToSign() const;
		int					getGradeToExecute() const;
		void				beSigned(const Bureaucrat &bureaucrat);

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
				virtual const char* what() const noexcept;
		};
};

std::ostream& operator<<(std::ostream &os, const Form& form);

#endif /* FORM_HPP*/
