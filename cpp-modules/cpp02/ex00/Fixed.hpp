/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:01:05 by jrinta-           #+#    #+#             */
/*   Updated: 2025/03/03 14:52:53 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>

class Fixed {
	private:
		int					_value;
		static const int	_bits = 8;
	public:
		Fixed();
		Fixed(const Fixed &src);
		Fixed& operator=(const Fixed &rhs);
		Fixed(Fixed &&other) noexcept;
		Fixed& operator=(Fixed &&rhs) noexcept;
		~Fixed();
		const int&	getRawBits( void ) const;
		void		setRawBits ( int const raw );
};

#endif /* FIXED_HPP */
