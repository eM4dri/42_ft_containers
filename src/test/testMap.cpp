/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testMap.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:49:56 by emadriga          #+#    #+#             */
/*   Updated: 2023/02/28 17:08:42 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test/testMap.hpp"

	void testMapIntInsertDelete()
	{
		NS::map<char,int> mymap;

		// first insert function version (single parameter):
		mymap.insert ( NS::pair<char,int>('a',100) );
		mymap.insert ( NS::pair<char,int>('z',200) );

		NS::pair<NS::map<char,int>::iterator,bool> ret;
		ret = mymap.insert ( NS::pair<char,int>('z',500) );
		if (ret.second==false) {
			std::cout << "element 'z' already existed";
			std::cout << " with a value of " << ret.first->second << '\n';
		}

		//second insert function version (with hint position):
		NS::map<char,int>::iterator it = mymap.begin();
		mymap.insert (it, NS::pair<char,int>('b',300));  // max efficiency inserting
		mymap.insert (it, NS::pair<char,int>('c',400));  // no max efficiency inserting

		// third insert function version (range insertion):
		NS::map<char,int> anothermap;
		anothermap.insert(mymap.begin(), mymap.find('c'));

		// showing contents:
		std::cout << "mymap contains:\n";
		for (NS::map<char,int>::iterator it2 =mymap.begin(); it2!=mymap.end(); ++it2)
			std::cout << it2->first << " => " << it2->second << '\n';

		std::cout << "anothermap contains:\n";
		for (NS::map<char,int>::iterator it3 =anothermap.begin(); it3!=anothermap.end(); ++it3)
			std::cout << it3->first << " => " << it3->second << '\n';
	}

	// void testRBTIntInsertDelete()
	// {
	// 	NS::red_black_tree<int, int> tree;

	// 	tree.insert(7);
	// 	tree.insert(3);
	// 	tree.insert(18);
	// 	tree.insert(10);
	// 	tree.insert(22);
	// 	tree.insert(8);
	// 	tree.insert(11);
	// 	tree.insert(26);
	// 	tree.insert(2);
	// 	tree.insert(6);
	// 	tree.insert(13);
	// 	tree.insert(23);
	// 	tree.insert(15);
	// 	tree.insert(5);
	// 	tree.insert(2);
	// 	tree.insert(42);
	// 	tree.insert(100);
	// 	tree.insert(99);
	// 	tree.insert(98);
	// 	tree.insert(58);

	// 	tree.printInOrder();
	// 	tree.printInOrderDesc();
	// 	tree.printLevelOrder();
	// 	tree.printInNext();
	// 	tree.printInNextDesc();

	// 	std::cout << std::endl << "Deleting 18, 11, 3, 10, 22" << std::endl;

	// 	tree.deleteByVal(18);
	// 	tree.deleteByVal(11);
	// 	tree.deleteByVal(3);
	// 	tree.deleteByVal(10);
	// 	tree.deleteByVal(22);
	// 	tree.deleteByVal(2);

	// 	tree.printInOrder();
	// 	tree.printInOrderDesc();
	// 	tree.printLevelOrder();
	// 	tree.printInNext();
	// 	tree.printInNextDesc();
	// }

	// void testRBTStringInsertDelete()
	// {
	// 	NS::red_black_tree<std::string, std::string> tree;

	// 	tree.insert("d");
	// 	tree.insert("b");
	// 	tree.insert("i");
	// 	tree.insert("f");
	// 	tree.insert("j");
	// 	tree.insert("e");
	// 	tree.insert("g");
	// 	tree.insert("k");
	// 	tree.insert("a");
	// 	tree.insert("c");
	// 	tree.insert("h");

	// 	tree.printInOrder();
	// 	tree.printInOrderDesc();
	// 	tree.printLevelOrder();
	// 	tree.printInNext();
	// 	tree.printInNextDesc();

	// 	std::cout << std::endl << "Deleting i, g, b, f, j" << std::endl;

	// 	tree.deleteByVal("i");
	// 	tree.deleteByVal("g");
	// 	tree.deleteByVal("b");
	// 	tree.deleteByVal("f");
	// 	tree.deleteByVal("j");

	// 	tree.printInOrder();
	// 	tree.printInOrderDesc();
	// 	tree.printLevelOrder();
	// 	tree.printInNext();
	// 	tree.printInNextDesc();
	// }

	// void testRBTStringInsertDelete2()
	// {
	// 	NS::red_black_tree<std::string, std::string> tree;

	// 	tree.insert("7");
	// 	tree.insert("3");
	// 	tree.insert("18");
	// 	tree.insert("10");
	// 	tree.insert("22");
	// 	tree.insert("8");
	// 	tree.insert("11");
	// 	tree.insert("26");
	// 	tree.insert("2");
	// 	tree.insert("6");
	// 	tree.insert("13");

	// 	tree.printInOrder();
	// 	tree.printInOrderDesc();
	// 	tree.printLevelOrder();
	// 	tree.printInNext();
	// 	tree.printInNextDesc();

	// 	std::cout << std::endl << "Deleting 18, 11, 3, 10, 22" << std::endl;

	// 	tree.deleteByVal("18");
	// 	tree.deleteByVal("11");
	// 	tree.deleteByVal("3");
	// 	tree.deleteByVal("10");
	// 	tree.deleteByVal("22");

	// 	tree.printInOrder();
	// 	tree.printInOrderDesc();
	// 	tree.printLevelOrder();
	// 	tree.printInNext();
	// 	tree.printInNextDesc();
	// }

	// void testRBTFixedInsertDelete()
	// {
	// 	NS::red_black_tree<Fixed, Fixed> tree;

	// 	tree.insert(42.42f);
	// 	tree.insert(0);
	// 	tree.insert(5.2f);
	// 	tree.insert(2);
	// 	tree.insert(42);
	// 	tree.insert(18.5f);
	// 	tree.insert(6.6f);
	// 	tree.insert(90.13f);
	// 	tree.insert(3);
	// 	tree.insert(3);
	// 	tree.insert(4.0f);
	// 	tree.insert(25.3f);

	// 	tree.printInOrder();
	// 	tree.printInOrderDesc();
	// 	tree.printLevelOrder();
	// 	tree.printInNext();
	// 	tree.printInNextDesc();

	// 	std::cout << std::endl << "Deleting 5.2f, 6.6f, 0, 2, 42" << std::endl;

	// 	tree.deleteByVal(5.2f);
	// 	tree.deleteByVal(6.6f);
	// 	tree.deleteByVal(0);
	// 	tree.deleteByVal(2);
	// 	tree.deleteByVal(42);

	// 	tree.printInOrder();
	// 	tree.printInOrderDesc();
	// 	tree.printLevelOrder();
	// 	tree.printInNext();
	// 	tree.printInNextDesc();

	// }
