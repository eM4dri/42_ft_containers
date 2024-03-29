/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:49:56 by emadriga          #+#    #+#             */
/*   Updated: 2023/03/02 17:45:58 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
#define FIXED_HPP
#include "utility/Log.hpp"

class Fixed{
	public:
		Fixed( void );
		Fixed( const int int_num );
		Fixed( const float float_num );

		Fixed( const Fixed& copy );
		~Fixed( void );

		Fixed & operator=( const Fixed& assign );


		int 	getRawBits( void ) const;
		void  setRawBits ( const int raw );

		int		toInt(void) const;
		float	toFloat(void) const;

		bool	 	operator > ( const Fixed& rhs )const;
		bool	 	operator < ( const Fixed& rhs )const;
		bool	 	operator >= ( const Fixed& rhs );
		bool	 	operator <= ( const Fixed& rhs );
		bool	 	operator == ( const Fixed& rhs );
		bool	 	operator != ( const Fixed& rhs );
		Fixed	 	operator + ( const Fixed& rhs );
		Fixed	 	operator - ( const Fixed& rhs );
		Fixed	 	operator * ( const Fixed& rhs );
		Fixed	 	operator / ( const Fixed& rhs );
		Fixed&	 	operator ++ ( void );
		Fixed	 	operator ++ ( int );
		Fixed&	 	operator -- ( void );
		Fixed	 	operator -- ( int );

		Fixed & min(Fixed& a, Fixed& b);
		Fixed & max(Fixed& a, Fixed& b);
		const Fixed & min(const Fixed& a, const Fixed& b) ;
		const Fixed & max(const Fixed& a, const Fixed& b) ;

		//*Private

		const std::string & getName() const;


	private:
		int 							_rawBits;
		static const int				_fractionalBits = 8;
		std::string						_name;
		int		_toFixed(const int int_num) const;
		int		_toFixed(const float float_num) const;

};
std::ostream & operator<<( std::ostream & o, const Fixed& rhs );

#endif
