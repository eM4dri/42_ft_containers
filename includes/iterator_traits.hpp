/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:55:32 by emadriga          #+#    #+#             */
/*   Updated: 2022/09/22 16:13:02 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator.hpp"
#include <iostream>
#include <cstddef>

namespace ft
{
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
		typedef T									value_type;
		typedef T*									pointer;
		typedef T&									reference;
		typedef ptrdiff_t							difference_type;
		typedef std::random_access_iterator_tag		iterator_category;
	};

	template<class T>
	struct iterator_traits<const T*>
	{
		typedef T									value_type;
		typedef T const *							pointer;
		typedef T const &							reference;
		typedef ptrdiff_t							difference_type;
		typedef std::random_access_iterator_tag		iterator_category;
	};

}//namespace ft
