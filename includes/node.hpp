/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:26:25 by emadriga          #+#    #+#             */
/*   Updated: 2022/12/06 18:34:02 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>

namespace ft
{
	enum COLOR { RED, BLACK };

	template<class T>
	class node
	{
		public:
			T		val;
			COLOR	color;
			node 	*left, *right, *parent, *next, *prev;

			node(T val)
				: val(val)
			{
				parent = left = right = next = prev = NULL;
				// node is created during insertion
				// node is red at insertion
				color = RED;
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
