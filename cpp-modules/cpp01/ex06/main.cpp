/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 23:20:01 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/03 00:07:03 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int	main(int argc, char **argv)
{
	Harl harl;

	if (argc != 2)
		std::cout	<< "Usage: " << argv[0]
					<< " <DEBUG/INFO/WARNING/ERROR>" << std::endl;
	else
		harl.complain(std::string(argv[1]));
	return (0);
}
