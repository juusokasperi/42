/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 12:47:38 by jrinta-           #+#    #+#             */
/*   Updated: 2025/09/05 10:28:43 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

static void	checkHeader(std::ifstream &file, std::string database);

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: " << argv[0] << " <inputFile>" << std::endl;
		return (1);
	}
	try {
		BitcoinExchange exchange(DATABASE);
		std::string	line;
		std::ifstream file(argv[1]);
		if (!file)
			throw std::runtime_error("failure to open input file.");
		checkHeader(file, argv[1]);
		while (std::getline(file, line))
		{
			try {
				exchange.convert(line);
			} catch (std::exception &e) {
				std::cerr << "Error: " << e.what() << std::endl;
			}
		}
	} catch (std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return (0);
}

static void	checkHeader(std::ifstream &file, std::string database)
{
	std::string line;
	std::getline(file, line);
	std::regex headerRegex(R"(^\s*date\s*\|\s*value\s*$)");
	if (!std::regex_match(line, headerRegex))
		throw std::runtime_error("Header invalid or missing in input file " + database);
}
