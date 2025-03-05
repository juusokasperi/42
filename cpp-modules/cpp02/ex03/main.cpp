/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:00:21 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/05 17:06:19 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Point.hpp"

bool bsp( Point const a, Point const b, Point const c, Point const point);

int main(void)
{
	Point a(300, 10);
	Point b(100, 300);
	Point c(500, 300);
	Point p1(250, 250);
	Point p2;
	Point p3(300, 5);
	Point p4(300,10);

	std::cout << "Triangle coordinates: A(300,10) B(100,300) C(500,300)" << std::endl;
	std::cout << "Point(250,250) is inside the triangle: " << bsp(a, b, c, p1) << std::endl;
	std::cout << "Point(0,0) is inside the triangle: " << bsp(a, b, c, p2) << std::endl;
	std::cout << "Point(300,5) is inside the triangle: " << bsp(a, b, c, p3) << std::endl;
	std::cout << "Point(300,10) is inside the triangle: " << bsp(a, b, c, p4) << std::endl;
	return (0);
}
