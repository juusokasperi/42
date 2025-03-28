/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:08:54 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/05 17:06:15 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

Point::Point(): _x(Fixed(0)), _y(Fixed(0))
{
}

Point::Point(const float x, const float y): _x(Fixed(x)), _y(Fixed(y))
{
}

Point::Point(const Point &src): _x(src._x), _y(src._y)
{
}

Point::~Point()
{
}

Fixed	Point::getX(void) const
{
	return (_x);
}

Fixed	Point::getY(void) const
{
	return (_y);
}
