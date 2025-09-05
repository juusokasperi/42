/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 18:40:22 by jrinta-           #+#    #+#             */
/*   Updated: 2025/09/05 11:11:46 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <stack>
# include <iostream>
# include <sstream>
# include <limits>
# include <cstring>

class RPN {
	private:
		static long	_doMath(long firstOperand, long secondOperand, char op);

	public:
		RPN() = delete;
		RPN(const RPN &src) = delete;
		RPN(RPN &&other) = delete;
		RPN& operator=(const RPN &rhs) = delete;
		RPN& operator=(RPN &&other) = delete;
		~RPN() = delete;

		static long	calculate(const std::string &input);
};

#endif /* RPN_HPP */
