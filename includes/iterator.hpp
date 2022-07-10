/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:55:32 by emadriga          #+#    #+#             */
/*   Updated: 2022/07/10 21:25:59 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <cstddef>

namespace ft
{

	struct input_iterator_tag {}; // LegacyInputIterator .
	struct output_iterator_tag {}; // LegacyOutputIterator 
	struct forward_iterator_tag			: public input_iterator_tag {};  // LegacyForwardIterator
	struct bidirectional_iterator_tag	: public forward_iterator_tag {};  //  LegacyBidirectionalIterator
	struct random_access_iterator_tag	: public bidirectional_iterator_tag {}; // LegacyRandomAccessIterator

		/*  Check iterator_tag*/

	template <bool is_valid, typename T>
		struct check_iterator_tag
		{
			typedef T type;
			const static bool value = is_valid;
		};
	

	template< typename T >
		struct is_input_it_tag : public check_iterator_tag <false , T> {};
		
	template<>
		struct is_input_it_tag<ft::input_iterator_tag> : public check_iterator_tag<true, ft::input_iterator_tag> {};
		
	template<>
		struct is_input_it_tag<ft::output_iterator_tag> : public check_iterator_tag<true, ft::output_iterator_tag> {};

	template<>
		struct is_input_it_tag<ft::forward_iterator_tag> : public check_iterator_tag<true, ft::forward_iterator_tag> {};
		
	template<>
		struct is_input_it_tag<ft::bidirectional_iterator_tag> : public check_iterator_tag<true, ft::bidirectional_iterator_tag> {};
		
	template<>
		struct is_input_it_tag<ft::random_access_iterator_tag> : public check_iterator_tag<true, ft::random_access_iterator_tag> {};


	template< typename T >
		struct __is_forward_iterator: public check_iterator_tag <false , T> {};
	template<>
		struct __is_forward_iterator <ft::forward_iterator_tag> : public check_iterator_tag<true, ft::forward_iterator_tag> {};
	template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator {
		typedef T         value_type;
		typedef Distance  difference_type;
		typedef Pointer   pointer;
		typedef Reference reference;
		typedef Category  iterator_category;
	};

	template<class Iter>
	struct iterator_traits 
	{
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::iterator_category	iterator_category;
	};

	template<class T>
	struct iterator_traits<T*> 
	{
		typedef T										value_type;
		typedef T*										pointer;
		typedef T&										reference;
		typedef ptrdiff_t								difference_type;
		typedef std::random_access_iterator_tag			iterator_category;
	};

	template<class T>
	struct iterator_traits<const T*> 
	{
		typedef T										value_type;
		typedef T const *								pointer;
		typedef T const &								reference;
		typedef ptrdiff_t								difference_type;
		typedef std::random_access_iterator_tag			iterator_category;
	};

}//namespace ft
