/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:30:11 by emadriga          #+#    #+#             */
/*   Updated: 2022/09/22 18:41:36 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft{
	template <class T1, class T2> struct pair{
		public:
			typedef T1		first_type;
			typedef T2		second_type;

		private:
			T1			first;
			T2			second;



		public:
		///*	Member functions
			pair(){}

			template< class U1, class U2 >
			pair( const pair<U1, U2>& p ) {}

			pair( const T1& x, const T2& y ) {}


	};
}//namespace ft
