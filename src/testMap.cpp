/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testMap.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:49:56 by emadriga          #+#    #+#             */
/*   Updated: 2022/12/20 20:58:46 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testMap.hpp"

//	public
	void testMapIntInsertDelete()
	{
		NS::red_black_tree<int> tree;

		tree.insert(7);
		tree.insert(3);
		tree.insert(18);
		tree.insert(10);
		tree.insert(22);
		tree.insert(8);
		tree.insert(11);
		tree.insert(26);
		tree.insert(2);
		tree.insert(6);
		tree.insert(13);

		tree.printInOrder();
		tree.printInOrderDesc();
		tree.printLevelOrder();
		tree.printInNext();
		tree.printInNextDesc();

		std::cout << std::endl << "Deleting 18, 11, 3, 10, 22" << std::endl;

		tree.deleteByVal(18);
		tree.deleteByVal(11);
		tree.deleteByVal(3);
		tree.deleteByVal(10);
		tree.deleteByVal(22);

		tree.printInOrder();
		tree.printInOrderDesc();
		tree.printLevelOrder();
		tree.printInNext();
		tree.printInNextDesc();
	}

	void testMapStringInsertDelete()
	{
		NS::red_black_tree<std::string> tree;

		tree.insert("d");
		tree.insert("b");
		tree.insert("i");
		tree.insert("f");
		tree.insert("j");
		tree.insert("e");
		tree.insert("g");
		tree.insert("k");
		tree.insert("a");
		tree.insert("c");
		tree.insert("h");

		tree.printInOrder();
		tree.printInOrderDesc();
		tree.printLevelOrder();
		tree.printInNext();
		tree.printInNextDesc();

		std::cout << std::endl << "Deleting i, g, b, f, j" << std::endl;

		tree.deleteByVal("i");
		tree.deleteByVal("g");
		tree.deleteByVal("b");
		tree.deleteByVal("f");
		tree.deleteByVal("j");

		tree.printInOrder();
		tree.printInOrderDesc();
		tree.printLevelOrder();
		tree.printInNext();
		tree.printInNextDesc();
	}

	void testMapStringInsertDelete2()
	{
		NS::red_black_tree<std::string> tree;

		tree.insert("7");
		tree.insert("3");
		tree.insert("18");
		tree.insert("10");
		tree.insert("22");
		tree.insert("8");
		tree.insert("11");
		tree.insert("26");
		tree.insert("2");
		tree.insert("6");
		tree.insert("13");

		tree.printInOrder();
		tree.printInOrderDesc();
		tree.printLevelOrder();
		tree.printInNext();
		tree.printInNextDesc();

		std::cout << std::endl << "Deleting 18, 11, 3, 10, 22" << std::endl;

		tree.deleteByVal("18");
		tree.deleteByVal("11");
		tree.deleteByVal("3");
		tree.deleteByVal("10");
		tree.deleteByVal("22");

		tree.printInOrder();
		tree.printInOrderDesc();
		tree.printLevelOrder();
		tree.printInNext();
		tree.printInNextDesc();
	}
