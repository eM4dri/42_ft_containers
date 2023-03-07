/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testTree.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:49:56 by emadriga          #+#    #+#             */
/*   Updated: 2023/03/07 17:03:15 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "test/testTree.hpp"

#ifdef LOGTREE
//	private
	static void testInitial()
	{

		NS::set<int> mySet;
		mySet.insert(15);
		mySet.insert(16);
		mySet.insert(17);
		mySet.insert(14);
		mySet.insert(13);
		mySet.insert(18);
		mySet.insert(19);
		mySet.insert(12);
		mySet.insert(11);
		mySet.insert(20);
		mySet.insert(21);
		mySet.insert(10);
		mySet.insert(9);
		mySet.insert(22);
		mySet.insert(23);
		mySet.insert(8);
		mySet.insert(7);
		mySet.insert(24);
		mySet.insert(25);
		mySet.m_Tree.printLevelOrder();
	}

	void testInsertParentUncleRed()
	{
		NS::set<std::string> mySet;
		mySet.insert("1");
		mySet.insert("2");
		mySet.insert("3 uncle");
		mySet.insert("4 grandparent");
		mySet.insert("5 parent");
		mySet.m_Tree.printLevelOrder();
		LOG("mySet.insert(\"6\");");
		mySet.insert("6 son");
		mySet.m_Tree.printLevelOrder();
	}

	void testInsertLeftLeft()
	{
		NS::set<std::string> mySet;
		mySet.insert("5");
		mySet.insert("4");
		mySet.insert("3 granparent");
		mySet.insert("2 parent");
		mySet.m_Tree.printLevelOrder(true);
		LOG("mySet.insert(\"1\");");
		mySet.insert("1 son");
		mySet.m_Tree.printLevelOrder();
	}

	void testInsertRightRight()
	{
		NS::set<std::string> mySet;
		mySet.insert("1");
		mySet.insert("2");
		mySet.insert("3 granparent");
		mySet.insert("4 parent");
		mySet.m_Tree.printLevelOrder(true);
		LOG("mySet.insert(\"5\");");
		mySet.insert("5 son");
		mySet.m_Tree.printLevelOrder();
	}

	void testInsertLeftRight()
	{
		NS::set<std::string> mySet;
		mySet.insert("5");
		mySet.insert("4");
		mySet.insert("3 granparent");
		mySet.insert("1 parent");
		mySet.m_Tree.printLevelOrder(true);
		LOG("mySet.insert(\"2\");");
		mySet.insert("2 son");
		mySet.m_Tree.printLevelOrder();
	}

	void testInsertRightLeft()
	{
		NS::set<std::string> mySet;
		mySet.insert("1");
		mySet.insert("2");
		mySet.insert("3 granparent");
		mySet.insert("5 parent");
		mySet.m_Tree.printLevelOrder(true);
		LOG("mySet.insert(\"4\");");
		mySet.insert("4 son");
		mySet.m_Tree.printLevelOrder();
	}

	static void testRemoveRpBs2Bc()
	{
		NS::set<std::string> mySet;
		mySet.insert("5");
		mySet.insert("4");
		mySet.insert("6 sibling");
		mySet.insert("3");
		mySet.insert("2");
		mySet.insert("7 parent");
		mySet.insert("9 ❌");
		mySet.insert("8");
		mySet.erase("8");
		mySet.m_Tree.printLevelOrder(true);
		LOG("mySet.erase(\"9\");");
		mySet.erase("9 ❌");
		mySet.m_Tree.printLevelOrder();
	}

	static void testRemoveBpBs2Bc()
	{
		NS::set<std::string> mySet;
		mySet.insert("11");
		mySet.insert("12");
		mySet.insert("13");
		mySet.insert("14");
		mySet.insert("15 ❌");
		mySet.insert("16 parent");
		mySet.insert("17 sibling");
		mySet.insert("18");
		mySet.insert("19");
		mySet.insert("21");
		mySet.insert("22");
		mySet.insert("23");
		mySet.insert("24");
		mySet.insert("25");
		mySet.insert("26");
		mySet.insert("27");
		mySet.insert("28");
		mySet.insert("29");
		mySet.erase("29");
		mySet.erase("27");
		mySet.erase("28");
		mySet.erase("24");
		mySet.erase("25");
		mySet.erase("26");
		mySet.erase("22");
		mySet.m_Tree.printLevelOrder(true);
		LOG("mySet.erase(\"15\");");
		mySet.erase("15 ❌");
		mySet.m_Tree.printLevelOrder();
	}

	static void testRemoveBsRBc()
	{
		NS::set<std::string> mySet;
		mySet.insert("1");
		mySet.insert("2");
		mySet.insert("3");
		mySet.insert("4");
		mySet.insert("5 ❌");
		mySet.insert("6 parent");
		mySet.insert("7");
		mySet.insert("8 sibling");
		mySet.erase("7");
		mySet.insert("7 newphew");
		mySet.m_Tree.printLevelOrder(true);
		LOG("mySet.erase(\"5\");");
		mySet.erase("5 ❌");
		mySet.m_Tree.printLevelOrder();
	}

	static void testRemoveB2Rc()
	{
		NS::set<std::string> mySet;
		mySet.insert("1");
		mySet.insert("2");
		mySet.insert("3");
		mySet.insert("4");
		mySet.insert("5 ❌");
		mySet.insert("6 parent");
		mySet.insert("7");
		mySet.insert("8 sibling");
		mySet.erase("7");
		mySet.insert("7 newphew");
		mySet.insert("9 outer newphew");
		mySet.m_Tree.printLevelOrder();
		LOG("mySet.erase(\"5\");");
		mySet.erase("5 ❌");
		mySet.m_Tree.printLevelOrder();
	}

	static void testErase2BLeftLeft()
	{
		NS::set<std::string> mySet;
		mySet.insert("5 ❌");
		mySet.insert("4 parent");
		mySet.insert("3 red right newphew");
		mySet.insert("2 sibling");
		mySet.insert("1 red left newphew");
		mySet.m_Tree.printLevelOrder();
		LOG("mySet.erase(\"5\");");
		mySet.erase("5 ❌");
		mySet.m_Tree.printLevelOrder();
	}

	static void testErase2BLeftRight()
	{
		NS::set<std::string> mySet;
		mySet.insert("5 ❌");
		mySet.insert("4 parent");
		mySet.insert("3 red right newphew");
		mySet.insert("2 sibling");
		mySet.insert("1");
		mySet.erase("1");
		mySet.m_Tree.printLevelOrder();
		LOG("mySet.erase(\"5\");");
		mySet.erase("5 ❌");
		mySet.m_Tree.printLevelOrder();
	}

	static void testErase2BRightLeft()
	{
		NS::set<std::string> mySet;
		mySet.insert("1 ❌");
		mySet.insert("2 parent");
		mySet.insert("3 red left newphew");
		mySet.insert("4 sibling");
		mySet.insert("5");
		mySet.erase("5");
		mySet.m_Tree.printLevelOrder(true);
		LOG("mySet.erase(\"1\");");
		mySet.erase("1 ❌");
		mySet.m_Tree.printLevelOrder();
	}

	static void testErase2BRightRight()
	{
		NS::set<std::string> mySet;
		mySet.insert("1 ❌");
		mySet.insert("2 parent");
		mySet.insert("3 sibling");
		mySet.insert("4 red right newphew");
		mySet.m_Tree.printLevelOrder(true);
		LOG("mySet.erase(\"1\");");
		mySet.erase("1 ❌");
		mySet.m_Tree.printLevelOrder();
	}

	static void testErase2BBs2Bc()
	{
		NS::set<std::string> mySet;
		mySet.insert("1 ❌");
		mySet.insert("2 parent");
		mySet.insert("3 sibling");
		mySet.insert("4");
		mySet.erase("4");
		mySet.m_Tree.printLevelOrder(true);
		LOG("mySet.erase(\"1\");");
		mySet.erase("1 ❌");
		mySet.m_Tree.printLevelOrder(true);
	}

	static void testErase2BRs()
	{
		NS::set<std::string> mySet;
		mySet.insert("1 ❌");
		mySet.insert("2 parent");
		mySet.insert("4 sibling");
		mySet.insert("3 left newphew");
		mySet.insert("5 right newphew");
		mySet.insert("6");
		mySet.erase("6");
		mySet.m_Tree.printLevelOrder();
		LOG("mySet.erase(\"1\");");
		mySet.erase("1 ❌");
		mySet.m_Tree.printLevelOrder();
	}

//	public

	void testTree()
	{
		performTest("Tree's initial", &testInitial);

		//https://www.happycoders.eu/algorithms/red-black-tree-java/#:~:text=Case%201%3A%20New%20node%20is,inserted%20node%20is%20%22inner%20grandchild%22
		performTest("Tree's insert parent & uncle red", &testInsertParentUncleRed);
		performTest("Tree's insert left left case", &testInsertLeftLeft);
		performTest("Tree's insert left right case", &testInsertLeftRight);
		performTest("Tree's insert right left case", &testInsertRightLeft);
		performTest("Tree's insert right right case", &testInsertRightRight);
		performTest("Tree's erase red parent & black sibling with 2 black children case", &testRemoveRpBs2Bc);
		performTest("Tree's erase black parent & black sibling with 2 black children case", &testRemoveBpBs2Bc);
		performTest("Tree's erase black sibling with 1 red & 1 black (outer newphew) childrens case", &testRemoveBsRBc);
		performTest("Tree's erase black sibling with 2 red childrens case", &testRemoveB2Rc);

		//https://www.geeksforgeeks.org/deletion-in-red-black-tree/?ref=lbp
		performTest("Tree's erase doubleblack left left case", &testErase2BLeftLeft);
		performTest("Tree's erase doubleblack left right case", &testErase2BLeftRight);
		performTest("Tree's erase doubleblack right left case", &testErase2BRightLeft);
		performTest("Tree's erase doubleblack right right case", &testErase2BRightRight);
		performTest("Tree's erase doubleblack black sibling with 2 black children case", &testErase2BBs2Bc);
		performTest("Tree's erase doubleblack red sibling", &testErase2BRs);
	}
#else
	void testTree(){}
#endif
