/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 18:31:01 by jrinta-           #+#    #+#             */
/*   Updated: 2025/04/04 16:39:34 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <sstream>

static int	ft_error(std::string error, std::ifstream &ifs);
static int	incorrect_syntax(char **argv);
static void	ft_sed(std::string content, std::string filename,
			std::string toFind, std::string toReplace);
static int	ft_readfile(char *filename, std::string *content);

int	main(int argc, char **argv)
{
	std::string			content;

	if (argc != 4)
		return (incorrect_syntax(argv));
	if (ft_readfile(argv[1], &content) == -1)
		return (1);
	ft_sed(content, std::string(argv[1]),
		std::string(argv[2]), std::string(argv[3]));
	return (0);
}

static void	ft_sed(std::string content, std::string filename,
	std::string toFind, std::string toReplace)
{
	std::ofstream	ofs;
	size_t			pos;
	std::string		fileReplace = filename + ".replace";

	ofs.open(fileReplace.c_str());
	if (content.length() == 0)
	{
		ofs.close();
		return ;
	}
	pos = content.find(toFind);
	while (pos != std::string::npos)
	{
		content.erase(pos, toFind.length());
		content.insert(pos, toReplace);
		pos = content.find(toFind, pos + toReplace.length());
	}
	ofs << content;
	ofs.close();
}

static int	ft_readfile(char *filename, std::string *content)
{
	std::ifstream		ifs;
	std::stringstream	buffer;
	ifs.open(filename);
	if (!ifs)
		return (ft_error("Error opening the file.", ifs));
	buffer << ifs.rdbuf();
	if (ifs.fail())
		return (ft_error("Error reading the file.", ifs));
	ifs.close();
	*content = buffer.str();
	return (0);
}

static int	incorrect_syntax(char **argv)
{
	std::cout	<< "Usage: " << argv[0]
				<< " <filename> <string_to_replace> <replacement>"
				<< std::endl;
	return (1);
}

static int	ft_error(std::string error, std::ifstream &ifs)
{
	if (ifs.is_open())
		ifs.close();
	std::cerr << error << std::endl;
	return (-1);
}
