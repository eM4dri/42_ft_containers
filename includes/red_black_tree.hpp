/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:26:19 by emadriga          #+#    #+#             */
/*   Updated: 2023/02/23 17:33:30 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <memory>
#include "node.hpp"
#include "pair.hpp"
#include "swap.hpp"
#include "tree_iterator.hpp"
#include "reverse_iterator.hpp"
#define RESET_COLOR   "\033[0m"
// #define BLACK   "\033[30m"      /* Black */
#define RED_COLOR     "\033[31m"      /* Red */

namespace ft
{
	enum e_compare { BIG, SMALL  };
	
	// KeyOfVal functor for map
	template < typename Key,
			typename Val /* = ft::pair<Key, typename T> */ >
	struct map_get_key {
		const Key operator()(const Val& value) const {
			return value.first;
		}
	};

	// KeyOfVal functor for set
	template < typename Key >
	struct set_get_key {
		const Key operator()(const Key& value) const {
			return value;
		}
	};

	
	// template< typename T, class Alloc = std::allocator<T> >
	template <	typename Key,
				typename Val,
				typename KeyOfVal,
				typename Compare = std::less<Key>,
				typename Alloc = std::allocator<Val> >
	class red_black_tree
	{
		public:
			typedef	Key													key_type;
			typedef	Val													value_type;
			typedef Compare												key_compare;
			typedef KeyOfVal											key_extractor;
			typedef Alloc												allocator_type;
			// typedef typename allocator_type::size_type			size_type;
			typedef node<Val>												node_type;
			// get another allocator.
			typedef typename Alloc::
					template rebind<node_type>::other					node_allocator;
			typedef typename node_allocator::pointer					node_ptr;
  			typedef typename node_allocator::const_pointer				const_node_ptr;
			typedef ft::tree_iterator<node_ptr, Val>					iterator;
			typedef ft::tree_iterator<const_node_ptr, const Val>		const_iterator;
			typedef ft::reverse_iterator<iterator>						reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;
			typedef typename allocator_type::size_type					size_type;

		private:
			node_allocator 		m_Allocate;
			key_compare			m_Compare;
			node_ptr			m_Root;
			node_ptr			m_End;
			size_type			m_Size;
			key_extractor		m_GetKey;


			// left rotates the given node
			void leftRotate(node_ptr x)
			{
				// new parent will be node's right child
				node_ptr nParent = x->right;

				// update root if current node is root
				if (x == m_Root)
					m_Root = nParent;

				x->moveDown(nParent);

				// connect x with new parent's left element
				x->right = nParent->left;
				// connect new parent's left element with node
				// if it is not null
				if (nParent->left != NULL)
				nParent->left->parent = x;

				// connect new parent with x
				nParent->left = x;
			}

			void rightRotate(node_ptr x)
			{
				// new parent will be node's left child
				node_ptr nParent = x->left;

				// update root if current node is root
				if (x == m_Root)
					m_Root = nParent;

				x->moveDown(nParent);

				// connect x with new parent's right element
				x->left = nParent->right;
				// connect new parent's right element with node
				// if it is not null
				if (nParent->right != NULL)
					nParent->right->parent = x;

				// connect new parent with x
				nParent->right = x;
			}

			// fix red red at given node
			void fixRedRed(node_ptr x)
			{
				// if x is root color it black and return
				if (x == m_Root)
				{
					x->color = BLACK;
					return;
				}

				// initialize parent, grandparent, uncle
				node_ptr parent = x->parent;
				node_ptr uncle = x->uncle();
				node_ptr grandparent = parent->parent;

				if (parent->color != BLACK)
				{
					if (uncle != NULL && uncle->color == RED)
					{
						// uncle red, perform recoloring and recurse
						parent->color = BLACK;
						uncle->color = BLACK;
						grandparent->color = RED;
						fixRedRed(grandparent);
					}
					else
					{
						// Else perform LR, LL, RL, RR
						if (parent->isOnLeft())
						{
							if (x->isOnLeft())
							{
								// for left right
								ft::swap(parent->color, grandparent->color);
							}
							else
							{
								leftRotate(parent);
								ft::swap(x->color, grandparent->color);
							}
							// for left left and left right
							rightRotate(grandparent);
						}
						else
						{
							if (x->isOnLeft())
							{
								// for right left
								rightRotate(parent);
								ft::swap(x->color, grandparent->color);
							}
							else
							{
								ft::swap(parent->color, grandparent->color);
							}

							// for right right and right left
							leftRotate(grandparent);
						}
					}
				}
			}

			// find node that do not have a left child
			// in the subtree of the given node
			node_ptr successor(node_ptr x)
			{
				node_ptr temp = x;

				while (temp->left != NULL)
				{
					// std::cout << "HOLAHOLA\t" << std::endl;
					temp = temp->left;
				}

				return temp;
			}

			// find node that replaces a deleted node in BST
			node_ptr BSTreplace(node_ptr x)
			{
				// when node have 2 children
				if (x->left != NULL && x->right != NULL)
					return successor(x->right);

				// when leaf
				if (x->left == NULL && x->right == NULL)
					return NULL;

				// when single child
				if (x->left != NULL)
					return x->left;
				else
					return x->right;
			}

			//deletes node fixing prev a next nodes redirection nodes previosly
			void deleteThisNode(node_ptr node)
			{
				if (node->prev != NULL)
					node->prev->next = node->next;
				if (node->next != NULL)
					node->next->prev = node->prev;
				destroyNode(node);
			}

			// deletes the given node
	/*comp*/void deleteNode(node_ptr v)
			{
				if (size() == 1)
				{
					destroyNode(m_Root);
					m_Root = m_End;
					return;
				}
				// std::cout << "HEY\t" << std::endl;
				
				node_ptr u = BSTreplace(v);

				// True when u and v are both black
				bool uvBlack = ((u == NULL || u->color == BLACK) && (v->color == BLACK));
				node_ptr parent = v->parent;

				if (u == NULL)
				{
					// std::cout << "HEY\tWEY" << std::endl;
					// u is NULL therefore v is leaf
					if (v == m_Root)
					{
						// v is root, making root null
						m_Root = NULL;
					}
					else
					{
						if (uvBlack)
						{
							// std::cout << "HEY\tWEY\tYEY" << std::endl;
							// u and v both black
							// v is leaf, fix double black at v
							fixDoubleBlack(v);
						}
						else
						{
							// u or v is red
							if (v->sibling() != NULL)
								// sibling is not null, make it red"
								v->sibling()->color = RED;
						}

						// delete v from the tree
						if (v->isOnLeft())
							parent->left = NULL;
						else
							parent->right = NULL;
					}
					deleteThisNode(v);
					return;
				}

				if (v->left == NULL || v->right == NULL)
				{
					// std::cout << "HEY\tWEY\tHEY" << std::endl;
					// v has 1 child
					if (v == m_Root)
					{
						// v is root, assign the value of u to v, and delete u
						// swapEverithingButValues(u , v);
						// if (u->parent != NULL)
						// {
						// 	if (u->parent->left != NULL && u->parent->left == v)
						// 		u->parent->left = u;
						// 	else if (u->parent->right != NULL && u->parent->right == v)
						// 		u->parent->right = u;
						// }
						// if ( v->parent != NULL)
						// {
						// 	if (v->parent->left != NULL && v->parent->left == u)
						// 		v->parent->left = v;
						// 	else if (v->parent->right != NULL && v->parent->right == u)
						// 		v->parent->right = v;	
						// }
						
						// v->val = u->val;
						u->left = u->right = u->prev = NULL;
						u->next = m_End;
						m_Root = u;
						m_End->prev = m_Root;
						deleteThisNode(v);
					}
					else
					{
						// Detach v from tree and move u up
						if (v->isOnLeft())
							parent->left = u;
						else
							parent->right = u;
						deleteThisNode(v);
						u->parent = parent;
						if (uvBlack)
						{
							// u and v both black, fix double black at u
							fixDoubleBlack(u);
						}
						else
						{
							// u or v red, color u black
							u->color = BLACK;
						}
					}
					return;
				}

				// v has 2 children, swap values with successor and recurse
				std::cout << "u " << u << std::endl;
				printfThisNode(u);
				std::cout << "v " << v << std::endl;
				printfThisNode(v);
				swapEverithingButValues(u , v);
				std::cout << "u " << u << std::endl;
				printfThisNode(u);
				std::cout << "v " << v << std::endl;
				printfThisNode(v);
				// if (v == m_Root)
				// 	m_Root = u;
				// std::cout << "HOLA\t" << std::endl;
				deleteNode(v);
				// deleteNode(u);
			}

			// ft::swap(u->val , v->val);
			// deleteNode(u);

			void printfThisNode(node_ptr node)
			{
				std::cout << "\tfirst: " << node->val.first;
				std::cout << "\tsecond: " << node->val.second;
				std::cout << "\tparent: " << node->parent;
				std::cout << "\tleft: " << node->left;
				std::cout << "\n\tprev: " << node->prev;
				std::cout << "\tnext: " << node->next;
				std::cout << "\tright: " << node->right;
				
				
				std::cout << std::endl;

				
			}
			void swapValues(node_ptr u, node_ptr v)
			{
				Val temp;
				temp = u->val;
				u->val = v->val;
				v->val = temp;
			}

			void swapEverithingButValues(node_ptr u, node_ptr v)
			{
				ft::swap(u->color, v->color);
				ft::swap(u->parent, v->parent);
				ft::swap(u->next, v->next);
				ft::swap(u->prev, v->prev);
				ft::swap(u->left, v->left);
				ft::swap(u->right, v->right);
				if (u->parent != NULL)
				{
					if (u->parent->left != NULL && u->parent->left == v)
						u->parent->left = u;
					else if (u->parent->right != NULL && u->parent->right == v)
						u->parent->right = u;
				}
				if ( v->parent != NULL )
				{
					if (v->parent->left != NULL && v->parent->left == u)
						v->parent->left = v;
					else if (v->parent->right != NULL && v->parent->right == u)
						v->parent->right = v;	
				}
				if (u->next != NULL)
					u->next->prev = v;
				if (v->next != NULL)
					v->next->prev = u;
				if (u->prev != NULL)
					u->prev->next = v;
				if (v->prev != NULL)
					v->prev->next = u;
				// node_ptr tmp1= NULL;
				// node_ptr tmp2 = NULL;
				// if (u->next != NULL)
				// 	 tmp1 = u;
				// if (v->next != NULL)
				// 	tmp2 = v;
				// if (tmp1 != NULL)
				// 	u->next->prev = tmp1;
				// if (tmp2 != NULL)
				// 	v->next->prev = tmp2;
			}

	/*comp*/void fixDoubleBlack(node_ptr x)
			{
				if (x == m_Root)
					// Reached root
					return;
				node_ptr sibling = x->sibling(), parent = x->parent;
				if (sibling == NULL)
				{
					// No sibiling, double black pushed up
					fixDoubleBlack(parent);
				}
				else
				{
					if (sibling->color == RED)
					{
						// Sibling red
						parent->color = RED;
						sibling->color = BLACK;
						if (sibling->isOnLeft())
						{
							// left case
							rightRotate(parent);
						}
						else
						{
							// right case
							leftRotate(parent);
						}
						fixDoubleBlack(x);
					}
					else
					{
						// Sibling black
						if (sibling->hasRedChild())
						{
							// at least 1 red children
							if (sibling->left != NULL && sibling->left->color == RED)
							{
								if (sibling->isOnLeft())
								{
									// left left
									sibling->left->color = sibling->color;
									sibling->color = parent->color;
									rightRotate(parent);
								}
								else
								{
									// right left
									sibling->left->color = parent->color;
									rightRotate(sibling);
									leftRotate(parent);
								}
							}
							else
							{
								if (sibling->isOnLeft())
								{
									// left right
									sibling->right->color = parent->color;
									leftRotate(sibling);
									rightRotate(parent);
								}
								else
								{
									// right right
									sibling->right->color = sibling->color;
									sibling->color = parent->color;
									leftRotate(parent);
								}
							}
							parent->color = BLACK;
						}
						else
						{
							// 2 black children
							sibling->color = RED;
							if (parent->color == BLACK)
								fixDoubleBlack(parent);
							else
								parent->color = BLACK;
						}
					}
				}
			}

			// prints level order for given node
			void levelOrder(node_ptr x, const int nodeLevel)
			{
				const int sonLevel = nodeLevel + 1;
				if (x == NULL)
					return;
				for (int i = 0; i < nodeLevel; i++)
					std::cout << "\t";
				if (!x->color)
					std::cout << RED_COLOR;
				std::cout << x->val << "|";
				std::cout << (!x->color ? 'R' : 'B') << std::endl;
				std::cout << RESET_COLOR;
				levelOrder(x->left, sonLevel);
				levelOrder(x->right, sonLevel);
			}

			// prints inorder recursively
			void inorder(node_ptr x)
			{
				if (x == NULL)
					return;
				inorder(x->left);
				std::cout << m_GetKey(x->val) << " ";
				inorder(x->right);
			}

			// prints inorderdesc recursively
			void inorderdesc(node_ptr x)
			{
				if (x == NULL)
					return;
				inorderdesc(x->right);
				std::cout << x->val << " ";
				inorderdesc(x->left);
			}

			void destroyNode(node_ptr node)
			{
				m_Allocate.destroy(node);
				m_Allocate.deallocate(node, 1);
				m_Size--;
				node = NULL;
			}

			void destroyAllNodes(node_ptr x)
			{
				if (x == NULL)
					return;
				// std::cout << " x " << &x << " : " << x << '\n';
				// if (x->left != NULL)
					destroyAllNodes(x->left);
				// if (x->right != NULL)
					destroyAllNodes(x->right);
				destroyNode(x);
				// x = NULL;
			}

		public:
			void clear()
			{
				// if (m_Root != NULL && m_GetKey(m_Root->val) != 0)

				if ( m_Root != m_End )
				{
					destroyAllNodes(m_Root);
					
					// m_End = NULL;
					// m_Size = 0;
					m_Root = m_End;
				}
			}

			// void deleteTreeNode (iterator position)
			// {
			// 	deleteNode(position);
			// }

			// no need to swap m_Allocate & m_Compare shared types from both trees
			void swap(red_black_tree &other)
			{
				ft::swap(m_Root, other.m_Root);
				ft::swap(m_End, other.m_End);
				ft::swap(m_Size, other.m_Size);
			}

			// void deleteTreeNode(node_ptr v)
			// {
			// 	deleteNode(v);
			// }

		// explicit vector ( const allocator_type& alloc = allocator_type() )
		// 		:	m_Allocate(alloc), m_Data(NULL), m_Size(0), m_Capacity(0) {	}
			// constructor
			// initialize root
			// red_black_tree()
			// 	: m_Allocate(), m_Root(NULL), m_End(NULL), m_Size(0) {}
			
			red_black_tree( const allocator_type& alloc = allocator_type(),
							const key_compare& comp = key_compare() )
				:	m_Allocate(alloc), m_Compare (comp), m_Root(NULL), m_End(NULL), m_Size(0) 
			{ 
				m_End = m_Allocate.allocate(1);
				m_Root = m_End;
			}

			~red_black_tree()	
			{	
				clear();
				m_Allocate.deallocate(m_End, 1);
			}

			node_ptr getRoot() { return m_Root; }

			// searches for given value
			// if found returns the node (used for delete)
			// else returns the last node while traversing (used in insert)
	/*comp*/node_ptr search(value_type val) {
				node_ptr temp = m_Root;
				while (temp != NULL)
				{
					if (m_Compare(m_GetKey(val), m_GetKey(temp->val)))
					// if (n < temp->val)
					{
						if (temp->left == NULL)
							break;
						else
							temp = temp->left;
					}
					else if (m_Compare(m_GetKey(temp->val), m_GetKey(val)))
					// else if ((n > temp->val))
					{
						if (temp->right == NULL)
							break;
						else
							temp = temp->right;
					}
					else
						return temp;
				}

				return temp;
			}

			node_ptr find (value_type val){
				node_ptr temp = m_Root;
				while (temp != NULL)
				{
					if (m_Compare(m_GetKey(val), m_GetKey(temp->val)))
					// if (n < temp->val)
					{
						if (temp->left == NULL)
							break;
						else
							temp = temp->left;
					}
					else if (m_Compare(m_GetKey(temp->val), m_GetKey(val)))
					// else if ((n > temp->val))
					{
						if (temp->right == NULL)
							break;
						else
							temp = temp->right;
					}
					else
						return temp;
				}
				return NULL;
			}

			// inserts the given value to tree
	/*comp*/void insert(value_type val) {
				if (m_Root == m_End)
				{
					// when root is null
					// simply insert value at root
					m_Root = m_Allocate.allocate(1);
					m_Allocate.construct(m_Root, node_type(val));
					m_Root->color = BLACK;
					m_Root->next = m_End;
					m_End->prev = m_Root;
				}
				else
				{
					node_ptr temp = search(val);
					e_compare compare;

					if (m_Compare(m_GetKey(val), m_GetKey(temp->val)))
						compare = SMALL;
					else if (m_Compare(m_GetKey(temp->val), m_GetKey(val)))
						compare = BIG;
					else // return if value already exists
						return;

					node_ptr newNode = m_Allocate.allocate(1);
					m_Allocate.construct(newNode, node_type(val));

					// if value is not found, search returns the node
					// where the value is to be inserted

					// connect new node to correct node
					newNode->parent = temp;

					// if (val < temp->val)
					if (compare == SMALL)
					{
						temp->left = newNode;
						if (temp->prev != NULL)
						{
							temp->prev->next = newNode;
							newNode->prev = temp->prev;
						}
						temp->prev = newNode;
						newNode->next = temp;
					}
					else if (compare == BIG)
					{
						temp->right = newNode;
						if (temp->next != NULL)
						{
							temp->next->prev = newNode;
							newNode->next = temp->next;
						}
						temp->next = newNode;
						newNode->prev = temp;
					}

					// fix red red violaton if exists
					fixRedRed(newNode);
					if (newNode == maximum())
					{
						newNode->next = m_End;
						m_End->prev = newNode;
					}
				}
				m_Size++;
			}
			
			bool empty() const { return (m_Size == 0); }
			// bool empty() const { (m_Root == NULL); }

			size_type size() const { return m_Size; }

			size_type max_size() const { return m_Allocate.max_size(); }

			// utility function that deletes the node with given value
			void deleteByVal(value_type val) {
				if (empty())
					return;

				node_ptr node = find(val);

				if (node == NULL)
				{
					// std::cout << "No node found to delete with value:" << val << std::endl;
					return;
				}
				if (size()!=1 && node == maximum())
				{ 
					m_End->prev = node->prev;
					node->prev->next = m_End;
				}
				deleteNode(node);
			}

			node_ptr minimum() const
			{
				if ( m_Root == m_End )
					return m_End;
				node_ptr	node = m_Root;
				// std::cout << "HEY :" << node  << std::endl;
				// std::cout << "HEY :" << m_End  << std::endl;
				while (node->left != NULL)
					node = node->left;
				return (node);
			}

			node_ptr maximum() const
			{
				node_ptr	node = m_Root;
				while (node->right != NULL)
					node = node->right;
				return (node);
			}

			key_compare key_comp() const { return m_Compare; }

			// prints inorder of the tree
			void printInOrder() {
				std::cout << "Inorder: " << std::endl;
				if (m_Root == NULL)
					std::cout << "Tree is empty" << std::endl;
				else
					inorder(m_Root);
				std::cout << std::endl;
			}

			// prints inorder of the tree
			void printInOrderDesc() {
				std::cout << "InorderDesc: " << std::endl;
				if (m_Root == NULL)
					std::cout << "Tree is empty" << std::endl;
				else
					inorderdesc(m_Root);
				std::cout << std::endl;
			}

			// prints inorder of the tree using next
			void printInNext() {
				node_ptr temp = m_Root;
				std::cout << "InorderNext: " << std::endl;
				if (m_Root == NULL)
					std::cout << "Tree is empty" << std::endl;
				else
				{
					while (temp->prev != NULL)
						temp = temp->prev;
					while (temp->next != m_End)
					{
						std::cout << m_GetKey(temp->val) << " ";
						temp = temp->next;
					}
					std::cout << m_GetKey(temp->val) << " ";
				}
				std::cout << std::endl;
			}

			// prints inorder desc of the tree using prev
			void printInNextDesc() {
				node_ptr temp = m_End->prev;
				std::cout << "InorderNextDesc: " << std::endl;
				if (m_Root == NULL)
					std::cout << "Tree is empty" << std::endl;
				else
				{
					while (temp->prev != NULL)
					{
						std::cout << temp->val << " ";
						temp = temp->prev;
					}
					std::cout << temp->val << " ";
				}
				std::cout << std::endl;
			}

			// prints level order of the tree
			void printLevelOrder() {
				const int rootLevel = 0;
				std::cout << "Level order: " << std::endl;
				if (m_Root == NULL)
					std::cout << "Tree is empty" << std::endl;
				else
					levelOrder(m_Root, rootLevel);
				std::cout << std::endl;
			}

			iterator begin()	{	return iterator(minimum());	}
			const_iterator begin() const	{	return const_iterator(minimum());	}

			iterator end()	{	return iterator(m_End);	}
			const_iterator end() const	{	return iterator(m_End);		}
			// iterator begin()	{	return iterator(m_End, minimum());	}
			// const_iterator begin() const	{	return const_iterator(m_End, minimum());	}

			// iterator end()	{	return iterator(m_End, m_End);	}
			// const_iterator end() const	{	return iterator(m_End, m_End);		}

			reverse_iterator rbegin()	{	return reverse_iterator(end());	}
			const_reverse_iterator rbegin() const	{	return const_reverse_iterator(end());	}

			reverse_iterator rend()	{	return reverse_iterator(begin());	}
			const_reverse_iterator rend() const	{	return const_reverse_iterator(begin());	}

			iterator lower_bound (const key_type& k)
			{
				node_ptr temp = minimum();

				while (m_Compare(m_GetKey(temp->val), k) && temp != m_End)
					temp = temp->next;
				return iterator(temp);
			}
			const_iterator lower_bound (const key_type& k) const
			{
				node_ptr temp = minimum();

				while (m_Compare(m_GetKey(temp->val), k) && temp != m_End)
					temp = temp->next;
				return const_iterator(temp);
			}

			iterator upper_bound (const key_type& k)
			{
				node_ptr temp = maximum();
				if (m_Compare(m_GetKey(temp->val), k))
					return iterator(m_End);
					
				node_ptr const min  = minimum();
				while (m_Compare(k ,m_GetKey(temp->val)) && temp != min)
					temp = temp->prev;
				if ( 
					(	temp == min && !m_Compare(k, m_GetKey(temp->val)) 	)
					|| (	temp != min && !m_Compare(m_GetKey(temp->val), k)	)	
				)
					return iterator(temp->next);
				return iterator(temp);
			}
			const_iterator upper_bound (const key_type& k) const
			{
				node_ptr temp = maximum();
				if (m_Compare(m_GetKey(temp->val), k))
					return const_iterator(m_End);
					
				node_ptr const min  = minimum();
				while (m_Compare(k ,m_GetKey(temp->val)) && temp != min)
					temp = temp->prev;
				if ( 
					(	temp == min && !m_Compare(k, m_GetKey(temp->val)) 	)
					|| (	temp != min && !m_Compare(m_GetKey(temp->val), k)	)	
				)
					return const_iterator(temp->next);
				return const_iterator(temp);
			}
	};

}//namespace ft
