/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testSet.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:49:56 by emadriga          #+#    #+#             */
/*   Updated: 2023/02/27 08:54:59 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test/testSet.hpp"

#define T1 int
/// https://www.technical-recipes.com/2012/how-to-convert-const_iterators-to-iterators-using-stddistance-and-stdadvance/
void testThisSet()
{
	NS::set<T1> const st;
	NS::set<T1>::iterator it = st.begin(); // <-- no error, actually ! set allows for const_iterator => iterator conversion

	(void)it;
}
