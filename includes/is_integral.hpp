/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 20:56:13 by emadriga          #+#    #+#             */
/*   Updated: 2022/09/22 16:13:05 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
	template <class T>
	struct	is_integral
		{	static const bool value = false;	};

	template<>
	struct is_integral<bool>
		{	static const bool value = true;	};

	template<>
	struct is_integral<char>
		{	static const bool value = true;	};

	template<>
	struct is_integral<char16_t>
		{	static const bool value = true;	};

	template<>
	struct is_integral<char32_t>
		{	static const bool value = true;	};

	template<>
	struct is_integral<wchar_t>
		{	static const bool value = true;	};

	template<>
	struct is_integral<signed char>
		{	static const bool value = true;	};

	template<>
	struct is_integral<short int>
		{	static const bool value = true;	};

	template<>
	struct is_integral<int>
		{	static const bool value = true;	};

	template<>
	struct is_integral<long int>
		{	static const bool value = true;	};

	// template<>
	// struct is_integral<long long int>
	// 	{	static const bool value = true;	};

	template<>
	struct is_integral<unsigned char>
		{	static const bool value = true;	};

	template<>
	struct is_integral<unsigned short int>
		{	static const bool value = true;	};

	template<>
	struct is_integral<unsigned int>
		{	static const bool value = true;	};

	template<>
	struct is_integral<unsigned long int>
		{	static const bool value = true;	};

	// template<>
	// struct is_integral<unsigned long long int>
	// 	{	static const bool value = true;	};

}//namespace ft
