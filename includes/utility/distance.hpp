/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:11:45 by emadriga          #+#    #+#             */
/*   Updated: 2023/03/05 13:45:01 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../iterators/iterator_traits.hpp"

namespace ft
{
	template<typename It>
	typename ft::iterator_traits<It>::difference_type
		distance(It first, It last)
	{
		typename ft::iterator_traits<It>::difference_type result = 0;
		while (first != last) {
			++first;
			++result;
		}
		return result;
	}

}//namespace ft
