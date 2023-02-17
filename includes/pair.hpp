/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:30:11 by emadriga          #+#    #+#             */
/*   Updated: 2023/02/17 12:08:34 by emadriga         ###   ########.fr       */
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

			first_type		first;
			second_type		second;

		///*	Member functions
			pair()
				:	first(), second() {}

			template< typename U1, typename U2 >
			pair( const pair<U1, U2>& copy )
				:	first(copy.first), second(copy.second) {}

			pair( const T1& x, const T2& y )
				:	first(x), second(y) {}

			~pair() {}

			pair& operator= (const pair& assign )
			{
				if (this != &assign)
				{
					first = assign.first;
					second = assign.second;
				}
				return *this;
			}

	};
	///*	Non Member functions
	template <typename T1,typename T2>
	ft::pair<T1,T2> make_pair (T1 first, T2 second)
		{ return ( ft::pair<T1,T2>(first, second) ); }

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
