/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 18:40:22 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/31 00:13:10 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <stack>
# include <iostream>
# include <sstream>

class RPN {
private:
	std::stack<long>	_stack;
public:
	RPN();
	RPN(const RPN &src);
	RPN(RPN &&other);
	RPN& operator=(const RPN &rhs);
	RPN& operator=(RPN &&other);
	~RPN();

	long	calculate(const std::string &input);
};

#endif /* RPN_HPP */
