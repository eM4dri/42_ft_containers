/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testTree.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:49:56 by emadriga          #+#    #+#             */
/*   Updated: 2023/03/06 12:53:28 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "test/testTree.hpp"

//	private
static void testInitial()
{
	NS::set<int, int> mySet;

	tree.insert(15);
	tree.insert(16);
	tree.insert(17);
	tree.insert(14);
	tree.insert(13);
	tree.insert(18);
	tree.insert(19);
	tree.insert(12);
	tree.insert(11);
	tree.insert(20);
	tree.insert(21);
	tree.insert(10);
	tree.insert(9);
	tree.insert(22);
	tree.insert(23);
	tree.insert(8);
	tree.insert(7);
	tree.insert(24);
	tree.insert(25);

	tree.printLevelOrder();
	// tree.printInOrder();
	// tree.printInOrder();
	// tree.printInOrderDesc();
	// tree.printInOrderDesc();
	// tree.printLevelOrder();
	// tree.printInNext();
	// tree.printInNext();
	// tree.printInNextDesc();
	// tree.printInNextDesc();
	// std::cout << std::endl << "Deleting 18, 11, 3, 10, 22" << std::endl;
	// std::cout << std::endl << "Deleting 18, 11, 3, 10, 22" << std::endl;
	// tree.deleteByVal(18);
	// tree.deleteByVal(18);
	// tree.deleteByVal(11);
	// tree.deleteByVal(11);
	// tree.deleteByVal(3);
	// tree.deleteByVal(3);
	// tree.deleteByVal(10);
	// tree.deleteByVal(10);
	// tree.deleteByVal(22);
	// tree.deleteByVal(22);
	// tree.deleteByVal(2);
	// tree.deleteByVal(2);
	// tree.printInOrder();
	// tree.printInOrder();
	// tree.printInOrderDesc();
	// tree.printInOrderDesc();
	// tree.printLevelOrder();
	// tree.printLevelOrder();
	// tree.printInNext();
	// tree.printInNext();
	// tree.printInNextDesc();
	// tree.printInNextDesc();
}


//	public

#ifdef LOGTREE	// log red_black_tree
		void testTree()
		{
			performTest("Tree's initial", &testInitial);
		}
#else
		void testTree()
		{	};
#endif	