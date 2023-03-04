/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testCommon.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:49:56 by emadriga          #+#    #+#             */
/*   Updated: 2023/03/04 13:04:34 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDU_HPP
#define EDU_HPP

# include <iostream>
# include <string>			//	std::string
# include <stack>			//	std::stack
# include <vector>			//	std::vector
# include <map>				//	std::map
# include <set>				//	std::set
# include <list>			//	std::list
# include "Fixed.hpp"
# ifndef NS
# define NS ft
# endif
void performTest(std::string title, void (*f)());

#endif
