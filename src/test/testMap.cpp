/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testMap.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:49:56 by emadriga          #+#    #+#             */
/*   Updated: 2023/03/04 19:21:06 by emadriga         ###   ########.fr       */
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
void	printElementsSize(T_MAP const &mp, std::string print = "default")
{
	typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
	std::cout << print << " content is:" << std::endl;
	for (; it != ite; ++it)
		 printPair(it);
	std::cout << "size: " << mp.size() << std::endl;
	if (!DIFF)
		std::cout << "max_size: " << mp.max_size() << std::endl;
	std::cout << "###############################################" << std::endl;
}

template <typename T_MAP>
void	printElementsDesc(T_MAP const &mp, std::string print = "default")
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


template <typename T, typename U>
void	tree_cmp(T &m, U &n) {
	typename T::iterator	mb = m.begin();
	typename T::iterator	me = m.end();
	typename U::iterator	nb = n.begin();
	typename U::iterator	ne = n.end();

	while (mb != me && nb != ne)
	{
		std::cout << "#[" << mb->first << ":" << mb->second << "] ";
		std::cout << "@[" << nb->first << ":" << nb->second << "]#\n";
		++mb;
		++nb;
	}
}

static void testNicoBasics()
{
	NS::map<int,int>		mymap;
	LOG("map basics");

	NS::map<int,int>		m;
	LOG2("\tmap->size()", m.size());
	LOG2("\tmap->empty()", m.empty());
	if (!DIFF)
		LOG2("\tmap->max_size()", m.max_size());
	LOG2("\tmap->insert(5,5)", (m.insert(NS::make_pair(5,5)).second));
	LOG2("\tmap->insert(3,3)", (m.insert(NS::make_pair(3,3)).second));
	LOG2("\tmap->insert(6,6)", (m.insert(NS::make_pair(6,6)).second));
	LOG2("\tmap->insert(1,1)", (m.insert(NS::make_pair(1,1)).second));
	LOG2("\tmap->size()", m.size());
	LOG2("\tmap->empty()", m.empty());
	if (!DIFF)
		LOG2("\tmap->max_size()", m.max_size());
	NS::map<int,int>		n(m);
	
	tree_cmp(m, n);
	LOG2("\tmap[exists]", m[3]);
	LOG2("\tmap[doesn't exist]", m[4]);
	tree_cmp(m, n);
	m.swap(n);
	tree_cmp(m, n);
	m.erase(1);
	if (n==m) std::cout << "\tn and m are equal\n";
 	if (n!=m) std::cout << "\tn and m are not equal\n";
	if (n< m) std::cout << "\tn is less than m\n";
 	if (n> m) std::cout << "\tn is greater than m\n";
  	if (n<=m) std::cout << "\tn is less than or equal to m\n";
  	if (n>=m) std::cout << "\tn is greater than or equal to m\n";
	
	m.clear();
	LOG2("\tmap->size()", m.size());
	LOG2("\tmap->empty()", m.empty());
	if (!DIFF)
		LOG2("\tmap->max_size()", m.max_size());
	tree_cmp(m, m);
	m = n;
	tree_cmp(m, n);
	LOG2("key_comp(1,2)",(m.key_comp())(1,2));
	LOG2("key_comp(2,1)",(m.key_comp())(2,1));
	LOG2("value_comp(beg, ++beg)",m.value_comp()(*m.begin(), *(++m.begin())));
	LOG2("value_comp(beg,++(++beg))",m.value_comp()(*m.begin(), *++(++m.begin())));
	LOG2("find(3)", m.find(3)->first);
	LOG2("count(exists)", m.count(5));
	LOG2("count(doesn't exist)", m.count(99));
	LOG2("lower bound", m.lower_bound(5)->first);
	LOG2("upper bound", m.upper_bound(5)->first);
	LOG2("equal range", m.equal_range(5).first->first);
	printElementsDesc(m);
	printElementsDesc(n);
}

static void testNico2nd()
{	
	std::map<int, std::string> msys;
	{
		std::pair<int, std::string> psys(1, "1");
		std::pair<int, std::string> psys2(2, "2");
		msys.insert(psys);

		int i = 0;
		LOG("single node");
		LOG("incrementing");
		for (std::map<int, std::string>::iterator isys = msys.begin();  isys != msys.end() ; ++isys)
		{
			++i;
			std::cout << "\t" << i << ")" << " " << isys->first << ":" << isys->second << std::endl; 
		}
		i = 0;	
		LOG("decrement");
		for (std::map<int, std::string>::iterator isys = --(msys.end());  isys != msys.begin() ; --isys)
		{
			++i;
			std::cout << "\t" << i << ")" << " " << isys->first << ":" << isys->second << std::endl; 
		}
		LOG("two nodes (right favored)");
		i = 0;	
		msys.insert(psys2);
		LOG("incrementing");
		for (std::map<int, std::string>::iterator isys = msys.begin();  isys != msys.end() ; ++isys)
		{
			++i;
			std::cout << "\t" << i << ")" << " " << isys->first << ":" << isys->second << std::endl; 
		}
		
		i = 0;	
		LOG("decrement");
		for (std::map<int, std::string>::iterator isys = --(msys.end());  isys != msys.begin() ; --isys)
		{
			++i;
			std::cout << "\t" << i << ")" << " " << isys->first << ":" << isys->second << std::endl; 
		}

		
		LOG("///MAP DELETIOn TESTS\\\\\\");
		NS::map<int,int>	del;
		NS::pair<int, int>	ds1(1,1);
		NS::pair<int, int>	ds2(2,2);
		NS::pair<int,int>	ds3(3,3);
		NS::pair<int, int>	ds4(4,4);
		NS::pair<int, int>	ds5(5,5);
		NS::pair<int, int>	ds6(6,6);

		LOG("contents pre erase:");
		del.insert(ds1);
		del.insert(ds2);
		del.insert(ds3);
		del.insert(ds4);
		del.insert(ds5);
		del.insert(ds6);
		for (NS::map<int, int>::iterator isys = del.begin();  isys != del.end() ; ++isys)
		{
			std::cout << isys->first << ":" << isys->second << std::endl; 
		}
		del.erase(del.begin());
		LOG("begin() erase:(no children)");
		for (NS::map<int, int>::iterator isys = del.begin();  isys != del.end() ; ++isys)
		{
			std::cout << isys->first << ":" << isys->second << std::endl; 
		}
		del.erase(del.find(4));
		LOG("find(4) erase:(root of tree, two children)");
		for (NS::map<int, int>::iterator isys = del.begin();  isys != del.end() ; ++isys)
		{
			std::cout << isys->first << ":" << isys->second << std::endl; 
		}
		printElementsDesc(del);
		printElementsDesc(msys);
	}
}
static void testNico3rd()
{
	std::list<NS::pair<const int, int> > lst;
	unsigned int lst_size = 7;
	
	for (unsigned int i = 0; i < 7; ++i)
	{
		lst.push_back(NS::pair<const int, int> (lst_size - i, i));
	}

	NS::map<int, int> mp(lst.begin(), lst.end());
	NS::map<int, int>::iterator it = mp.begin();
	NS::map<int, int>::iterator ite = mp.end();

	NS::map<int,int> mrc(it, --(--ite));

	
	std::list<NS::pair<const int, char> > lsterase;

	lst_size = 10;
	for (unsigned int i = 0; i < lst_size; ++i)
	{
		lsterase.push_back(NS::make_pair((int)lst_size - i, (int)i + 65));
	}
	NS::map<int, int> mpe(lsterase.begin(), lsterase.end());
	std::cout << "Deling " << (++mpe.begin())->first << std::endl;
	mpe.erase(++mpe.begin());

	std::cout << "Deling " << (mpe.begin())->first << std::endl;
	mpe.erase(mpe.begin());
	

	std::cout << "Deling " << (--mpe.end())->first << std::endl;
	mpe.erase(--mpe.end());
	
	std::cout << "Deling " << (--(--mpe.end()))->first << std::endl;
	mpe.erase(--(--mpe.end()));
	printElementsDesc(mp);
	printElementsDesc(mpe);
}

static void testNico4th()
{
	std::list<NS::pair<const int, std::string> > lst;
	unsigned int lst_size = 10;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(NS::pair<const int, std::string >(i, std::string((lst_size - i), i + 65)));
	NS::map<int, std::string> mp(lst.begin(), lst.end());

	std::cout << "erase " << (++mp.begin())->first << std::endl;
	mp.erase( ++mp.begin());

	std::cout << "erase " << mp.begin()->first << std::endl;
	mp.erase( mp.begin());

	std::cout << "erase " << (--mp.end())->first << std::endl;
	mp.erase( --mp.end());

	std::cout << std::endl;
	mp.erase(mp.begin(), ++(++(++mp.begin())));
	std::cout << "erasing range :\n";
	for (NS::map<int, std::string>::iterator i = --(--(--mp.end())); i != --mp.end();  ++i)
	{
		std::cout << "(" << i->first << ")" << " ";
	}
	printElementsDesc(mp);
}

template <typename MAP, typename T1>
void	ft_erase(MAP &mp, const T1 param)
{
	std::cout << "\t-- [" << param << "] --" << std::endl;
	mp.erase(param);
}

static void testNico5th()
{
	LOG("TRICKY ERASURE");
	NS::map<int, std::string> mp;
	mp[42] = "lol";
	mp[50] = "mdr";
	mp[25] = "funny";

	mp[46] = "bunny";
	mp[21] = "fizz";
	mp[30] = "buzz";
	mp[55] = "fuzzy";

	mp[18] = "bee";
	mp[23] = "coconut";
	mp[28] = "diary";
	mp[35] = "fiesta";
	mp[44] = "hello";
	mp[48] = "world";
	mp[53] = "this is a test";
	mp[80] = "hey";

	mp[12] = "no";
	mp[20] = "idea";
	mp[22] = "123";
	mp[24] = "345";
	mp[27] = "27";
	mp[29] = "29";
	mp[33] = "33";
	mp[38] = "38";

	mp[43] = "1";
	mp[45] = "2";
	mp[47] = "3";
	mp[49] = "4";
	mp[51] = "5";
	mp[54] = "6";
	mp[60] = "7";
	mp[90] = "8";
	printElementsDesc(mp);
	ft_erase(mp, 25); // right != NULL; left != NULL
	ft_erase(mp, 55); // right != NULL; left != NULL
	ft_erase(mp, 24); // right != NULL; left != NULL
	ft_erase(mp, 54); // right != NULL; left != NULL
	ft_erase(mp, 22); // right == NULL; left == NULL
	ft_erase(mp, 51); // right == NULL; left == NULL
	ft_erase(mp, 21); // right == NULL; left != NULL
	ft_erase(mp, 53); // right != NULL; left == NULL
	ft_erase(mp, 20); // right == NULL; left != NULL
	ft_erase(mp, 23); // right != NULL; left != NULL
	ft_erase(mp, 42); // right != NULL; left != NULL; parent == NULL
	ft_erase(mp, 38); // right != NULL; left != NULL; parent == NULL
	ft_erase(mp, 35); // right != NULL; left != NULL; parent == NULL
	ft_erase(mp, 33); // right != NULL; left != NULL; parent == NULL
	printElementsDesc(mp);
}
static void testNico6th()
{
	LOG("complex insertion 🤯, worst case scenario");
	NS::map<int, int> m;
	
	for (size_t i = 0; i < 1e6;++i)
	{
		m.insert(NS::make_pair(i, i % 99));
	}
	LOG("in order");
	for (NS::map<int, int>::iterator i = m.begin(); i != m.end(); ++i)
	{ 
		std::cout << i->second << "\n";
	}
	LOG("in reverse");
	for (NS::map<int, int>::reverse_iterator i = m.rbegin(); i != m.rend(); ++i)
	{ 
		std::cout << i->second<< "\n";
	}
	printElementsDesc(m);
	printElementsSize(m);
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

static void testAnaPerformance()
{
	NS::map<int, std::string> m;

	for (int i = 0; i < 100000; i++)
		m.insert(NS::pair<int, std::string>(i, "a"));
	
	printElementsDesc(m);

	for (int i = 0; i < 100000; i++)
		m.erase(i);

	for (int i = 21000; i < 50000; i+=100)
		m.find(i);
}

//	public

void testMap()
{
	performTest("Map's int insert", &testInserts);
	performTest("Map's constructor", &testConstructor);
	performTest("Map's assignment", &testAssigment);
	performTest("Map's iterators", &testIteratorsAccess);
	performTest("Map's capacity", &testCapacity);
	performTest("Map's inserts", &testInserts);
	performTest("Map's erases", &testErases);
	performTest("Map's swap", &testSwap);
	performTest("Map's clear", &testClear);
	performTest("Map's compares", &testCompares);
	performTest("Map's bounds", &testBounds);
	performTest("Map's count", &testCount);
	performTest("Map's equal_range", &testEqualRange);
	performTest("Map's find", &testFind);
	performTest("Map's Ana", &testAnaPerformance);
	if (EXTRA)
	{
		performTest("Map's nico basics", &testNicoBasics);
		performTest("Map's nico 2nd", &testNico2nd);
		performTest("Map's nico 3rd", &testNico3rd);
		performTest("Map's nico 4th", &testNico4th);
		performTest("Map's nico 5th", &testNico5th);
		performTest("Map's nico 6th", &testNico6th);
	}
}
