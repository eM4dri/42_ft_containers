/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:26:19 by emadriga          #+#    #+#             */
/*   Updated: 2022/07/17 12:28:31 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "node.hpp"
#include "vector.hpp"
#define RESET_COLOR   "\033[0m"
// #define BLACK   "\033[30m"      /* Black */
#define RED_COLOR     "\033[31m"      /* Red */

namespace ft
{
	template <class T>
	class red_black_tree
	{
		private:
			node<T> *root;

			// left rotates the given node
			void leftRotate(node<T> *x)
			{
				// new parent will be node's right child
				node<T> *nParent = x->right;

				// update root if current node is root
				if (x == root)
					root = nParent;

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

			void rightRotate(node<T> *x)
			{
				// new parent will be node's left child
				node<T> *nParent = x->left;

				// update root if current node is root
				if (x == root)
					root = nParent;

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

			void swapColors(node<T> *x1, node<T> *x2)
			{
				COLOR temp;
				temp = x1->color;
				x1->color = x2->color;
				x2->color = temp;
			}

			void swapValues(node<T> *u, node<T> *v)
			{
				T temp;
				temp = u->val;
				u->val = v->val;
				v->val = temp;
			}

			// fix red red at given node
			void fixRedRed(node<T> *x)
			{
				// if x is root color it black and return
				if (x == root)
				{
					x->color = BLACK;
					return;
				}

				// initialize parent, grandparent, uncle
				node<T> *parent = x->parent;
				node<T> *uncle = x->uncle();
				node<T> *grandparent = parent->parent;

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
			node<T> *successor(node<T> *x)
			{
				node<T> *temp = x;

				while (temp->left != NULL)
					temp = temp->left;

				return temp;
			}

			// find node that replaces a deleted node in BST
			node<T> *BSTreplace(node<T> *x)
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

			// deletes the given node
			void deleteNode(node<T> *v)
			{
				node<T> *u = BSTreplace(v);

				// True when u and v are both black
				bool uvBlack = ((u == NULL || u->color == BLACK) && (v->color == BLACK));
				node<T> *parent = v->parent;

				if (u == NULL)
				{
					// u is NULL therefore v is leaf
					if (v == root)
					{
						// v is root, making root null
						root = NULL;
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
					delete v;
					return;
				}

				if (v->left == NULL || v->right == NULL)
				{
					// v has 1 child
					if (v == root)
					{
						// v is root, assign the value of u to v, and delete u
						v->val = u->val;
						v->left = v->right = NULL;
						delete u;
					}
					else
					{
						// Detach v from tree and move u up
						if (v->isOnLeft())
							parent->left = u;
						else
							parent->right = u;
						delete v;
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

			void fixDoubleBlack(node<T> *x)
			{
				if (x == root)
					// Reached root
					return;
				node<T> *sibling = x->sibling(), *parent = x->parent;
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
			void levelOrder(node<T> *x)
			{
				if (x == NULL)
				// return if node is null
				return;

				// queue for level order
				ft::vector<node<T> *> q;
				// queue<node *> q;
				node<T> *curr;

				// push x
				q.push_back(x);

				while (!q.empty())
				{
					// while q is not empty
					// dequeue
					curr = q.front();
					//q.pop();
					q.erase(q.begin());

					// push children to queue
					if (curr->left != NULL)
						q.push_back(curr->left);
					if (curr->right != NULL)
						q.push_back(curr->right);
						
					// print node value
					if (!curr->color)
						std::cout << RED_COLOR;
					// system(curr->color ? "Color B5": "Color DE");
					std::cout << curr->val << "|";
					std::cout << (!curr->color ? 'R' : 'B');
					if (!q.empty() && curr->val > q.front()->val )
						std::cout << std::endl;
					else
						std::cout << "\t";
					std::cout << RESET_COLOR;
				}
			}

			// prints inorder recursively
			void inorder(node<T> *x)
			{
				if (x == NULL)
					return;
				inorder(x->left);
				std::cout << x->val << " ";
				inorder(x->right);
			}

		public:
			// constructor
			// initialize root
			red_black_tree() { root = NULL; }

			node<T> *getRoot() { return root; }

			// searches for given value
			// if found returns the node (used for delete)
			// else returns the last node while traversing (used in insert)
			node<T> *search(T n) {
				node<T> *temp = root;
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
						break;
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

			// inserts the given value to tree
			void insert(T n) {
				node<T> *newNode = new node<T>(n);
				if (root == NULL)
				{
					// when root is null
					// simply insert value at root
					newNode->color = BLACK;
					root = newNode;
				}
				else
				{
					node<T> *temp = search(n);

					if (temp->val == n)
					{
						// return if value already exists
						return;
					}

					// if value is not found, search returns the node
					// where the value is to be inserted

					// connect new node to correct node
					newNode->parent = temp;

					if (n < temp->val)
						temp->left = newNode;
					else
						temp->right = newNode;

					// fix red red voilaton if exists
					fixRedRed(newNode);
				}
			}

			// utility function that deletes the node with given value
			void deleteByVal(T n) {
				if (root == NULL)
				// Tree is empty
					return;

				node<T> *v = search(n);
				// node *v = search(n), *u;

				if (v->val != n)
				{
					std::cout << "No node found to delete with value:" << n << std::endl;
					return;
				}

				deleteNode(v);
			}

			// prints inorder of the tree
			void printInOrder() {
				std::cout << "Inorder: " << std::endl;
				if (root == NULL)
					std::cout << "Tree is empty" << std::endl;
				else
					inorder(root);
				std::cout << std::endl;
			}

			// prints level order of the tree
			void printLevelOrder() {
				std::cout << "Level order: " << std::endl;
				if (root == NULL)
					std::cout << "Tree is empty" << std::endl;
				else
					levelOrder(root);
				std::cout << std::endl;
			}
	};

}//namespace ft
