/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:43:50 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/02 16:12:54 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int	main(void)
{
	int	N = 0;
	Zombie	*horde;

	while (N <= 0)
	{
		std::cout << TMAGENTA << "Insert size of zombieHorde: " << TRESET;
		std::cin >> N;
		if (N <= 0)
			std::cout << "Invalid size, must be bigger than 0." << std::endl;
	}
	std::cout << "Creating zombieHorde of size " << N << std::endl;
	horde = zombieHorde(N, "Brain Eater");
	for (int i = 0; i < N; i++)
	{
		std::cout << TMAGENTA << "[" << i << "] " << TRESET;
		horde[i].announce();
	}
	delete[] (horde);
	return (0);
}
