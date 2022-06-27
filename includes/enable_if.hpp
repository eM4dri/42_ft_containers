/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 20:51:21 by emadriga          #+#    #+#             */
/*   Updated: 2022/06/27 20:56:47 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
	template<bool Cond, class T = void> 
	struct enable_if {};

	template<class T>
	struct enable_if<true, T> 
	{	
		typedef T type; 
	};

}