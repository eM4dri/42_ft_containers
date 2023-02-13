/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:26:19 by emadriga          #+#    #+#             */
/*   Updated: 2023/02/13 14:08:01 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <memory>
#include "node.hpp"
#include "tree_iterator.hpp"
#define RESET_COLOR   "\033[0m"
// #define BLACK   "\033[30m"      /* Black */
#define RED_COLOR     "\033[31m"      /* Red */

namespace ft
{
	// template< typename T, class Alloc = std::allocator<T> >
	template <	typename T, 
				typename Compare = std::less<T>, 
				typename Alloc = std::allocator<T> >
	class red_black_tree
	{
		public:
			typedef Compare										value_compare;
			typedef Alloc										allocator_type;
			// typedef typename allocator_type::size_type			size_type;
			typedef node<T>										node_type;
			// get another allocator.
			typedef typename Alloc::
					template rebind<node_type>::other			node_allocator;
			typedef typename node_allocator::pointer			node_ptr;
  			typedef typename node_allocator::const_pointer		const_node_ptr;
		private:
			node_allocator 		m_Allocate;
			value_compare		m_Compare;
			node_ptr			m_Root;
			node_ptr			m_End;
			// size_type			m_Size;
			

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

			void swapColors(node_ptr x1, node_ptr x2)
			{
				e_color temp;
				temp = x1->color;
				x1->color = x2->color;
				x2->color = temp;
			}

			void swapValues(node_ptr u, node_ptr v)
			{
				T temp;
				temp = u->val;
				u->val = v->val;
				v->val = temp;
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
								swapColors(parent, grandparent);
							}
							else
							{
								leftRotate(parent);
								swapColors(x, grandparent);
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
								swapColors(x, grandparent);
							}
							else
							{
								swapColors(parent, grandparent);
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
					temp = temp->left;

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
						// v is root, assign the value of u to v, and delete u
						v->val = u->val;
						v->left = v->right = NULL;
						deleteThisNode(u);
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
				swapValues(u, v);
				deleteNode(u);
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
				std::cout << x->val << " ";
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
			}

			void destroyAllNodes(node_ptr x)
			{
				if (x == NULL)
					return;
				destroyAllNodes(x->left);
				destroyAllNodes(x->right);
				destroyNode(x);
				x = NULL;
			}

			void clear()
			{
				if (m_Root != NULL)
				{
					destroyAllNodes(m_Root);
					m_Allocate.deallocate(m_End, 1);
				}
			}

		public:
		// explicit vector ( const allocator_type& alloc = allocator_type() )
		// 		:	m_Allocate(alloc), m_Data(NULL), m_Size(0), m_Capacity(0) {	}
			// constructor
			// initialize root
			red_black_tree( const allocator_type& alloc = allocator_type(),
							const value_compare& comp = value_compare() )
				:	m_Allocate(alloc), m_Compare (comp), m_Root(NULL), m_End(NULL) { }

			~red_black_tree()	{	clear();	}

			node_ptr getRoot() { return m_Root; }

			// searches for given value
			// if found returns the node (used for delete)
			// else returns the last node while traversing (used in insert)
	/*comp*/node_ptr search(T n) {
				node_ptr temp = m_Root;
				while (temp != NULL)
				{
					if (n < temp->val)
					{
						if (temp->left == NULL)
							break;
						else
							temp = temp->left;
					}
					else if (n == temp->val)
						return temp;
					else
					{
						if (temp->right == NULL)
							break;
						else
							temp = temp->right;
					}
				}

				return temp;
			}

			node_ptr find (T n){
				node_ptr temp = m_Root;
				while (temp != NULL)
				{
					if (n < temp->val)
					{
						if (temp->left == NULL)
							break;
						else
							temp = temp->left;
					}
					else if (n == temp->val)
						return temp;
					else
					{
						if (temp->right == NULL)
							break;
						else
							temp = temp->right;
					}
				}
				return NULL;
			}

			// inserts the given value to tree
	/*comp*/void insert(T n) {
				if (m_Root == NULL)
				{
					// when root is null
					// simply insert value at root
					m_Root = m_Allocate.allocate(1);
					m_Allocate.construct(m_Root, n);
					m_End = m_Allocate.allocate(1);
					m_Root->color = BLACK;
					m_Root->next = m_End;
					m_End->prev = m_Root;
				}
				else
				{
					node_ptr temp = search(n);

					if (temp->val == n)
					{
						// return if value already exists
						return;
					}
					node_ptr newNode = m_Allocate.allocate(1);
					m_Allocate.construct(newNode, n);

					// if value is not found, search returns the node
					// where the value is to be inserted

					// connect new node to correct node
					newNode->parent = temp;

					if (n < temp->val)
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
					else
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
			}

			bool empty() const{
				return (m_Root == NULL);
			}

			// utility function that deletes the node with given value
			void deleteByVal(T val) {
				if (empty())
					return;

				node_ptr node = find(val);

				if (node == NULL)
				{
					std::cout << "No node found to delete with value:" << val << std::endl;
					return;
				}
				if (node == maximum())
				{
					m_End->prev = node->prev;
					node->prev->next = m_End;
				}
				deleteNode(node);
			}

			node_ptr minimum() const
			{
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
						std::cout << temp->val << " ";
						temp = temp->next;
					}
					std::cout << temp->val << " ";
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
	};

}//namespace ft
