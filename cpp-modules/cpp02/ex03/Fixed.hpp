/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:01:05 by jrinta-           #+#    #+#             */
/*   Updated: 2025/04/14 16:10:52 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>
# include <cmath>
# include <limits>

const int	FIXED_INT_MAX = 8388607;
const int	FIXED_INT_MIN = -8388608;
const float	FIXED_FLOAT_MAX = 8388607.0f;
const float	FIXED_FLOAT_MIN = -8388608.0f;

class Fixed {
	private:
		int					_value;
		static const int	_fractionalBits = 8;
	public:
		Fixed();
		Fixed(const int	value);
		Fixed(const float value);
		Fixed(const Fixed &src);
		Fixed& operator=(const Fixed &rhs);
		~Fixed();

		int					getRawBits(void) const;
		void				setRawBits (int const raw);
		float				toFloat(void) const;
		int					toInt(void) const;

		bool				operator>(const Fixed &rhs) const;
		bool				operator<(const Fixed &rhs) const;
		bool				operator>=(const Fixed &rhs) const;
		bool				operator<=(const Fixed &rhs) const;
		bool				operator==(const Fixed &rhs) const;
		bool				operator!=(const Fixed &rhs) const;

		Fixed				operator+(const Fixed &rhs) const;
		Fixed				operator-(const Fixed &rhs) const;
		Fixed				operator*(const Fixed &rhs) const;
		Fixed				operator/(const Fixed &rhs) const;

		Fixed&				operator++();
		Fixed				operator++(int);
		Fixed&				operator--();
		Fixed				operator--(int);

		static Fixed&		min(Fixed &a, Fixed &b);
		static const Fixed&	min(const Fixed &a, const Fixed &b);
		static Fixed&		max(Fixed &a, Fixed &b);
		static const Fixed&	max(const Fixed &a, const Fixed &b);
};

std::ostream& operator<<(std::ostream &os, const Fixed& fixed);

#endif /* FIXED_HPP */
