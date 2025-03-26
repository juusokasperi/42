/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 19:48:40 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/26 21:33:54 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.tpp"
#include <iostream>

static void	test_str(void)
{
	std::cout << "\033[0;93m*** TEST STRING ARRAY***\033[0m" << std::endl;
	Array<std::string> strArray;
	Array<std::string> strArray2(10);

	std::cout << "Default constructor was called for first array, size is " << strArray.size() << std::endl;
	std::cout <<  "Second array size is " << strArray2.size() << std::endl;
	strArray = strArray2;
	std::cout << "Copy assignment operator called for strArray = strArray2, so strArray.size is " << strArray.size() << std::endl;

	for (int i = 0; i < 10; i++)
	{
		strArray[i] = "First str Array n. " + std::to_string(i + 1);
		strArray2[i] = "Second str Array n. " + std::to_string(i + 1);
	}
	std::cout << std::endl;
	for (int i = 0; i < 10; i++)
	{
		std::cout << strArray[i] << std::endl;
		std::cout << strArray2[i] << std::endl;
	}
	std::cout << std::endl;
	strArray = std::move(strArray2);
	std::cout <<  "Moving strArray2 to strArray so second array size is " << strArray2.size() << std::endl;
	for (int i = 0; i < 10; i++)
	{
		std::cout << strArray[i] << std::endl;
	}
	std::cout << std::endl;
}

static void	test_float(void)
{
	std::cout << "\033[0;93m*** TEST FLOAT ARRAY***\033[0m" << std::endl;
	Array<float> array;
	Array<float> array2(10);

	std::cout << "Default constructor was called for first array, size is " << array.size() << std::endl;
	std::cout <<  "Second array size is " << array2.size() << std::endl;
	array = array2;
	std::cout << "Copy assignment operator called for array = array2, so array.size is " << array.size() << std::endl;

	for (int i = 0; i < 10; i++)
	{
		array[i] = 0.0f + i;;
		array2[i] = 0.5f + i;
	}
	std::cout << std::endl;
	for (int i = 0; i < 10; i++)
	{
		std::cout <<array[i] << std::endl;
		std::cout << array2[i] << std::endl;
	}
	std::cout << std::endl;
	array = std::move(array2);
	std::cout <<  "Moving array2 to array so second array size is " << array2.size() << std::endl;
	for (int i = 0; i < 10; i++)
		std::cout << array[i] << std::endl;
	Array<float> array3 = std::move(array);
	std::cout <<  "Moving array to array3 so first array size is " << array.size() << std::endl;
	for (int i = 0; i < 10; i++)
		std::cout << array3[i] << std::endl;
	try {
		std::cout << "Trying to reach index 10 (out of bounds)" << std::endl;
		std::cout << array3[10] << std::endl;
	} catch (const std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	std::cout << std::endl;
}

int	main(void)
{
	test_str();
	test_float();
	std::cout << "\033[0;93m***TEST SIZE 0***\033[0m" << std::endl;
	Array<int> array(0);
	std::cout << "Array size is " << array.size() << std::endl;
	try {
		std::cout << "Trying to access array[0]" << std::endl;
		std::cout << array[0] << std::endl;
	} catch (const std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return (0);
}
