/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 14:06:54 by jrinta-           #+#    #+#             */
/*   Updated: 2025/09/05 11:45:22 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(std::string database)
{
	std::string line;
	std::ifstream ifs(database);
	std::regex headerRegex("^\\s*date\\s*,\\s*exchange_rate\\s*$");

	if (!ifs)
		throw std::runtime_error("Failure opening database file " + database);
	std::getline(ifs,line);
	if (!std::regex_match(line, headerRegex))
		throw std::runtime_error("Header invalid or missing in database file.");
	_parseData(ifs);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src): _data(src._data)
{
}

BitcoinExchange::~BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(BitcoinExchange &&other): _data(std::move(other._data))
{
}

BitcoinExchange&	BitcoinExchange::operator=(const BitcoinExchange &rhs)
{
	if (this != &rhs)
		_data = rhs._data;
	return (*this);
}

BitcoinExchange&	BitcoinExchange::operator=(BitcoinExchange &&other)
{
	if (this != &other)
		_data = std::move(other._data);
	return (*this);
}

static bool	isLeapYear(int year) {
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

std::string	BitcoinExchange::_validateDate(std::smatch &match) const
{
	std::time_t t = std::time(nullptr);
	std::tm* now = std::localtime(&t);
	int	thisYear = now->tm_year + 1900;

	int	year = std::stoi(match[1].str());
	int month = std::stoi(match[2].str());
	int day = std::stoi(match[3].str());
	if (year < 2009 || year > thisYear)
		throw std::runtime_error("invalid year => " + match[0].str());
	if (month < 1 || month > 12)
		throw std::runtime_error("invalid month >= " + match[1].str());
	static const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int maxDay = daysInMonth[month - 1];
	if (month == 2 && isLeapYear(year))
		maxDay = 29;
	if (day < 1 || day > maxDay)
		throw std::runtime_error("invalid day => " + match[0].str());
	if (year == 2009 && month == 1 && day < 2)
		throw std::runtime_error("invalid date => " + match[0].str());
	return (match[1].str() + "-" + match[2].str() + "-" + match[3].str());
}

void	BitcoinExchange::_parseData(std::ifstream &ifs)
{
	std::string	line;
	std::regex dataRegex(DATA_REGEX);
	while (std::getline(ifs, line))
	{
		std::smatch	match;
		if (!std::regex_match(line, match, dataRegex))
			throw std::runtime_error("bad input => " + line);
		std::string date = _validateDate(match);
		double exchangeRate = std::stod(match[4].str());
		if (exchangeRate < 0)
			throw std::runtime_error("invalid exchange rate => " + line);
		_data.insert({date, exchangeRate});
	}
}

void	BitcoinExchange::convert(std::string input) const
{
	if (input.empty())
		return;
	std::regex dataRegex(CONVERT_REGEX);
	std::smatch	match;
	if (!std::regex_match(input, match, dataRegex))
		throw std::runtime_error("bad input => " + input);
	std::string date = _validateDate(match);
	double value = std::stod(match[4]);
	if (value < 0)
		throw std::runtime_error("not a positive number.");
	if (value > 1000)
		throw std::runtime_error("too large a number.");
	if (_data.empty())
		throw std::runtime_error("exchange database is empty.");
	auto it = _data.lower_bound(date);
	if (it == _data.end() || (it != _data.begin() && it->first != date))
		--it;
	std::cout << date << " => " << match[4] << " = " << value * it->second << std::endl;
}
