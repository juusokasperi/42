/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 18:44:25 by jrinta-           #+#    #+#             */
/*   Updated: 2025/05/23 18:51:13 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN()
{
}

RPN::~RPN()
{
}

RPN::RPN(const RPN &src)
{
	(void)src;
}

RPN::RPN(RPN &&other)
{
	(void)other;
}

RPN&	RPN::operator=(const RPN &rhs)
{
	(void)rhs;
	return (*this);
}

RPN&	RPN::operator=(RPN &&other)
{
	(void)other;
	return (*this);
}

static bool	outOfRange(long firstOperand, long secondOperand, char op)
{
	switch (op)
	{
		case '+':
			return ((secondOperand > 0 && firstOperand > LONG_MAX - secondOperand)
				|| (secondOperand < 0 && firstOperand < LONG_MIN - secondOperand));
		case '-':
			return ((secondOperand < 0 && firstOperand > LONG_MAX + secondOperand)
				|| (secondOperand > 0 && firstOperand < LONG_MIN + secondOperand));
		case '*':
			if (secondOperand == 0)
				return (false);
			else if (secondOperand == -1)
				return (firstOperand == LONG_MIN);
			else if (secondOperand > 0)
				return (firstOperand > LONG_MAX / secondOperand
					|| firstOperand < LONG_MIN / secondOperand);
			else
				return (firstOperand < LONG_MAX / secondOperand
					|| firstOperand > LONG_MIN / secondOperand);
		case '/':
			return (firstOperand == LONG_MIN && secondOperand == -1);
		default:
			throw std::runtime_error("Invalid operator " + std::string(1, op));
	}
}

static bool	isNumber(const std::string &s)
{
	size_t	i = 0;
	if (s.length() > 1 && (s[0] == '+' || s[0] == '-'))
		i++;
	while (i < s.length())
	{
		if (!std::isdigit(s[i]))
			return (false);
		i++;
	}
	return (true);
}

static bool	isOperator(const std::string &s)
{
	return (s.length() == 1 && std::strchr("+-/*", s[0]));
}


long RPN::_doMath(long firstOperand, long secondOperand, char op)
{
	if (outOfRange(firstOperand, secondOperand, op))
		throw std::out_of_range("Calculation out of range.");
	switch (op)
	{
		case '+':
			return (firstOperand + secondOperand);
		case '-':
			return (firstOperand - secondOperand);
		case '*':
			return (firstOperand * secondOperand);
		case '/':
			if (secondOperand == 0)
				throw std::runtime_error("Division by zero.");
			return (firstOperand / secondOperand);
		default:
			throw std::runtime_error("Invalid operator " + std::string(1, op));
	}
}

/*
	Remove the if (num < 0 || num > 9) check at 137-138 to
	make the calculator work with all integers.
*/
long	RPN::calculate(const std::string &input)
{
	if (input.empty())
		throw std::runtime_error("Empty input.");
	if (!std::isdigit(input[0]))
		throw std::runtime_error("Invalid syntax.");
	std::stack<long>	stack;
	std::stringstream ss(input);
	std::string	token;
	while (ss >> token)
	{
		if (isNumber(token))
		{
			int	num;
			try {
				num = std::stoi(token);
			} catch (std::exception &e) {
				throw std::out_of_range("Invalid integer " + token);
			}
			if (num < 0 || num > 9)
				throw std::runtime_error("Number " + token + " not in range (0-9).");
			stack.push(num);
		}
		else if (isOperator(token))
		{
			if (stack.size() < 2)
				throw std::runtime_error("Unexpected operator " + token);
			long secondOperand = stack.top();
			stack.pop();
			long firstOperand = stack.top();
			stack.pop();
			stack.push(_doMath(firstOperand, secondOperand, token[0]));
		}
		else
			throw std::runtime_error("Invalid operator " + token);
	}
	if (stack.size() > 1)
		throw std::runtime_error("Input missing " + std::to_string(stack.size() - 1) + " operator(s).");
	if (stack.empty())
		throw std::runtime_error("Input missing an operand.");
	return (stack.top());
}
