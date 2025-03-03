/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:01:05 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/03 17:32:39 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>

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
		Fixed(Fixed &&other) noexcept;
		Fixed& operator=(Fixed &&rhs) noexcept;
		~Fixed();

		const int&	getRawBits( void ) const;
		void		setRawBits ( int const raw );
		float		toFloat( void ) const;
		int			toInt( void ) const;
};

std::ostream& operator<<(std::ostream &os, const Fixed& fixed);

#endif /* FIXED_HPP */
