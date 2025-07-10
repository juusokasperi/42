/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:47:59 by jrinta-           #+#    #+#             */
/*   Updated: 2025/05/23 19:17:12 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <map>
# include <iostream>
# include <fstream>
# include <regex>
# include <ctime>

constexpr char DATABASE[] = "data.csv";
constexpr char DATA_REGEX[] = R"(^(\d{4})-(0[1-9]|1[0-2])-(0[1-9]|[12]\d|3[01]),\s*(-?\d+(\.\d+)?)$)";
constexpr char CONVERT_REGEX[] = R"(^(\d{4})-(0[1-9]|1[0-2])-(0[1-9]|[12]\d|3[01])\s*\|\s*(-?\d+(\.\d+)?)$)";

class BitcoinExchange {
	private:
	std::map<std::string, double> _data;

	void			_parseData(std::ifstream &ifs);
	std::string		_validateDate(std::smatch &match) const;
	public:
		BitcoinExchange() = delete;
		BitcoinExchange(std::string database);
		~BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &src);
		BitcoinExchange& operator=(const BitcoinExchange &rhs);
		BitcoinExchange(BitcoinExchange &&other);
		BitcoinExchange& operator=(BitcoinExchange &&other);

		void	convert(std::string input) const;
};

#endif /* BITCOINEXCHANGE_HPP */
