/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:49:56 by emadriga          #+#    #+#             */
/*   Updated: 2022/06/22 17:52:32 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Vector.hpp"
#include "Log.hpp"

// #include <vector>

class Fixed{
	public:
		Fixed( void ): _rawBits(0){
			LOG("Fixed default constructor");
		}

		Fixed( const int int_num ): _rawBits ( _toFixed( int_num ) ) {
			LOG("Fixed fields constructor");
		}

		Fixed( const float float_num ): _rawBits ( _toFixed( float_num ) ){
			LOG("Fixed fields constructor");
		}

		Fixed( const Fixed& src ){
			LOG("Fixed copy constructor");
			*this = src;
		}

		~Fixed( void ){
			LOG("Fixed destructor");
		}

		Fixed & operator=( const Fixed& rhs ){
			if (this != &rhs)
				this->_rawBits = rhs.getRawBits();
			return *this;
		}

		int 	getRawBits( void ) const{
			return this->_rawBits;
		}

		void  setRawBits ( const int raw ){
			this->_rawBits = raw;
		}

		int		toInt(void) const{
			return (this->_rawBits >> this->_fractionalBits);
		}

		float	toFloat(void) const{
			return ((float)this->_rawBits / (float)(1 << this->_fractionalBits));
		}
		bool	 	operator > ( const Fixed& rhs )const{
			return ( this->getRawBits() > rhs.getRawBits() );
		}
		bool	 	operator < ( const Fixed& rhs )const{
			return ( this->getRawBits() < rhs.getRawBits() );
		}
		bool	 	operator >= ( const Fixed& rhs ){
			return ( this->getRawBits() >= rhs.getRawBits() );
		}
		bool	 	operator <= ( const Fixed& rhs ){
			return ( this->getRawBits() <= rhs.getRawBits() );
		}
		bool	 	operator == ( const Fixed& rhs ){
			return ( this->getRawBits() == rhs.getRawBits() );
		}
		bool	 	operator != ( const Fixed& rhs ){
			return ( this->getRawBits() != rhs.getRawBits() );
		}
		Fixed	 	operator + ( const Fixed& rhs ){
			Fixed result;
			result.setRawBits(this->getRawBits() + rhs.getRawBits());
			return ( result );
		}
		Fixed	 	operator - ( const Fixed& rhs ){
			Fixed result;
			result.setRawBits(this->getRawBits() - rhs.getRawBits());
			return ( result );
		}
		Fixed	 	operator * ( const Fixed& rhs ){
			float result;
			result = this->toFloat() * rhs.toFloat();
			return (Fixed(result));
		}
		Fixed	 	operator / ( const Fixed& rhs ){
			float result;
			result = this->toFloat() / rhs.toFloat();
			return (Fixed(result));
		}
		Fixed&	 	operator ++ ( void ){
			this->setRawBits(this->getRawBits() + 1);
			return ( *this );
		}
		Fixed	 	operator ++ ( int ){
			Fixed output(*this);
			this->setRawBits(this->getRawBits() + 1);
			return ( output );
		}
		Fixed&	 	operator -- ( void ){
			this->setRawBits(this->getRawBits() - 1);
			return ( *this );
		}
		Fixed	 	operator -- ( int ){
			Fixed output(*this);
			this->setRawBits(this->getRawBits() - 1);
			return ( output );
		}
			
		Fixed & min(Fixed& a, Fixed& b){
			if (a.getRawBits() < b.getRawBits())
				return (a);
			return (b);
		}
		Fixed & max(Fixed& a, Fixed& b){
			if (a.getRawBits() > b.getRawBits())
				return (a);
			return (b);
		}
		const Fixed & min(const Fixed& a, const Fixed& b) {
			if (a.getRawBits() < b.getRawBits())
				return (a);
			return (b);
		}
		const Fixed & max(const Fixed& a, const Fixed& b) {
			if (a.getRawBits() > b.getRawBits())
				return (a);
			return (b);
		}

		//*Private
		int		_toFixed(const int int_num) const{
			return (int_num << this->_fractionalBits);
		}

		int		_toFixed(const float float_num) const{
			return (float_num * (float)(1 << this->_fractionalBits));
		}
		
	private:
			int 				_rawBits;
			static const int	_fractionalBits = 8; 

};
std::ostream & operator<<( std::ostream & o, const Fixed& rhs ) {
	o << rhs.toFloat();
	return o;
}

template<typename T>
void PrintVector( const Vector<T> & vector)
{
	std::cout << "Vector size "<< vector.Size() << std::endl;
	for (size_t i = 0; i < vector.Size(); i++)
		std::cout << vector[i] << std::endl;
	std::cout << "\t-------------\t" << std::endl;	
}

template<typename T>
void PrintVector2( const Vector<T> & vector)
{
	for (VectorIterator< Vector <T> > it = vector.begin(); 
		it != vector.end(); it++)
		std::cout << *it << std::endl;
	std::cout << "\t-------------\t" << std::endl;		
}

void ft_exit(void)
{
	system("leaks interns");
}

int main()
{
	if (0)
		atexit(ft_exit);
	{	
		Vector<std::string> values;
		values.PushBack("ycarro");
		values.PushBack("jmatute");
		values.PushBack("jalvarad");
		values.Print();

		for (Vector<std::string>::Iterator it = values.begin();
			it != values.end(); it++)
			std::cout << *it << std::endl;
		std::cout << "\t-------------\t" << std::endl;
	}
	{	
		Vector<Fixed> values;
		values.PushBack(42.42f);
		values.PushBack(0);
		values.PushBack(5.2f);
		values.PopBack();
		values.Print();
		PrintVector2(values);
	}

}
