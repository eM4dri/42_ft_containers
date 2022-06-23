/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:49:56 by emadriga          #+#    #+#             */
/*   Updated: 2022/06/23 14:30:18 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Vector.hpp"
#include "Log.hpp"

 #include <vector>
 #include <string>
#define DEFAULT_NAME "Anonimous"

class Fixed{
	public:
		Fixed( void )
			: _rawBits(0), _name(DEFAULT_NAME), m_MemoryBlock(nullptr)
		{
			m_MemoryBlock = new int[5];
			LOG("Fixed default constructor");
		}

		Fixed( const int int_num )
			: _rawBits ( _toFixed( int_num ) ), _name(DEFAULT_NAME), m_MemoryBlock(nullptr)
		{
			m_MemoryBlock = new int[5];
			LOG("Fixed int constructor");
		}

		Fixed( const float float_num )
			: _rawBits ( _toFixed( float_num ) ), _name(DEFAULT_NAME), m_MemoryBlock(nullptr)
		{
			m_MemoryBlock = new int[5];
			LOG("Fixed float constructor");
		}

		Fixed( const Fixed& copy )
		{
			LOG("Fixed copy constructor");
			*this = copy;
		}

		~Fixed( void )
		{
			LOG("Fixed destructor");
			delete[] m_MemoryBlock;
		}

		Fixed & operator=( const Fixed& assign )
		{
			LOG("Fixed assign constructor");
			if (this != &assign)
			{
				_rawBits = assign.getRawBits();
				_name = assign.getName();
				m_MemoryBlock = new int[5];
			}
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
		
		const std::string & getName() const{
			return _name;
		}
		
	private:
			int 							_rawBits;
			static const int				_fractionalBits = 8;
			std::string						_name;
			int								*m_MemoryBlock;

};
std::ostream & operator<<( std::ostream & o, const Fixed& rhs ) {
	o << rhs.toFloat();
	o << "\t";
	o << rhs.getName();
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
	system("leaks containers");
}

int main()
{
	if (1)
		atexit(ft_exit);
	{	
		// std::vector<std::string> values;
		
		Vector<std::string> values;
		values.PushBack("ycarro");
		values.PushBack("jmatute");
		values.PushBack("jalvarad");
		values.PushBack("ycarro");
		values.PushBack("jmatute");
		values.PushBack("jalvarad");
		values.PopBack();
		//values.Print();
		PrintVector2(values);

		for (Vector<std::string>::iterator it = values.begin();
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
		// PrintVector2(values);
	}

}
