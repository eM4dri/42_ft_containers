/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testSet.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:49:56 by emadriga          #+#    #+#             */
/*   Updated: 2023/03/01 23:17:43 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test/testSet.hpp"

#define T1 int

bool fncomp (int lhs, int rhs) {return lhs<rhs;}

struct classcomp {
  bool operator() (const int& lhs, const int& rhs) const
  {return lhs<rhs;}
};

template <typename T_SET>
void	printElements(T_SET const &st, std::string print)
{
	std::cout << print << " content is:" << std::endl;

	typename T_SET::const_iterator it = st.begin(), ite = st.end();
	for (; it != ite; ++it)
		std::cout << "- " << *it << std::endl;
	std::cout << "###############################################" << std::endl;
}

void testThisSet()
{
	NS::set<T1> const st;
	NS::set<T1>::iterator it = st.begin(); // <-- no error, actually ! set allows for const_iterator => iterator conversion

	(void)it;
}

void testConstructor()
{
	NS::set<int> first;                           // empty set of ints

	int myints[]= {10,20,30,40,50};
	NS::set<int> second (myints,myints+5);        // range

	NS::set<int> third (second);                  // a copy of second

	NS::set<int> fourth (second.begin(), second.end());  // iterator ctor.

	NS::set<int,classcomp> fifth;                 // class as Compare

	bool(*fn_pt)(int,int) = fncomp;
	NS::set<int,bool(*)(int,int)> sixth (fn_pt);  // function pointer as Compare

	static const char *names[] =
	{ "first", "second", "third", "fourth", "fifth", "sixth" };
	printElements(first, names[0]);
	printElements(second, names[1]);
	printElements(third, names[2]);
	printElements(fourth, names[3]);
	printElements(fifth, names[4]);
	printElements(sixth, names[5]);

}

void testAssignment()
{
	static const char *names[] =
	{ "first", "second"};
	int myints[]={ 12,82,37,64,15 };
	NS::set<int> first (myints,myints+5);   // set with 5 ints
	NS::set<int> second;                    // empty set
	std::cout << names[0] <<"'s size: " << first.size() << std::endl;
	printElements(first, names[0]);
	std::cout << names[0] <<"'s size: " << second.size() << std::endl;
	printElements(second, names[1]);

	second = first;                          // now second contains the 5 ints
	first = NS::set<int>();                 // and first is empty

	std::cout << names[0] <<"'s size: " << first.size() << std::endl;
	printElements(first, names[0]);
	std::cout << names[0] <<"'s size: " << second.size() << std::endl;
	printElements(second, names[1]);
}

void testIterators()
{
	{
		int myints[] = {75,23,65,42,13};
		NS::set<int> myset (myints,myints+5);

		std::cout << "myset contains(ASC):";
		for (NS::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
		std::cout << ' ' << *it;

		std::cout << std::endl;
	}
	{
		int myints[] = {21,64,17,78,49};
		NS::set<int> myset (myints,myints+5);

		NS::set<int>::reverse_iterator rit;

		std::cout << "myset contains(DESC):";
		for (rit=myset.rbegin(); rit != myset.rend(); ++rit)
		std::cout << ' ' << *rit;

		std::cout << std::endl;
	}
}

void testCapacity()
{
	{

		NS::set<int> myset;

		myset.insert(20);
		myset.insert(30);
		myset.insert(10);

		std::cout << "myset contains:";
		while (!myset.empty())
		{
			std::cout << "size: " << myset.size() << '\t';
			std::cout << "empty: " << myset.empty() << '\t';
			std::cout << "begin: " << *myset.begin() << std::endl;
			myset.erase(myset.begin());
		}
		std::cout << std::endl;
	}
	{
		int i;
		NS::set<int> myset;

		if (myset.max_size()>1000)
		{
			for (i=0; i<1000; i++)
				myset.insert(i);
			std::cout << "The set contains 1000 elements." << std::endl;
		}
		else
			std::cout << "The set could not hold 1000 elements." << std::endl;

	}
}

void testCompares()
{
	NS::set<int> myset;
	int highest;

	for (int i=0; i<=5; i++)
		myset.insert(i);

	std::cout << "myset contains:";

	highest=*myset.rbegin();
	NS::set<int>::iterator it=myset.begin();

	while ( myset.key_comp()(*(++it),highest) )
		std::cout << ' ' << *it;

	std::cout << " using key_comp" << std::endl;

	std::cout << "myset contains:";

	it=myset.begin();

	while ( myset.value_comp()(*(++it),highest) )
		std::cout << ' ' << *it;
	std::cout << " using value_comp" << std::endl;
}

void testInserts()
{
	NS::set<int> myset;
	NS::set<int>::iterator it;
	NS::pair<NS::set<int>::iterator,bool> ret;

	// set some initial values:
	for (int i=1; i<=5; ++i)
		myset.insert(i*10);    // set: 10 20 30 40 50

	ret = myset.insert(20);               // no new element inserted

	if (ret.second==false)
		it=ret.first;  // "it" now points to element 20

	myset.insert (it,25);                 // max efficiency inserting
	myset.insert (it,24);                 // max efficiency inserting
	myset.insert (it,26);                 // no max efficiency inserting

	int myints[]= {5,10,15};              // 10 already in set, not inserted
	myset.insert (myints,myints+3);

	printElements(myset, "myset");
}

void testErases()
{
	NS::set<int> myset;
	NS::set<int>::iterator it;

	// insert some values:
	for (int i=1; i<10; i++)
		myset.insert(i*10);  // 10 20 30 40 50 60 70 80 90

	it = myset.begin();
	++it;                    // "it" points now to 20

	myset.erase (it);

	myset.erase (40);

	it = myset.find (60);
	myset.erase (it, myset.end());

	printElements(myset, "myset");
}

void testSwap()
{
	static const char *names[] =
	{ "first", "second"};
	int myints[]={12,75,10,32,20,25};
	NS::set<int> first (myints,myints+3);     // 10,12,75
	NS::set<int> second (myints+3,myints+6);  // 20,25,32

	first.swap(second);

	printElements(first, names[0]);
	printElements(second, names[1]);
}

void testClear()
{
	NS::set<std::string> myset;
	myset.insert("100");
	myset.insert("200");
	myset.insert("300");
	printElements(myset, "myset");
	myset.clear();
	myset.insert("1101");
	myset.insert("2202");
	printElements(myset, "myset");
}

void testFind()
{
	NS::set<int> myset;
	NS::set<int>::iterator it;

	// set some initial values:
	for (int i=1; i<=5; i++)
		myset.insert(i*10);    // set: 10 20 30 40 50

	it=myset.find(20);
	myset.erase (it);
	myset.erase (myset.find(40));
	printElements(myset, "myset");
}

void testCount()
{
	NS::set<int> myset;

	// set some initial values:
	for (int i=1; i<5; ++i)
		myset.insert(i*3);    // set: 3 6 9 12
	for (int i=0; i<10; ++i)
	{
		std::cout << i;
		if (myset.count(i) != 0)
			std::cout << " is an element of myset." << std::endl;
		else
			std::cout << " is not an element of myset." << std::endl;
	}
}

void testBounds()
{
	NS::set<int> myset;
	NS::set<int>::iterator itlow,itup;

	for (int i=1; i<10; i++) myset.insert(i*10); // 10 20 30 40 50 60 70 80 90

	itlow=myset.lower_bound (30);                //       ^
	itup=myset.upper_bound (60);                 //                   ^

	myset.erase(itlow,itup);                     // 10 20 70 80 90
	printElements(myset, "myset");
}

void testEqualRange()
{
  NS::set<int> myset;

  for (int i=1; i<=5; i++) myset.insert(i*10);   // myset: 10 20 30 40 50

  NS::pair<NS::set<int>::const_iterator,NS::set<int>::const_iterator> ret;
  ret = myset.equal_range(30);

  std::cout << "the lower bound points to: " << *ret.first << std::endl;
  std::cout << "the upper bound points to: " << *ret.second << std::endl;
}
