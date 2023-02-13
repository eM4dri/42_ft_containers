/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:12:32 by emadriga          #+#    #+#             */
/*   Updated: 2023/02/13 14:24:36 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <map>
#include "tree_iterator.hpp"
#include "red_black_tree.hpp"
// #include "reverse_tree_iterator.hpp"
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
            typedef typename pair<const key_type,mapped_type>                   value_type;
            typedef Compare 								                    key_compare;
            typedef Alloc                                                       allocator_type;
            typedef typename allocator_type::reference			                reference;
            typedef typename allocator_type::const_reference		            const_reference;
            typedef typename allocator_type::pointer				            pointer;
            typedef typename allocator_type::const_pointer			            const_pointer;
            // typedef ft::tree_iterator<Node, value_type>				        iterator;
            // typedef ft::bidirectional_iterator<const_pointer>		        const_iterator;
            // typedef ft::reverse_iterator<iterator>							reverse_iterator;
            // typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;
            typedef typename ft::iterator_traits<iterator>::difference_type 	difference_type;
            typedef typename allocator_type::size_type							size_type;

            
        private:
            typedef ft::red_black_tree<value_type>  tree_type;
            
            allocator_type                      m_Allocate;
            tree_type                           m_Tree;
            size_type                           m_Size;

        public:
        ///*	Member functions
            explicit map (  const key_compare& comp = key_compare(),
                            const allocator_type& alloc = allocator_type())
                :	m_Allocate(alloc), m_Tree(comp), m_Size(0) {};

            template <class InputIterator>
            map (   InputIterator first, 
                    InputIterator last,
                    const key_compare& comp = key_compare(),
                    const allocator_type& alloc = allocator_type())
                :   m_Allocate(alloc), m_Tree(comp), m_Size(0) 
                {   insert(first, last);    };

            map (const map& copy)
                :	m_Allocate(alloc), m_Tree(comp), m_Size(0)
				{	operator=(copy);	}
                
            ~map()	{	clear();	}

            map& operator= (const map & assign )
			{
				if (this != &assign)
				{
					if (m_Size > 0)
					    clear();
					m_Allocate = assign.get_allocator();
					insert(assign.begin(), assign.end());
				}
				return *this;
			}

        ///*	Iterators
			iterator begin()	{	return m_Tree.begin();	}
			const_iterator begin() const	{	return m_Tree.begin();	}

			iterator end()	{	return m_Tree.end();	}
			const_iterator end() const	{	return m_Tree.end();	}

            reverse_iterator rbegin()	{	return reverse_iterator(end());	}
			const_reverse_iterator rbegin() const	{	return const_reverse_iterator(end());	}

			reverse_iterator rend()	{	return reverse_iterator(begin());	}
			const_reverse_iterator rend() const	{	return const_reverse_iterator(begin());	}


        ///*	Capacity
            bool empty() const  {   return m_Tree.empty();   }
        


            
        ///*	Element access
            mapped_type& operator[] (const key_type& key) 
            {   
                node_ptr node = m_Tree.find(key);
                if (!node)
                {
                    return  (*((this->insert(make_pair(k,mapped_type()))).first)).second;
                }
                return node->val.second
            }
        


		///* Allocator
			allocator_type get_allocator() const	{ return m_Allocate; }
    }
    
    
    
    
    
    
    
    ;

}//namespace ft

