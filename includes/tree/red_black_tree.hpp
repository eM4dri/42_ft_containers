/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:26:19 by emadriga          #+#    #+#             */
/*   Updated: 2023/03/03 20:43:44 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
// #include <memory>									//	std::allocator
#include <functional>									//	std::less
#include "node.hpp"
#include "../utility/pair.hpp"
#include "../iterators/tree_iterator.hpp"
#include "../vector.hpp"
#define RESET_COLOR   "\033[0m"		/* Black */
#define RED_COLOR     "\033[31m"	/* Red */

namespace ft
{
	enum e_compare { BIG, SMALL  };

	// KeyOfVal functor for map
	template <	typename Key,
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
			typedef node<Val>											node_type;
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

		public:
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

			void clear()
			{
				if ( m_Root != m_End )
				{
					destroyAllNodes(m_Root);
					m_Root = m_End;
				}
			}

			key_compare key_comp() const { return m_Compare; }

			bool empty() const { return (m_Size == 0); }

			size_type size() const { return m_Size; }

			size_type max_size() const { return m_Allocate.max_size(); }

			iterator begin()	{	return iterator(minimum());	}
			const_iterator begin() const	{	return const_iterator(minimum());	}

			iterator end()	{	return iterator(m_End);	}
			const_iterator end() const	{	return iterator(m_End);		}

			reverse_iterator rbegin()	{	return reverse_iterator(end());	}
			const_reverse_iterator rbegin() const	{	return const_reverse_iterator(end());	}

			reverse_iterator rend()	{	return reverse_iterator(begin());	}
			const_reverse_iterator rend() const	{	return const_reverse_iterator(begin());	}

			iterator lower_bound (const key_type& k)
			{
				node_ptr temp = minimum();
				while (	temp != m_End &&	\
						m_Compare(m_GetKey(temp->val), k) )	//	while k is bigger
					temp = temp->next;
				return iterator(temp);
			}
			const_iterator lower_bound (const key_type& k) const
			{
				node_ptr temp = minimum();
				while (	temp != m_End &&	\
						m_Compare(m_GetKey(temp->val), k) )	//	while k is bigger
					temp = temp->next;
				return const_iterator(temp);
			}

			iterator upper_bound (const key_type& k)
			{
				node_ptr temp = minimum();
				while (	temp != m_End &&	\
						!m_Compare(k, m_GetKey(temp->val)) )	//	while k is bigger or equal
					temp = temp->next;
				return iterator(temp);
			}
			const_iterator upper_bound (const key_type& k) const
			{
				node_ptr temp = minimum();
				while (	temp != m_End &&	\
						!m_Compare(k, m_GetKey(temp->val)) )	//	while k is bigger or equal
					temp = temp->next;
				return const_iterator(temp);
			}

			// no need to swap m_Allocate & m_Compare shared types from both trees
			void swap(red_black_tree &other)
			{
				ft::swap(m_Root, other.m_Root);
				ft::swap(m_End, other.m_End);
				ft::swap(m_Size, other.m_Size);
			}

			// searches for given value
			// if found returns the node
			// else returns NULL
			node_ptr find (value_type val) const
			{
				if (m_Root == m_End)
					return NULL;
				node_ptr temp = m_Root;
				while (temp != m_End)
				{
					if (m_Compare(m_GetKey(val), m_GetKey(temp->val)))	//	val < temp->val
					{
						if (temp->left == NULL)
							break;
						else
							temp = temp->left;
					}
					else if (m_Compare(m_GetKey(temp->val), m_GetKey(val)))	//	val > temp->val
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
			void insert(value_type val)
			{
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
				}
				m_Size++;
			}

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

			void eraseMapRange (iterator first, iterator last)
			{
				ft::vector<value_type> keys;
				typename ft::vector<value_type>::iterator it;

				while (first != last)
					keys.push_back( *first++ );

				for (it = keys.begin(); it != keys.end(); it++)
					deleteByVal(*it);
			}

			void eraseSetRange (const_iterator first, const_iterator last)
			{
				ft::vector<key_type> keys;
				typename ft::vector<key_type>::iterator it;

				while (first != last)
				{
					keys.push_back( m_GetKey(*first) );
					first++;
				}

				for (it = keys.begin(); it != keys.end(); it++)
					deleteByVal(*it);
			}

		private:
			// searches for given value
			// if found returns the node
			// else returns the last node while traversing (used in insert)
			node_ptr search(value_type val)
			{
				node_ptr temp = m_Root;
				while (temp != m_End)
				{
					if (m_Compare(m_GetKey(val), m_GetKey(temp->val)))	//	val < temp->val
					{
						if (temp->left == NULL)
							break;
						else
							temp = temp->left;
					}
					else if (m_Compare(m_GetKey(temp->val), m_GetKey(val)))	//	val > temp->val
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
				m_Root->parent = NULL;
				m_Root->color = BLACK;
				destroyNode(node);
			}

			// deletes the given node
			void deleteNode(node_ptr v)
			{
				if (size() == 1)
				{
					destroyNode(m_Root);
					m_Root = m_End;
					return;
				}

				node_ptr u = BSTreplace(v);

				// True when u and v are both black
				bool uvBlack = ((u == NULL || u->color == BLACK) && (v->color == BLACK));
				node_ptr parent = v->parent;

				if (u == NULL)
				{
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
					// v has 1 child
					if (v == m_Root)
					{
						// v is root, assign the value of u to v, and delete u (move links & delete v)
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
				swapEverithingButValues(u , v);
				deleteNode(v);
			}

			void printfThisNode(node_ptr node)
			{
				if (node == NULL)
					return;
				if (!node->color)
					std::cout << RED_COLOR;
				std::cout << "\tfirst: " << node->val.first;
				std::cout << "\tsecond: " << node->val.second;
				std::cout << "\tparent: " << node->parent;
				std::cout << "\tleft: " << node->left;
				std::cout << "\n\tprev: " << node->prev;
				std::cout << "\tnext: " << node->next;
				std::cout << "\tright: " << node->right;
				if (node->parent != NULL)
				std::cout << "\n\tparent's sons " << node->parent->left << " & " << node->parent->right;
				if (node->prev != NULL)
					std::cout << "\n\tprev->next: " << node->prev->next;
				if (node->next != NULL)
					std::cout << "\n\tnext->prev: " << node->next->prev;

				if (node->left != NULL)
					std::cout << "\n\tleft son's father: " << node->left->parent;
				if (node->right != NULL)
					std::cout << "\n\tright son's father: " << node->right->parent;
				std::cout << RESET_COLOR;
				std::cout << std::endl;
			}

			void swapEverithingButValues(node_ptr u, node_ptr v)
			{
				ft::swap(u->color, v->color);

				ft::swap(u->parent, v->parent);
				if (u->parent == u)
					u->parent = v;
				else if (v->parent == v)
					v->parent = u;
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

				ft::swap(u->left, v->left);
				if (u->left == u)
					u->left = v;
				else if (v->left == v)
					v->left = u;

				ft::swap(u->right, v->right);
				if (u->right == u)
					u->right = v;
				else if (v->right == v)
					v->right = u;

				ft::swap(u->next, v->next);
				if (u->next == u)
					u->next = v;
				else if (v->next == v)
					v->next = u;

				ft::swap(u->prev, v->prev);
				if (u->prev == u)
					u->prev = v;
				else if (v->prev == v)
					v->prev = u;

				if (u->next != NULL && u->next->prev == v)
					u->next->prev = u;
				if (v->next != NULL && v->next->prev == u)
					v->next->prev = v;
				if (u->prev != NULL && u->prev->next == v)
					u->prev->next = u;
				if (v->prev != NULL && v->prev->next == u)
					v->prev->next = v;

				if (u->left != NULL)
					u->left->parent = u;
				if (u->right != NULL)
					u->right->parent = u;
				if (v->left != NULL)
					v->left->parent = v;
				if (v->right != NULL)
					v->right->parent = v;

				if (m_Root == u)
					m_Root = v;
				else if (m_Root == v)
					m_Root = u;
			}

			void fixDoubleBlack(node_ptr x)
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
			void levelOrder(node_ptr x, const int nodeLevel, const int nullVisible)
			{
				const int sonLevel = nodeLevel + 1;
				for (int i = 0; i < nodeLevel; i++)
					std::cout << "\t";
				if (nullVisible && x == NULL)
					std::cout << "(NULL)"<< std::endl;
				if (nullVisible && x == m_End)
					std::cout << "(m_End)"<< std::endl;
				if (x == NULL || x == m_End)
					return;
				if (!x->color)
					std::cout << RED_COLOR;
				std::cout << m_GetKey(x->val) << "|";
				std::cout << (!x->color ? 'R' : 'B') << std::endl;
				std::cout << RESET_COLOR;
				levelOrder(x->left, sonLevel, nullVisible);
				levelOrder(x->right, sonLevel, nullVisible);
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
				std::cout << m_GetKey(x->val) << " ";
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
				destroyAllNodes(x->left);
				destroyAllNodes(x->right);
				destroyNode(x);
			}

			node_ptr minimum() const
			{
				if ( m_Root == m_End )
					return m_End;
				node_ptr	node = m_Root;
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

		public: // log red_black_tree

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
						std::cout << m_GetKey(temp->val) << " ";
						temp = temp->prev;
					}
					std::cout << m_GetKey(temp->val) << " ";
				}
				std::cout << std::endl;
			}

			// prints level order of the tree
			void printLevelOrder() {
				const int rootLevel = 0;
				const int nullVisible = 1;
				std::cout << "Level order: " << std::endl;
				if (m_Root == NULL)
					std::cout << "Tree is empty" << std::endl;
				else
					levelOrder(m_Root, rootLevel, nullVisible);
				std::cout << std::endl;
			}


	};

}//namespace ft
