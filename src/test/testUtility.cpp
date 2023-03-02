/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testUtility.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:49:56 by emadriga          #+#    #+#             */
/*   Updated: 2023/03/02 18:03:51 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "test/testUtility.hpp"

//	private
static bool mycomp (char c1, char c2)
{ return std::tolower(c1)<std::tolower(c2); }

static void testLexicographicalCompare()
{
	char foo[]="Apple";
	char bar[]="apartment";
	std::cout << "Comparing foo and bar lexicographically (foo<bar):\n";
	std::cout << "Using default comparison (operator<): ";
	std::cout << NS::lexicographical_compare(foo,foo+5,bar,bar+9);
	std::cout << '\n';
	std::cout << "Using mycomp as comparison object: ";
	std::cout << NS::lexicographical_compare(foo,foo+5,bar,bar+9,mycomp) << std::endl;
	std::cout << "\t-------------\t" << std::endl;
}
//	public

void testUtility()
{
	performTest("Utility's lexicographical compare", &testLexicographicalCompare);
}
