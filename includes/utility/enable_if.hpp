/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 20:51:21 by emadriga          #+#    #+#             */
/*   Updated: 2023/03/03 17:41:39 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
	template < bool Cond, typename T = void >
	struct enable_if {};

	template < typename T >
	struct enable_if<true, T>
	{
		typedef T type;
	};

}//namespace ft
