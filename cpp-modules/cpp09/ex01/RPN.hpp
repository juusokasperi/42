/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 18:40:22 by jrinta-           #+#    #+#             */
/*   Updated: 2025/04/01 23:49:43 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <stack>
# include <iostream>
# include <sstream>

class RPN {
	private:
		static long	_doMath(long firstOperand, long secondOperand, char op);

		RPN();
		RPN(const RPN &src);
		RPN(RPN &&other);
		RPN& operator=(const RPN &rhs);
		RPN& operator=(RPN &&other);
		~RPN();
	public:
		static long	calculate(const std::string &input);
};

#endif /* RPN_HPP */
