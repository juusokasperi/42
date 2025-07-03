/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 15:56:06 by jrinta-           #+#    #+#             */
/*   Updated: 2025/07/03 18:15:45 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

# include <iostream>
# include <iomanip>
# include <limits>

typedef enum	e_type {
	CHAR,
	INT,
	FLOAT,
	DOUBLE,
	UNKNOWN = -1
} srcType;

enum e_pseudo {
	INF_P,
	INFF_P,
	INF_N,
	INFF_N,
	NAND,
	NANF,
	INVALID
};

class ScalarConverter {
	private:
		ScalarConverter();
		~ScalarConverter();
		ScalarConverter(const ScalarConverter &src);
		ScalarConverter& operator=(const ScalarConverter &rhs);

		static void		printDouble(double n, const std::string s);
		static void		printFloat(float n, const std::string s);
		static int		countPrecision(const std::string s);
		static void		printInt(int n);
		static void		printChar(char n);
		static void		pseudoLiterals(const std::string s);
		static void		emptyInput(void);
		static srcType	getType(const std::string s);
		static bool		isDouble(const std::string s);
		static bool		isFloat(const std::string s);
		static bool		isInt(const std::string s);
		static bool		isChar(const std::string s);
		static bool 	isPseudoLiteral(const std::string &s);
		static bool		isOverIntLimits(double n);
		static bool		isOverIntLimits(float n);
		static void		charAndIntImpossible();
	public:
		static void convert(const std::string s);
};

#endif /* SCALARCONVERTER_HPP */
