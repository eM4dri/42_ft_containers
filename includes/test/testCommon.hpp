/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testCommon.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:49:56 by emadriga          #+#    #+#             */
/*   Updated: 2023/03/09 12:02:57 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTCOMMON_HPP
#define TESTCOMMON_HPP

# include <iostream>
# include <string>			//	std::string
# include <stack>			//	std::stack
# include <vector>			//	std::vector
# include <map>				//	std::map
# include <set>				//	std::set
# include <list>			//	std::list
# include "Fixed.hpp"
# include "testVector.hpp"
# include "testStack.hpp"
# include "testUtility.hpp"
# include "testMap.hpp"
# include "testSet.hpp"
# include "testTree.hpp"
# ifndef NS
# define NS ft
# endif
	void performTest(std::string title, void (*f)());
#endif
