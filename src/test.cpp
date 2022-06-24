/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:49:56 by emadriga          #+#    #+#             */
/*   Updated: 2022/06/25 01:02:43 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "vector.hpp"
#include <vector>
#include <string>
#define DEFAULT_NAME "Anonimous"

#define NS ft

enum logLevel { VECTOR, FIXED };
static const char *logLevel[] =
	{ "vector", "fixed" };

class Fixed{
	public:
		Fixed( void )
			: _rawBits(0), _name(DEFAULT_NAME), m_MemoryBlock(nullptr)
		{
			m_MemoryBlock = new int[5];
			setMemoryBlock(0, -1, -2, -3);
			LOG("Fixed default constructor");
		}

		Fixed( const int int_num )
			: _rawBits ( _toFixed( int_num ) ), _name(DEFAULT_NAME), m_MemoryBlock(nullptr)
		{
			m_MemoryBlock = new int[5];
			setMemoryBlock(0, 10, 20, 30);
			LOG("Fixed int constructor");
		}

		Fixed( const float float_num )
			: _rawBits ( _toFixed( float_num ) ), _name(DEFAULT_NAME), m_MemoryBlock(nullptr)
		{
			m_MemoryBlock = new int[5];
			setMemoryBlock(0, 11, 222, 3333);
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
				setMemoryBlock(0, 1, 2, 3);
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

		const int & getMemoryBlock(size_t index) const{
			return m_MemoryBlock[index];

		}
		
		void setMemoryBlock(const int &a, const int &b, const int &c, const int &d){
			m_MemoryBlock[0] = a;
			m_MemoryBlock[1] = b;
			m_MemoryBlock[2] = c;
			m_MemoryBlock[3] = d;
			m_MemoryBlock[4] = 42;
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
	o << "\t(";
	o << rhs.getMemoryBlock(0);
	o << ", ";
	o << rhs.getMemoryBlock(1);
	o << ", ";
	o << rhs.getMemoryBlock(2);
	o << ", ";
	o << rhs.getMemoryBlock(3);
	o << ", ";
	o << rhs.getMemoryBlock(4);
	o << ")";
	return o;
}

void ft_exit(void)
{
	system("leaks containers");
}

int main(int argc, char **argv)
{
	if (0)
		atexit(ft_exit);
	if (argc == 1 || !strcmp( argv[1], logLevel[VECTOR] ) )
	{
		NS::vector<std::string> vector;
		vector.push_back("1 ycarro");
		vector.push_back("2 jmatute");
		vector.push_back("3 jalvarad");
		vector.push_back("4 tomartin");
		vector.push_back("5 crisfern");
		vector.push_back("6 agallipo");
		NS::vector<std::string>::iterator it  = vector.begin();
		it++;
		it++;
		it = vector.insert(it,"extra emadriga");
		vector.pop_back();
		
		std::cout << "Print vector using [] & size" << std::endl;
		std::cout << "Vector size "<< vector.size() << std::endl;
		for (size_t i = 0; i < vector.size(); i++)
			std::cout << vector[i] << std::endl;
		std::cout << "\t-------------\t" << std::endl;	
		
		std::cout << "Print vector using iterator" << std::endl;
		for (NS::vector<std::string>::iterator it  = vector.begin();
			it != vector.end(); it++)
			{
				std::cout << *it << std::endl;
			}
		std::cout << "\t-------------\t" << std::endl;

		std::cout << "Print vector using reverse iterator" << std::endl;
		for (NS::vector<std::string>::reverse_iterator it  = vector.rbegin();
			it != vector.rend(); it++)
			{
				std::cout << *it << std::endl;
			}
		std::cout << "\t-------------\t" << std::endl;
	}

	if (argc == 1 || !strcmp(argv[1], logLevel[VECTOR]) || !strcmp(argv[1], logLevel[FIXED] ) )
	{
		NS::vector<Fixed> vector;
		vector.push_back(42.42f);
		vector.push_back(0);
		vector.push_back(5.2f);
		vector.push_back(0);
		vector.pop_back();
		
		std::cout << "Print vector using [] & size" << std::endl;
		std::cout << "Vector size "<< vector.size() << std::endl;
		for (size_t i = 0; i < vector.size(); i++)
			std::cout << vector[i] << std::endl;
		std::cout << "\t-------------\t" << std::endl;	
		
		std::cout << "Print vector using iterator" << std::endl;
		for (NS::vector<Fixed>::iterator it  = vector.begin();
			it != vector.end(); it++)
			{
				std::cout << *it << std::endl;
			}
		std::cout << "\t-------------\t" << std::endl;

		std::cout << "Print vector using reverse iterator" << std::endl;
		for (NS::vector<Fixed>::reverse_iterator it  = vector.rbegin();
			it != vector.rend(); it++)
			{
				std::cout << *it << std::endl;
			}
		std::cout << "\t-------------\t" << std::endl;
	}

}
