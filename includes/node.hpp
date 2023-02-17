/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:26:25 by emadriga          #+#    #+#             */
/*   Updated: 2023/02/17 12:10:01 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>

namespace ft
{
	enum e_color { RED, BLACK };

	template< typename T, typename Alloc = std::allocator<T> >
	class node
	{
		public:
			typedef node*	node_ptr;

			T			val;
			e_color		color;
			node_ptr 	left, right, parent, next, prev;

			node(T val)
				: val(val)
			{
				parent = left = right = next = prev = NULL;
				// node is created during insertion
				// node is red at insertion
				color = RED;
			}

			node( const node & copy )
				: val(copy.val)
				{	operator=(copy);	}

			~node() {}

			node & operator = (const node & assign )
			{
				if (this != &assign)
				{
					val = assign.val;
					color = assign.color;
					left = assign.left;
					right = assign.right;
					parent = assign.parent;
					next = assign.next;
					prev = assign.prev;
				}
				return *this;
			}

			// returns pointer to uncle
			node *uncle()
			{
				// If no parent or grandparent, then no uncle
				if (parent == NULL || parent->parent == NULL)
					return NULL;

				if (parent->isOnLeft())
					// uncle on right
					return parent->parent->right;
				else
				// uncle on left
					return parent->parent->left;
			}

			// check if node is left child of parent
			bool isOnLeft() { return this == parent->left; }

			// returns pointer to sibling
			node *sibling()
			{
				// sibling null if no parent
				if (parent == NULL)
					return NULL;

				if (isOnLeft())
					return parent->right;

				return parent->left;
			}

			// moves node down and moves given node in its place
			void moveDown(node *nParent) {
				if (parent != NULL)
				{
					if (isOnLeft())
						parent->left = nParent;
					else
						parent->right = nParent;
				}
				nParent->parent = parent;
				parent = nParent;
			}

			bool hasRedChild()
			{
				return (left != NULL && left->color == RED) ||
					(right != NULL && right->color == RED);
			}
	};

}//namespace ft
