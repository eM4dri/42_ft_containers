/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:55:32 by emadriga          #+#    #+#             */
/*   Updated: 2023/02/16 10:43:37 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator_traits.hpp"
#include "node.hpp"
// #include <map>

namespace ft
{
	template<typename Node, typename Value>
	class tree_iterator
	{
		public:
			typedef Value						 									value_type;
			typedef value_type&						 								reference;
			typedef value_type*														pointer;
			typedef bidirectional_iterator_tag										iterator_category;
			typedef typename ft::iterator_traits<Node>::difference_type 			difference_type;
			typedef typename ft::iterator_traits<Node>::pointer 					node_pointer;

		private:
			node_pointer m_Node;

		public:
			tree_iterator()
				:	m_Node(NULL) { }

			template <class UNode, class UValue>
			tree_iterator(const tree_iterator<UNode, UValue> &src)
				: m_Node(src.getNode()) {}

			tree_iterator(node_pointer node)
				:	m_Node(node) {}

			tree_iterator( const tree_iterator & copy )
				:	m_Node(NULL)
				{	operator=(copy);	}

			~tree_iterator(){}

			tree_iterator & operator= ( const tree_iterator & assign )
			{
				if (this != &assign)
					m_Node = assign.getNode();
				return (*this);
			}

			template <class UNode, class UValue>
			tree_iterator & operator= ( const tree_iterator<UNode, UValue> & assign )
			{
				if (this != &assign)
					m_Node = assign.getNode();
				return (*this);
			}

			node_pointer getNode() const
				{ return m_Node; }

			tree_iterator & operator++ ()
			{
				m_Node = m_Node->next;
				return (*this);
			}

			tree_iterator  operator++ (int)
			{
				tree_iterator tmp(*this);
				++m_Node;
				return tmp;
			}

			tree_iterator & operator-- ()
			{
				m_Node = m_Node->previous;
				return (*this);
			}

			tree_iterator  operator-- (int)
			{
				tree_iterator tmp(*this);
				--m_Node;
				return tmp;
			}

			pointer operator-> () const
				{	return &m_Node->val;	}

			reference operator* () const
				{	return m_Node->val;	}

	};

	template <class UNode, class UValue, class VNode, class VValue>
	bool operator== (const tree_iterator<UNode, UValue>& a, const tree_iterator<VNode, VValue>& b)
		{	return a.getNode() == b.getNode();	}

	template <class UNode, class UValue, class VNode, class VValue>
	bool operator!= (const tree_iterator<UNode, UValue>& a,	const tree_iterator<VNode, VValue>& b)
		{	return !operator==(a, b);	}

}//namespace ft
