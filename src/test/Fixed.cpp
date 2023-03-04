/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:49:56 by emadriga          #+#    #+#             */
/*   Updated: 2023/03/04 16:36:54 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test/Fixed.hpp"
# define DEFAULT_NAME "Anonimous"

Fixed::Fixed( void )
	: _rawBits(0), _name(DEFAULT_NAME)
{}

Fixed::Fixed( const int int_num )
	: _rawBits ( _toFixed( int_num ) ), _name(DEFAULT_NAME)
{}

Fixed::Fixed( const float float_num )
	: _rawBits ( _toFixed( float_num ) ), _name(DEFAULT_NAME)
{}

Fixed::Fixed( const Fixed& copy ) {	*this = copy; }

Fixed::~Fixed( void ) {}

Fixed & Fixed::operator=( const Fixed& assign )
{
	if (this != &assign)
	{
		_rawBits = assign.getRawBits();
		_name = assign.getName();
	}
	return *this;
}

int 	Fixed::getRawBits( void ) const{
	return this->_rawBits;
}

void  Fixed::setRawBits ( const int raw ){
	this->_rawBits = raw;
}

int		Fixed::toInt(void) const{
	return (this->_rawBits >> this->_fractionalBits);
}

float	Fixed::toFloat(void) const{
	return ((float)this->_rawBits / (float)(1 << this->_fractionalBits));
}
bool	 	Fixed::operator > ( const Fixed& rhs )const{
	return ( this->getRawBits() > rhs.getRawBits() );
}
bool	 	Fixed::operator < ( const Fixed& rhs )const{
	return ( this->getRawBits() < rhs.getRawBits() );
}
bool	 	Fixed::operator >= ( const Fixed& rhs ){
	return ( this->getRawBits() >= rhs.getRawBits() );
}
bool	 	Fixed::operator <= ( const Fixed& rhs ){
	return ( this->getRawBits() <= rhs.getRawBits() );
}
bool	 	Fixed::operator == ( const Fixed& rhs ){
	return ( this->getRawBits() == rhs.getRawBits() );
}
bool	 	Fixed::operator != ( const Fixed& rhs ){
	return ( this->getRawBits() != rhs.getRawBits() );
}
Fixed	 	Fixed::operator + ( const Fixed& rhs ){
	Fixed result;
	result.setRawBits(this->getRawBits() + rhs.getRawBits());
	return ( result );
}
Fixed	 	Fixed::operator - ( const Fixed& rhs ){
	Fixed result;
	result.setRawBits(this->getRawBits() - rhs.getRawBits());
	return ( result );
}
Fixed	 	Fixed::operator * ( const Fixed& rhs ){
	float result;
	result = this->toFloat() * rhs.toFloat();
	return (Fixed(result));
}
Fixed	 	Fixed::operator / ( const Fixed& rhs ){
	float result;
	result = this->toFloat() / rhs.toFloat();
	return (Fixed(result));
}
Fixed&	 	Fixed::operator ++ ( void ){
	this->setRawBits(this->getRawBits() + 1);
	return ( *this );
}
Fixed	 	Fixed::operator ++ ( int ){
	Fixed output(*this);
	this->setRawBits(this->getRawBits() + 1);
	return ( output );
}
Fixed&	 	Fixed::operator -- ( void ){
	this->setRawBits(this->getRawBits() - 1);
	return ( *this );
}
Fixed	 	Fixed::operator -- ( int ){
	Fixed output(*this);
	this->setRawBits(this->getRawBits() - 1);
	return ( output );
}

Fixed & Fixed::min(Fixed& a, Fixed& b){
	if (a.getRawBits() < b.getRawBits())
		return (a);
	return (b);
}
Fixed & Fixed::max(Fixed& a, Fixed& b){
	if (a.getRawBits() > b.getRawBits())
		return (a);
	return (b);
}
const Fixed & Fixed::min(const Fixed& a, const Fixed& b) {
	if (a.getRawBits() < b.getRawBits())
		return (a);
	return (b);
}
const Fixed & Fixed::max(const Fixed& a, const Fixed& b) {
	if (a.getRawBits() > b.getRawBits())
		return (a);
	return (b);
}

const std::string & Fixed::getName() const{
	return _name;
}

//*Private
int		Fixed::_toFixed(const int int_num) const{
	return (int_num << this->_fractionalBits);
}

int		Fixed::_toFixed(const float float_num) const{
	return (float_num * (float)(1 << this->_fractionalBits));
}

std::ostream & operator<<( std::ostream & o, const Fixed& rhs ) {
	o << rhs.toFloat();
	o << "\t";
	o << rhs.getName();
	return o;
}
