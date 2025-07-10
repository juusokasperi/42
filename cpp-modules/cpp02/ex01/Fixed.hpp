/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:01:05 by jrinta-           #+#    #+#             */
/*   Updated: 2025/04/14 15:59:16 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>
# include <cmath>

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

		int			getRawBits( void ) const;
		void		setRawBits ( int const raw );
		float		toFloat( void ) const;
		int			toInt( void ) const;
};

std::ostream& operator<<(std::ostream &os, const Fixed& fixed);

#endif /* FIXED_HPP */
