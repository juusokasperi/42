/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 23:20:01 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/02 23:24:48 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int	main(void)
{
	Harl harl;

	std::cout << "Calling complain with DEBUG, INFO, WARNING and ERROR:" << std::endl;
	harl.complain("DEBUG");
	harl.complain("INFO");
	harl.complain("WARNING");
	harl.complain("ERROR");
	std::cout << std::endl << "Calling complain with invalid arguments:" << std::endl;
	harl.complain("DEBU");
	harl.complain("DEBUGG");
	harl.complain("");
	harl.complain("WARNINGI");
	std::cout << std::endl << "Exiting program." << std::endl;
	return (0);
}
