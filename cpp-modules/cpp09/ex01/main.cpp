/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 20:59:11 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/30 21:28:14 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: " << argv[0] << " \"x y + z * j /\"" << std::endl;
		return (1);
	}
	try {
		RPN rpn;
		int result = rpn.calculate(argv[1]);
		std::cout << "Result: " << argv[1] << " = " << result << std::endl;
	} catch (std::runtime_error &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return (0);
}
