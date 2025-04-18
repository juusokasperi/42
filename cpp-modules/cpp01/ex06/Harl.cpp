/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 23:06:07 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/03 00:06:44 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

void	Harl::complain( std::string level )
{
	std::string		levels[] = { "DEBUG", "INFO", "WARNING", "ERROR" };
	int				i;

	i = -1;
	while (++i < 4 && level != levels[i]);
	switch (i)
	{
		case (0):
			this->debug();
		case (1):
			this->info();
		case (2):
			this->warning();
		case (3):
			this->error();
			break ;
		default:
			std::cout << "[ Probably complaining about insignificant problems ]"
					  << std::endl;
	}
}

void	Harl::debug( void )
{
	std::cout	<< "[ DEBUG ]\n"
				<< "I love having extra bacon for my "
				<< "7XL-double-cheese-triple-pickle-special- ketchup burger. "
				<< "I really do!" << std::endl;
}

void	Harl::info( void )
{
	std::cout	<< "[ INFO ]\n"
				<< "I cannot believe adding extra bacon costs more money.\n"
				<< "You didn’t put enough bacon in my burger!\n"
				<< "If you did, I wouldn’t be asking for more!" << std::endl;
}

void	Harl::warning( void )
{
	std::cout	<< "[ WARNING ]\n"
				<< "I think I deserve to have some extra bacon for free.\n"
				<< "I’ve been coming for years whereas you started "
				<< "working here since last month." << std::endl;
}

void	Harl::error( void )
{
	std::cout	<< "[ ERROR ]\n"
				<< "This is unacceptable! I want to speak to the manager now."
				<< std::endl;
}

Harl::Harl()
{
}

Harl::~Harl()
{
}
