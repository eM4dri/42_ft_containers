/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:30:11 by emadriga          #+#    #+#             */
/*   Updated: 2023/02/13 12:02:08 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft{
	template <typename T1, typename T2>
	struct pair
	{
		public:
			typedef T1		first_type;
			typedef T2		second_type;
			
			first_type		m_first;
			second_type		m_second;

		public:
		///*	Member functions
			pair()
				:	m_first(), m_second() {}

			template< typename U1, typename U2 >
			pair( const pair<U1, U2>& copy )
				:	m_first( copy.m_second ), m_second( copy.m_second ) {}

			pair( const T1& x, const T2& y )
				:	m_first(x), m_second(y) {}

			~pair() {}

			pair& operator= (const pair& assign )
			{
				if (this != &assign)
				{
					m_first = assign.m_first;
					m_second = assign.m_second;
				}
				return *this;
			}

	};
	///*	Non Member functions
	template <typename T1,typename T2>
	pair<T1,T2> make_pair (T1 first, T2 second)
		{ return ( pair<T1,T2>(first, second) ); }

	template <typename T1, typename T2>
	bool operator== (const pair<T1,T2>& a, const pair<T1,T2>& b)
		{ return a.first == b.first && a.second == b.second; }

	template <typename T1, typename T2>
	bool operator!= (const pair<T1,T2>& a, const pair<T1,T2>& b)
		{ return !(a == b); }

	template <typename T1, typename T2>
	bool operator<  (const pair<T1,T2>& a, const pair<T1,T2>& b)
		{ return a.first < b.first || (!(b.first < a.first) && a.second < b.second); }

	template <typename T1, typename T2>
	bool operator<= (const pair<T1,T2>& a, const pair<T1,T2>& b)
		{ return !(b < a); }

	template <typename T1, typename T2>
	bool operator>  (const pair<T1,T2>& a, const pair<T1,T2>& b)
		{ return b < a; }

	template <typename T1, typename T2>
	bool operator>= (const pair<T1,T2>& a, const pair<T1,T2>& b)
		{ return !(a < b); }

}//namespace ft
