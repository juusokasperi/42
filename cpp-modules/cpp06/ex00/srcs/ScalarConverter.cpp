/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 15:59:52 by jrinta-           #+#    #+#             */
/*   Updated: 2025/07/03 18:18:12 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

/*
	Constructors
*/

ScalarConverter::ScalarConverter()
{
}

ScalarConverter::~ScalarConverter()
{
}

ScalarConverter::ScalarConverter(const ScalarConverter &src)
{
	(void)src;
}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter &rhs)
{
	(void)rhs;
	return *this;
}

void	ScalarConverter::convert(const std::string s)
{
	srcType type;
	char	c;
	int		num_i;
	float	num_f;
	double	num_d;

	if (s.empty())
		return emptyInput();
	if (isPseudoLiteral(s))
		return pseudoLiterals(s);
	type = getType(s);
	switch (type)
	{
		case CHAR:
			c = s[0];
			printChar(c);
			printInt(static_cast<int>(c));
			printFloat(static_cast<float>(c), s);
			printDouble(static_cast<double>(c), s);
			break ;
		case INT:
			try {
				num_i = std::stoi(s);
			} catch(std::exception &e) {
				emptyInput();
				break;
			}
			printChar(static_cast<char>(num_i));
			printInt(num_i);
			printFloat(static_cast<float>(num_i), s);
			printDouble(static_cast<double>(num_i), s);
			break ;
		case FLOAT:
			try {
				num_f = std::stof(s);
			} catch(std::exception &e) {
				emptyInput();
				break;
			}
			if (isOverIntLimits(num_f))
				charAndIntImpossible();
			else
			{
				printChar(static_cast<char>(num_f));
				printInt(static_cast<int>(num_f));
			}
			printFloat(num_f, s);
			printDouble(static_cast<double>(num_f), s);
			break ;
		case DOUBLE:
			try {
				num_d = std::stod(s);
			} catch(std::exception &e) {
				emptyInput();
				break;
			}
			if (isOverIntLimits(num_d))
				charAndIntImpossible();
			else
			{
				printChar(static_cast<char>(num_d));
				printInt(static_cast<int>(num_d));
			}
			printFloat(static_cast<float>(num_d), s);
			printDouble(num_d, s);
			break ;
		default:
			emptyInput();
			break ;
	}
}

bool	ScalarConverter::isChar(const std::string s)
{
	if (s.length() == 1 && std::isdigit(s[0]) == 0 && (s[0] >= 0 && s[0] <= 126))
		return true;
	return false;
}

bool	ScalarConverter::isInt(const std::string s)
{
	for (size_t i = 0; i < s.length(); ++i)
	{
		if (i == 0 && (s[0] == '-' || s[0] == '+'))
			continue;
		if (std::isdigit(s[i]) == 0)
			return false;
	}
	return true;
}

bool	ScalarConverter::isFloat(const std::string s)
{
	uint	len = s.length();
	bool	dot = false;

	if (s[len - 1] != 'f')
		return false;
	for (size_t i = 0; i < (len - 1); i++)
	{
		if (i == 0 && (s[0] == '-' || s[0] == '+'))
			continue ;
		if (s[i] == '.' && dot == false)
			dot = true;
		else if (s[i] == '.' && dot == true)
			return false;
		else if (std::isdigit(s[i]) == 0)
			return false;
	}
	return true;
}

bool	ScalarConverter::isDouble(const std::string s)
{
	uint	len = s.length();
	bool	dot = false;

	if (s[len - 1] == 'f')
		return false;
	for (size_t i = 0; i < len; i++)
	{
		if (i == 0 && (s[0] == '-' || s[0] == '+'))
			continue ;
		if (s[i] == '.' && dot == false)
			dot = true;
		else if (s[i] == '.' && dot == true)
			return false;
		else if (std::isdigit(s[i]) == 0)
			return false;
	}
	return true;
}

srcType	ScalarConverter::getType(const std::string s)
{
	if (isChar(s))
		return CHAR;
	else if (isInt(s))
		return INT;
	else if (isFloat(s))
		return FLOAT;
	else if (isDouble(s))
		return DOUBLE;
	else
		return UNKNOWN;
}

void	ScalarConverter::printFloat(float n, const std::string s)
{
	int	precision = countPrecision(s);

	if (n < -std::numeric_limits<float>::max() || n > std::numeric_limits<float>::max())
		std::cout << "float: impossible" << std::endl;
	else
		std::cout << "float: " << std::fixed << std::setprecision(precision) << n << "f" << std::endl;
}


void	ScalarConverter::printChar(char n)
{
	if (n < 0 || n > 127)
		std::cout << "char: impossible" << std::endl;
	else if (n < 32 || n == 127)
		std::cout << "char: Non displayable" << std::endl;
	else
		std::cout << "char: '" << n << "'" << std::endl;
}

void	ScalarConverter::printInt(int n)
{
	if (n < std::numeric_limits<int>::min()
		|| n > std::numeric_limits<int>::max())
		std::cout << "int: impossible" << std::endl;
	else
		std::cout << "int: " << n << std::endl;
}

int	ScalarConverter::countPrecision(const std::string s)
{
	int	i = 0;
	int	len = s.length();

	while (s[i] && s[i] != '.')
		i++;
	if (s[i] == '.')
		i++;
	if (s[len - 1] == 'f')
		len--;
	if (len > i)
		return (len - i);
	return 1;
}

void	ScalarConverter::printDouble(double n, const std::string s)
{
	int	precision = countPrecision(s);

	if (n < -std::numeric_limits<double>::max() || n > std::numeric_limits<double>::max())
		std::cout << "double: impossible" << std::endl;
	else
		std::cout << "double: " << std::fixed << std::setprecision(precision) << n << std::endl;
}

void	ScalarConverter::emptyInput(void)
{
	std::cout	<< "char: impossible" << std::endl
				<< "int: impossible" << std::endl
				<< "float: impossible" << std::endl
				<< "double: impossible" << std::endl;
}

void	ScalarConverter::pseudoLiterals(const std::string s)
{
	const std::string	cases[] = {"+inf", "+inff", "-inf", "-inff", "nan", "nanf" };
	float	num_f;
	double	num_d;

	int		i = -1;
	while (++i < 6 && cases[i] != s);
	switch (i)
	{
		case INF_P:
			num_d = std::numeric_limits<double>::infinity();
			num_f = static_cast<float>(num_d);
			break ;
		case INFF_P:
			num_f = std::numeric_limits<float>::infinity();
			num_d = static_cast<double>(num_f);
			break ;
		case INF_N:
			num_d = -std::numeric_limits<double>::infinity();
			num_f = static_cast<float>(num_d);
			break ;
		case INFF_N:
			num_f = -std::numeric_limits<float>::infinity();
			num_d = static_cast<double>(num_f);
			break ;
		case NAND:
			num_d = std::numeric_limits<double>::quiet_NaN();
			num_f = static_cast<float>(num_d);
			break ;
		case NANF:
			num_f = std::numeric_limits<float>::quiet_NaN();
			num_d = static_cast<double>(num_f);
			break ;
		default:
			return ;
	}
	std::cout	<< "char: impossible" << std::endl
				<< "int: impossible" << std::endl
				<< "float: " << num_f << "f" << std::endl
				<< "double: " << num_d << std::endl;
}

bool ScalarConverter::isPseudoLiteral(const std::string &s) { return s == "nan" || s == "nanf" || s == "+inff" || s == "-inff"; }
bool ScalarConverter::isOverIntLimits(double n) { return static_cast<long>(n) < std::numeric_limits<int>::min() || static_cast<long>(n) > std::numeric_limits<int>::max(); }
bool ScalarConverter::isOverIntLimits(float n) { return static_cast<long>(n) < std::numeric_limits<int>::min() || static_cast<long>(n) > std::numeric_limits<int>::max(); }

void ScalarConverter::charAndIntImpossible()
{
	std::cout	<< "char: impossible" << std::endl
				<< "int: impossible" << std::endl;
}
