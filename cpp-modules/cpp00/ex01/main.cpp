/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:38:53 by jrinta-           #+#    #+#             */
/*   Updated: 2025/02/28 15:55:12 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "simpleClass.hpp"

int	main(void)
{
	SimpleClass	simpleObject = SimpleClass("Name", 100);
	simpleObject.print();
	return (0);
}
