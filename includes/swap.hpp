/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 12:56:42 by emadriga          #+#    #+#             */
/*   Updated: 2023/02/14 14:51:07 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
    template<typename T>
    void swap ( T& a, T& b )
    {
        T tmp(a);
        a = b;
        b = tmp;
    }

}//namespace ft
