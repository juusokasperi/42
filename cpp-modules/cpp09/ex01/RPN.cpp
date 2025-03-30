/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 18:44:25 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/31 01:15:55 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(): _stack()
{
}

RPN::~RPN()
{
}

RPN::RPN(const RPN &src): _stack(src._stack)
{
}

RPN::RPN(RPN &&other): _stack(std::move(other._stack))
{
}

RPN&	RPN::operator=(const RPN &rhs)
{
	if (this != &rhs)
		_stack = rhs._stack;
	return (*this);
}

RPN&	RPN::operator=(RPN &&other)
{
	if (this != &other)
		_stack = std::move(other._stack);
	return (*this);
}

static bool	outOfRange(long firstOperand, long secondOperand, char op)
{
	switch (op)
	{
		case '+':
			return (firstOperand > LONG_MAX - secondOperand || firstOperand < LONG_MIN + secondOperand);
		case '-':
			return (firstOperand > LONG_MAX + secondOperand || firstOperand < LONG_MIN - secondOperand);
		case '*':
			return (secondOperand != 0 && (firstOperand > LONG_MAX / secondOperand || firstOperand < LONG_MIN / secondOperand));
		case '/':
			return (firstOperand == LONG_MIN && secondOperand == -1);
		default:
			throw std::runtime_error("Invalid operator " + std::string(1, op));
	}
}

static long doMath(long firstOperand, long secondOperand, char op)
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

static bool	isNumber(std::string &s)
{
	int	i = 0;
	if (s.length() > 1 && (s[0] == '+' || s[0] == '-'))
		i++;
	while (s[i])
	{
		if (!std::isdigit(s[i]))
			return (false);
		i++;
	}
	return (true);
}

static bool	isOperator(std::string &s)
{
	return (s.length() == 1 && std::strchr("+-/*", s[0]));
}

long	RPN::calculate(const std::string &input)
{
	std::stringstream ss(input);
	std::string	token;
	while (ss >> token)
	{
		if (isNumber(token))
		{
			try {
				_stack.push(std::stoi(token));
			} catch (std::exception &e) {
				throw std::runtime_error("Invalid number " + token);
			}
		}
		else if (isOperator(token))
		{
			if (_stack.size() < 2)
				throw std::runtime_error("Unexpected operator " + token);
			long secondOperand = _stack.top();
			_stack.pop();
			long firstOperand = _stack.top();
			_stack.pop();
			_stack.push(doMath(firstOperand, secondOperand, token[0]));
		}
		else
			throw std::runtime_error("Invalid operator " + token);
	}
	if (_stack.size() > 1)
		throw std::runtime_error("Input missing " + std::to_string(_stack.size() - 1) + " operator(s).");
	if (_stack.empty())
		throw std::runtime_error("Input missing an operand.");
	return (_stack.top());
}
