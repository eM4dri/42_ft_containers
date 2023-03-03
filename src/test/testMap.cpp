/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testMap.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:49:56 by emadriga          #+#    #+#             */
/*   Updated: 2023/03/03 17:34:05 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test/testMap.hpp"

//	private

static bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp {
bool operator() (const char& lhs, const char& rhs) const
  {return lhs<rhs;}
};

template <typename T>
static void	printPair(const T &iterator)
{
	std::cout << "key: " << iterator->first;
	std::cout << " | value: " << iterator->second;
	std::cout << std::endl;
}

template <typename T_MAP>
void	printElementsSize(T_MAP const &mp, std::string print)
{
	typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
	std::cout << print << " content is:" << std::endl;
	for (; it != ite; ++it)
		 printPair(it);
	std::cout << "size: " << mp.size() << std::endl;
	std::cout << "max_size: " << mp.max_size() << std::endl;
	std::cout << "###############################################" << std::endl;
}

template <typename T_MAP>
void	printElementsDesc(T_MAP const &mp, std::string print)
{
	typename T_MAP::const_reverse_iterator it = mp.rbegin(), ite = mp.rend();
	std::cout << print << " content desc is:" << std::endl;
	for (; it != ite; ++it)
		 printPair(it);
	std::cout << "###############################################" << std::endl;
}

static void testInserts()
{
	NS::map<char,int> mymap;

	// first insert function version (single parameter):
	mymap.insert ( NS::pair<char,int>('a',100) );
	mymap.insert ( NS::pair<char,int>('z',200) );

	NS::pair<NS::map<char,int>::iterator,bool> ret;
	ret = mymap.insert ( NS::pair<char,int>('z',500) );
	if (ret.second==false) {
		std::cout << "element 'z' already existed";
		std::cout << " with a value of " << ret.first->second << std::endl;
	}

	//second insert function version (with hint position):
	NS::map<char,int>::iterator it = mymap.begin();
	mymap.insert (it, NS::pair<char,int>('b',300));  // max efficiency inserting
	mymap.insert (it, NS::pair<char,int>('c',400));  // no max efficiency inserting

	// third insert function version (range insertion):
	NS::map<char,int> anothermap;
	anothermap.insert(mymap.begin(), mymap.find('c'));

	// showing contents:
	printElementsSize(mymap, "mymap");
	printElementsSize(anothermap, "anothermap");
}

static void nicostest()
{
	NS::map<int,int>		mymap;
	LOG(mymap.size());
	LOG(mymap.empty());
	LOG(mymap.max_size());
	LOG(mymap.insert(NS::make_pair(5,5)).second);
	LOG(mymap.insert(NS::make_pair(3,3)).second);
	LOG(mymap.insert(NS::make_pair(6,6)).second);
	LOG(mymap.insert(NS::make_pair(1,1)).second);
	LOG(mymap.size());
	LOG(mymap.empty());
	LOG(mymap.max_size());
	printElementsSize(mymap, "mymap");
}
static void testConstructor()
{
	NS::map<char,int> first;

	first['a']=10;
	first['b']=30;
	first['c']=50;
	first['d']=70;

	NS::map<char,int> second (first.begin(),first.end());

	NS::map<char,int> third (second);

	NS::map<char,int,classcomp> fourth;                 // class as Compare

	bool(*fn_pt)(char,char) = fncomp;
	NS::map<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as Compare
	static const char *names[] =
	{ "first", "second", "third", "fourth", "fifth" };
	printElementsSize(first, names[0]);
	printElementsSize(second, names[1]);
	printElementsSize(third, names[2]);
	printElementsSize(fourth, names[3]);
	printElementsSize(fifth, names[4]);
}

static void testAssigment()
{
	NS::map<char,int> first;
	NS::map<char,int> second;

	first['x']=8;
	first['y']=16;
	first['z']=32;

	second=first;                // second now contains 3 ints
	first=NS::map<char,int>();  // and first is now empty

	static const char *names[] =
		{ "first", "second"};
	printElementsSize(first, names[0]);
	printElementsSize(second, names[1]);
}

void testIteratorsAccess()
{
	NS::map<char,std::string> mymap;

	mymap['a']="an element";
	mymap['b']="another element";
	mymap['c']=mymap['b'];

	std::cout << "mymap['a'] is " << mymap['a'] << std::endl;
	std::cout << "mymap['b'] is " << mymap['b'] << std::endl;
	std::cout << "mymap['c'] is " << mymap['c'] << std::endl;
	std::cout << "mymap['d'] is " << mymap['d'] << std::endl;

	printElementsSize(mymap, "mymap");
	printElementsDesc(mymap, "mymap");
}

static void testCapacity()
{
	{
		NS::map<char,int> mymap;

		mymap['a']=10;
		mymap['b']=20;
		mymap['c']=30;

		while (!mymap.empty())
		{
			std::cout << mymap.begin()->first << " => " << mymap.begin()->second << std::endl;
			mymap.erase(mymap.begin());
		}
	}
	{
		int i;
		NS::map<int,int> mymap;

		if (mymap.max_size()>1000)
		{
			for (i=0; i<1000; i++) mymap[i]=0;
				std::cout << "The map contains 1000 elements." << std::endl;
		}
		else
			std::cout << "The map could not hold 1000 elements." << std::endl;
		std::cout << "mymap.size() is " << mymap.size() << std::endl;
	}
}

static void testErases()
{
	NS::map<char,int> mymap;
	NS::map<char,int>::iterator it;

	// insert some values:
	mymap['a']=10;
	mymap['b']=20;
	mymap['c']=30;
	mymap['d']=40;
	mymap['e']=50;
	mymap['f']=60;

	printElementsSize(mymap, "mymap");

	it=mymap.find('b');
	mymap.erase (it);                   // erasing by iterator

	mymap.erase ('c');                  // erasing by key

	it=mymap.find ('e');
	mymap.erase ( it, mymap.end() );    // erasing by range

	// show content:
	printElementsSize(mymap, "mymap");
}

static void testSwap()
{
	NS::map<char,int> foo,bar;

	foo['x']=100;
	foo['y']=200;

	bar['a']=11;
	bar['b']=22;
	bar['c']=33;

	foo.swap(bar);

	printElementsSize(foo, "foo");
	printElementsSize(bar, "bar");
}

static void testClear()
{
	NS::map<char,int> mymap;

	mymap['x']=100;
	mymap['y']=200;
	mymap['z']=300;

	printElementsSize(mymap, "mymap");

	mymap.clear();
	mymap['a']=1101;
	mymap['b']=2202;

	printElementsSize(mymap, "mymap");
}

static void testCompares()
{
	NS::map<char,int> mymap;

	mymap['a']=100;
	mymap['b']=200;
	mymap['c']=300;

	NS::map<char,int>::iterator highest = --mymap.end();	// key value of last element
	// *--highest;
	NS::map<char,int>::iterator it = mymap.begin();

	std::cout << "mymap contains(key_comp):" << std::endl;
	while ( mymap.key_comp()((*it++).first, highest->first))
		std::cout << it->first << " => " << it->second << std::endl;

 	highest = --mymap.end();
	it = mymap.begin();
	std::cout << "mymap contains(value_comp):" << std::endl;
	while ( mymap.value_comp()(*it++, *highest) )
		std::cout << it->first << " => " << it->second << std::endl;

}

static void testBounds()
{
	NS::map<char,int> mymap;
	NS::map<char,int>::iterator itlow,itup;

	mymap['a']=20;
	mymap['b']=40;
	mymap['c']=60;
	mymap['d']=80;
	mymap['e']=100;

	itlow=mymap.lower_bound ('b');  // itlow points to b
	itup=mymap.upper_bound ('d');   // itup points to e (not d!)

	mymap.erase(itlow,itup);        // erases [itlow,itup)
	printElementsSize(mymap, "mymap");
}

static void testCount()
{
	NS::map<char,int> mymap;
	char c;

	mymap ['a']=101;
	mymap ['c']=202;
	mymap ['f']=303;

	for (c='a'; c<'h'; c++)
	{
		std::cout << c;
		if (mymap.count(c)>0)
			std::cout << " is an element of mymap." << std::endl;
		else
			std::cout << " is not an element of mymap." << std::endl;
	}
}

static void testEqualRange()
{
	NS::map<char,int> mymap;

	mymap['a']=10;
	mymap['b']=20;
	mymap['c']=30;

	NS::pair<NS::map<char,int>::iterator,NS::map<char,int>::iterator> ret;
	ret = mymap.equal_range('b');

	std::cout << "lower bound points to: ";
	printPair(ret.first);
	std::cout << std::endl;

	std::cout << "upper bound points to: ";
	printPair(ret.second);
	std::cout << std::endl;
}

static void testFind()
{
	NS::map<char,int> mymap;
	NS::map<char,int>::iterator it;

	mymap['a']=50;
	mymap['b']=100;
	mymap['c']=150;
	mymap['d']=200;

	it = mymap.find('b');
	if (it != mymap.end())
	mymap.erase (it);

	// print content:
	std::cout << "elements in mymap:" << std::endl;
	std::cout << "a => " << mymap.find('a')->second << std::endl;
	std::cout << "c => " << mymap.find('c')->second << std::endl;
	std::cout << "d => " << mymap.find('d')->second << std::endl;
}

//	public

void testMap()
{
	performTest("Map's int insert", &testInserts);
	performTest("Map's nico", &nicostest);
	performTest("Set's constructor", &testConstructor);
	performTest("Set's assignment", &testAssigment);
	performTest("Set's iterators", &testIteratorsAccess);
	performTest("Set's capacity", &testCapacity);
	performTest("Set's inserts", &testInserts);
	performTest("Set's erases", &testErases);
	performTest("Set's swap", &testSwap);
	performTest("Set's clear", &testClear);
	performTest("Set's compares", &testCompares);
	performTest("Set's bounds", &testBounds);
	performTest("Set's count", &testCount);
	performTest("Set's equal_range", &testEqualRange);
	performTest("Set's find", &testFind);

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
