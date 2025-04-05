/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:01:10 by jrinta-           #+#    #+#             */
/*   Updated: 2025/04/05 19:13:18 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_HPP
# define POINT_HPP

# include "Fixed.hpp"

class Point {
	private:
		const Fixed _x;
		const Fixed _y;
	public:
		Point();
		Point(const float x, const float y);
		Point(const Point &src);
		Point& operator=(const Point &rhs) = delete;
		~Point();

		Fixed		getX(void) const;
		Fixed		getY(void) const;
};

std::ostream& operator<<(std::ostream &os, const Point& point);

#endif /* POINT_HPP */
