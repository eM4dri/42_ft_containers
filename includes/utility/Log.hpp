/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Log.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:49:56 by emadriga          #+#    #+#             */
/*   Updated: 2023/03/05 14:22:32 by emadriga         ###   ########.fr       */
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

#ifdef COMPARE
# define DIFF 1
#else
# define DIFF 0
#endif

#ifdef PLUS
# define EXTRA 1
#else
# define EXTRA 0
#endif
