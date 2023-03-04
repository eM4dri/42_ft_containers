/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:11:45 by emadriga          #+#    #+#             */
/*   Updated: 2023/03/04 11:52:34 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
	template<typename InputIterator, typename OutputIterator>
	OutputIterator copy (InputIterator first, InputIterator last, OutputIterator result)
	{
		while (first!=last) 
		{
			*result = *first;
			++result; ++first;
		}
		return result;
	}

}//namespace ft
