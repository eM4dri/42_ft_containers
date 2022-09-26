/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:30:11 by emadriga          #+#    #+#             */
/*   Updated: 2022/09/26 15:17:23 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft{
	template <class T1, class T2>
	struct pair
	{
		public:
			typedef T1		first_type;
			typedef T2		second_type;

		private:
			T1			m_first;
			T2			m_second;

		public:
		///*	Member functions
			pair()
				:	m_first(), m_second() {}

			template< class U1, class U2 >
			pair( const pair<U1, U2>& copy )
				:	m_first( copy.m_second ), m_second( copy.m_second ) {}

			pair( const T1& x, const T2& y )
				:	m_first(x), m_second(y) {}

			~pair() {}

			pair& operator= (const pair& assign )
			{
				if (*this != assign)
				{
					m_first = assign.m_first;
					m_second = assign.m_second;
				}
				return *this;
			}

	};
	///*	Non Member functions
	template <class T1,class T2>
	pair<T1,T2> make_pair (T1 x, T2 y)
		{ return ( pair<T1,T2>(x,y) ); }

	template <class T1, class T2>
	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return lhs.first==rhs.first && lhs.second==rhs.second; }

	template <class T1, class T2>
	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return !(lhs==rhs); }

	template <class T1, class T2>
	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

	template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return !(rhs<lhs); }

	template <class T1, class T2>
	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return rhs<lhs; }

	template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return !(lhs<rhs); }

}//namespace ft
