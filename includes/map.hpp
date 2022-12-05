/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:12:32 by emadriga          #+#    #+#             */
/*   Updated: 2022/12/05 17:29:13 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "bidirectional_iterator.hpp"
#include "reverse_iterator.hpp"
#include "enable_if.hpp"
#include "is_integral.hpp"
#include "lexicographical_compare.hpp"

namespace ft{
    template < class Key,                                           // map::key_type
           class T,                                                 // map::mapped_type
           class Compare = std::less<Key>,                          // map::key_compare
           class Alloc = std::allocator<std::pair<const Key,T> >    // map::allocator_type
           > 
    class map
    {
        public:
            typedef Key												            key_type;
            typedef T												            mapped_type;
            typedef Compare         								            key_compare;
            typedef typename allocator_type::reference  			            reference;
            typedef typename allocator_type::const_reference		            const_reference;
            typedef typename allocator_type::pointer				            pointer;
            typedef typename allocator_type::const_pointer			            const_pointer;
            typedef ft::bidirectional_iterator<pointer>							iterator;
            typedef ft::bidirectional_iterator<const_pointer>					const_iterator;
            typedef ft::reverse_iterator<iterator>								reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;
            typedef typename ft::iterator_traits<iterator>::difference_type 	difference_type;
            typedef typename allocator_type::size_type							size_type;
    };

}//namespace ft

