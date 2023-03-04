/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Log.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:49:56 by emadriga          #+#    #+#             */
/*   Updated: 2023/03/04 09:58:47 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

#ifdef SHOW_CONS_DEST
# define LOG(X) std::cout << X << std::endl
# define LOG2(X,Y) std::cout << X << ": " << Y << std::endl
#else
# define LOG(X)
# define LOG2(X,Y)
#endif
