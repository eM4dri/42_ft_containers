/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testVector.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:49:56 by emadriga          #+#    #+#             */
/*   Updated: 2023/03/04 16:37:53 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test/testVector.hpp"

//	private
template<typename T >
static void printVectorSize(NS::vector<T> & vector){
	std::cout << "Print vector using [] & size" << std::endl;
	std::cout << "Vector size "<< vector.size() << std::endl;
	for (size_t i = 0; i < vector.size(); i++)
	{
		if (DIFF)
			std::cout << vector[i] << std::endl;
		else
			std::cout << vector[i] << "\t\t" << &vector[i] << std::endl;
	}
	std::cout << "\t-------------\t" << std::endl;
}

template<typename T >
static void printVectorIterator(NS::vector<T> & vector){
	std::cout << "Print vector using iterator" << std::endl;
	for (typename NS::vector<T>::iterator it  = vector.begin();
	it != vector.end(); it++)
	{
		if (DIFF)
			std::cout << *it << std::endl;
		else
			std::cout << *it << "\t\t" << &(*it) << std::endl;
	}
	std::cout << "\t-------------\t" << std::endl;
}

template<typename T >
static void printVectorReverseIterator(NS::vector<T> & vector){
	std::cout << "Print vector using reverse iterator" << std::endl;
	for (typename NS::vector<T>::reverse_iterator it  = vector.rbegin();
	it != vector.rend(); it++)
	{
		if (DIFF)
			std::cout << *it << std::endl;
		else
			std::cout << *it << "\t\t" << &(*it) << std::endl;
	}
	std::cout << "\t-------------\t" << std::endl;
}

static void testStringPushPop()
{
	NS::vector<std::string> vector;
	vector.push_back("1 ycarro");
	vector.push_back("2 jmatute");
	vector.push_back("3 jalvarad");
	vector.push_back("4 tomartin");
	vector.push_back("5 crisfern");
	vector.push_back("6 agallipo");
	vector.pop_back();
	printVectorSize(vector);
	printVectorIterator(vector);
	printVectorReverseIterator(vector);
}

static void testFixedPushPop()
{
	NS::vector<Fixed> vector;
	vector.push_back(42.42f);
	vector.push_back(0);
	vector.push_back(5.2f);
	vector.push_back(0);
	vector.pop_back();
	printVectorSize(vector);
	printVectorIterator(vector);
	printVectorReverseIterator(vector);
}

static void testStringInsert()
{
	NS::vector<std::string> vector;
	vector.push_back("1 ycarro");
	vector.push_back("2 jmatute");
	vector.push_back("3 jalvarad");
	vector.push_back("4 tomartin");
	vector.push_back("5 crisfern");
	vector.push_back("6 agallipo");

	NS::vector<std::string>::iterator it  = vector.begin();
	it++;
	vector.insert(it, 3,"+3 carcebo");
	printVectorIterator(vector);
	NS::vector<std::string>::iterator it2  = vector.begin();
	it2  = vector.begin();
	it2++;
	it2++;
	it2++;
	vector.insert(it2, "+1 emadriga");
	it2  = vector.begin();
	it2++;
	it2++;
	it2++;
	if (!DIFF)
		std::cout << *it2 << "\t\t" << &(*it2) << std::endl;
	else
		std::cout << *it2 << std::endl;
	printVectorSize(vector);
}

static void testInsert()
{
	NS::vector<int> myvector;

	myvector.push_back(3);
	myvector.push_back(100);
	NS::vector<int>::iterator it = myvector.begin();

	it = myvector.insert ( it , 200 );

	myvector.insert (it,2,300);

	// "it" no longer valid, get a new one:
	it = myvector.begin();

	NS::vector<int> anothervector;
	myvector.insert (it, anothervector.begin(),anothervector.end());
	anothervector.push_back(2);
	anothervector.push_back(400);
	it++;
	it++;
	myvector.insert (it, anothervector.begin(),anothervector.end());

	int myarray [] = { 501,502,503 };
	myvector.insert (myvector.begin(), myarray, myarray+3);

	std::cout << "myvector contains:";
	for (it=myvector.begin(); it != myvector.end(); it++)
		std::cout << ' ' << *it;
	std::cout << std::endl;
}

static void testFixedErase(void)
{
	NS::vector<Fixed> vector;
	vector.push_back(42.42f);
	vector.push_back(0);
	vector.push_back(5.2f);
	vector.push_back(2);
	vector.push_back(42);
	vector.push_back(18.5f);
	vector.push_back(6.6f);
	vector.push_back(90.13f);
	vector.push_back(3);
	vector.push_back(3);
	vector.push_back(4.0f);
	vector.push_back(25.3f);
	vector.erase(vector.begin() + 2);
	vector.erase(vector.end() - 3, vector.end() - 1);

 	printVectorSize(vector);
	printVectorIterator(vector);
	printVectorReverseIterator(vector);
}

static void testConstructor()
{
	// constructors used in the same order as described above:
	NS::vector<int> first;                                // empty vector of ints
	NS::vector<int> second (4,100);                       // four ints with value 100
	NS::vector<int> third (second.begin(),second.end());  // iterating through second
	NS::vector<int> fourth (third);                       // a copy of third

	// the iterator constructor can also be used to construct from arrays:
	int myints[] = {16,2,77,29};
	NS::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

	std::cout << "The contents of fifth are:";
	for (NS::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << std::endl;
}

static void testAssignment()
{
	NS::vector<int> foo (3,0);
	NS::vector<int> bar (5,0);

	bar = foo;
	foo = NS::vector<int>();

	std::cout << "Size of foo: " << int(foo.size()) << std::endl;
	std::cout << "Size of bar: " << int(bar.size()) << std::endl;
}

static void testIterators()
{
	{
		NS::vector<int> myvector;
		for (int i=1; i<=5; i++)
			myvector.push_back(i);

		printVectorIterator(myvector);
	}
	{
		NS::vector<int> myvector (5);  // 5 default-constructed ints

		int i=0;

		NS::vector<int>::reverse_iterator rit = myvector.rbegin();
		for (; rit!= myvector.rend(); ++rit)
			*rit = ++i;

		printVectorReverseIterator(myvector);
	}
}

static void testCapacity()
{
	NS::vector<int> myints;
	std::cout << "0. size: " << myints.size() << std::endl;

	for (int i=0; i<10; i++)
		myints.push_back(i);
	std::cout << "1. size: " << myints.size() << '\t';
	if (!DIFF)
		std::cout << "capacity: " << myints.capacity() << "\t";
	if (!DIFF)
		std::cout << "max_size: " << myints.max_size();
  	std::cout << std::endl;

	myints.insert (myints.end(),10,100);
	std::cout << "2. size: " << myints.size() << '\t';
	if (!DIFF)
		std::cout << "capacity: " << myints.capacity() << "\t";
	if (!DIFF)
		std::cout << "max_size: " << myints.max_size();
  	std::cout << std::endl;

	myints.pop_back();
	std::cout << "3. size: " << myints.size() << '\t';
	if (!DIFF)
	  	std::cout << "capacity: " << myints.capacity() << "\t";
	if (!DIFF)
		std::cout << "max_size: " << myints.max_size();
  	std::cout << std::endl;
}

static void testResizeAt()
{

	NS::vector<int> myvector;

	// set some initial content:
	for (int i=1;i<10;i++)
	myvector.push_back(i);

	myvector.resize(5);
	myvector.resize(8,100);
	myvector.resize(12);

	std::cout << "myvector contains:";
	for (size_t i=0;i<myvector.size();i++)
		std::cout << ' ' << myvector.at(i);
	std::cout << std::endl;

}

static void testEmpty()
{
	NS::vector<int> myvector;
	int sum (0);

	for (int i=1;i<=10;i++)
	myvector.push_back(i);

	while (!myvector.empty())
	{
		sum += myvector.back();
		myvector.pop_back();
	}

	std::cout << "total: " << sum << std::endl;
}

static void testReserve()
{
	NS::vector<int>::size_type sz;

	NS::vector<int> foo;
	sz = foo.capacity();
	std::cout << "making foo grow:" << std::endl;
	for (int i=0; i<100; ++i) {
		foo.push_back(i);
		if (sz!=foo.capacity()) {
			sz = foo.capacity();
			std::cout << "capacity changed: " << sz << std::endl;
		}
	}

	NS::vector<int> bar;
	sz = bar.capacity();
	bar.reserve(100);   // this is the only difference with foo above
	std::cout << "making bar grow:" << std::endl;
	for (int i=0; i<100; ++i) {
		bar.push_back(i);
		if (sz!=bar.capacity()) {
			sz = bar.capacity();
			std::cout << "capacity changed: " << sz << std::endl;
		}
	}
}

static void testAccess()
{
	{
		NS::vector<int> myvector;

		myvector.push_back(78);
		myvector.push_back(16);

		// now front equals 78, and back 16

		myvector.front() -= myvector.back();

		std::cout << "myvector.front() is now " << myvector.front() << std::endl;
	}
	{
		NS::vector<int> myvector;

		myvector.push_back(10);

		while (myvector.back() != 0)
		{
			myvector.push_back ( myvector.back() -1 );
		}
		printVectorSize(myvector);
	}
}

static void testSwap()
{
	NS::vector<int> foo (3,100);   // three ints with a value of 100
	NS::vector<int> bar (5,200);   // five ints with a value of 200

	foo.swap(bar);

	printVectorIterator(foo);
	printVectorIterator(bar);
}

static void testInserts()
{
	NS::vector<int> myvector (3,100);
	NS::vector<int>::iterator it;

	it = myvector.begin();
	it = myvector.insert ( it , 200 );

	myvector.insert (it,2,300);

	// "it" no longer valid, get a new one:
	it = myvector.begin();

	NS::vector<int> anothervector (2,400);
	myvector.insert (it+2,anothervector.begin(),anothervector.end());

	int myarray [] = { 501,502,503 };
	myvector.insert (myvector.begin(), myarray, myarray+3);
	printVectorIterator(myvector);
}

static void testErases()
{
	NS::vector<int> myvector;

	// set some values (from 1 to 10)
	for (int i=1; i<=10; i++)
		myvector.push_back(i);

	// erase the 6th element
	myvector.erase (myvector.begin()+5);

	// erase the first 3 elements:
	myvector.erase (myvector.begin(),myvector.begin()+3);

	printVectorIterator(myvector);
}

static void testAssign()
{
	NS::vector<int> first;
	NS::vector<int> second;
	NS::vector<int> third;

	first.assign (7,100);             // 7 ints with a value of 100

	NS::vector<int>::iterator it;
	it=first.begin()+1;

	second.assign (it,first.end()-1); // the 5 central values of first

	int myints[] = {1776,7,4};
	third.assign (myints,myints+3);   // assigning from array.

	std::cout << "Size of first: " << int (first.size()) << std::endl;
	std::cout << "Size of second: " << int (second.size()) << std::endl;
	std::cout << "Size of third: " << int (third.size()) << std::endl;
}

static void testClear()
{
	NS::vector<int> myvector;
	myvector.push_back (100);
	myvector.push_back (200);
	myvector.push_back (300);

	printVectorIterator(myvector);

	myvector.clear();
	myvector.push_back (1101);
	myvector.push_back (2202);

	printVectorIterator(myvector);
}

static void testComparisons()
{
	NS::vector<int> foo (3,100);   // three ints with a value of 100
	NS::vector<int> bar (2,200);   // two ints with a value of 200

	if (foo==bar) std::cout << "foo and bar are equal" << std::endl;
	if (foo!=bar) std::cout << "foo and bar are not equal" << std::endl;
	if (foo< bar) std::cout << "foo is less than bar" << std::endl;
	if (foo> bar) std::cout << "foo is greater than bar" << std::endl;
	if (foo<=bar) std::cout << "foo is less than or equal to bar" << std::endl;
	if (foo>=bar) std::cout << "foo is greater than or equal to bar" << std::endl;
}

template<typename T>
void	putvec( std::string title, T c)
{
	size_t	pos = 0;

	std::cout << title << std::endl; 
	for (typename T::iterator i = c.begin(); i != c.end(); ++i)
	{
		std::cout << "[" << pos << "]" << " " << *i << std::endl;
		// std::cout << "addr:" << &(*i)<<std::endl;
		++pos;
	}
}

static void testNico()
{
	NS::vector<int>	simple;
	LOG("#SIMPLE(capacity member functions)#");
	LOG2("\tvector->size()", simple.size());
	LOG2("\tvector->empty()", simple.empty());
	if (!DIFF)
		LOG2("\tvector->max_size()", simple.max_size());
	LOG2("\tvector->capacity()", simple.capacity());
	LOG2("\tvector->reserve(0)", "done..");
	simple.reserve(0);
	LOG2("\tvector->capacity()", simple.capacity());
	LOG2("\tvector->size()", simple.size());
	try
	{
		LOG("\t[expected exception]");
		LOG2("\t\tvector->reserve(-1)", "done..");
		simple.reserve(-1);
	}
	catch (std::exception &e)
	{
		std::cout << "\t\t" <<  e.what() << std::endl;
	}
	LOG2("\tvector->capacity()", simple.capacity());
	LOG2("\tvector->size()", simple.size());
	LOG2("\tvector->reserve(4)", "done..");
	simple.reserve(4);
	LOG2("\tvector->capacity()", simple.capacity());
	LOG2("\tvector->size()", simple.size());
	LOG2("\tvector->resize(5)","done..");
	simple.resize(0);
	LOG2("\tvector->size()", simple.size());
	LOG2("\tvector->resize(5)","done..");
	simple.resize(5);
	LOG2("\tvector->size()", simple.size());
	putvec("simple vector", simple);
	LOG("-------------------------------------------------------------------");

	LOG("#TRICKIER (iterators, constructors, copy, assignment, swap, clear  and relational operators)");
	LOG("\tparametric constructor..");
	NS::vector<int> foo (3,100);   // three ints with a value of 100
	NS::vector<int> bar (2,200);   // two ints with a value of 200
	LOG("\t\t0K..");

	LOG("\trange constructor..");
	std::list<std::string>	l;
	for( size_t i = 0; i < 9 ; i++)
	{
		l.push_back(std::string(i + 1,i + 'a'));
	}
	LOG("inputted content:");
	for (std::list<std::string>::iterator i = l.begin(); i != l.end(); i++)
	{
		std::cout << "-" << *i << std::endl;
	}
	NS::vector<std::string> iv(l.begin(), l.end());
	putvec("corresponding vector", iv);
	for(NS::vector<std::string>::reverse_iterator it = iv.rbegin(); it != iv.rend(); ++it)
	{
		LOG2("rev", *it);
	}
	NS::vector<std::string> ivcopy(iv);
	LOG("\tcopy constructor..");
	putvec("copied vector", ivcopy);
	LOG("\trelational operators:");
	putvec("foo", foo);
	putvec("bar", bar);
 	if (foo==bar) std::cout << "\tfoo and bar are equal\n";
 	if (foo!=bar) std::cout << "\tfoo and bar are not equal\n";
	if (foo< bar) std::cout << "\tfoo is less than bar\n";
 	if (foo> bar) std::cout << "\tfoo is greater than bar\n";
  	if (foo<=bar) std::cout << "\tfoo is less than or equal to bar\n";
  	if (foo>=bar) std::cout << "\tfoo is greater than or equal to bar\n";
	LOG("\tassignment and swap");
	NS::vector<int> assigned(4, 999);
	putvec("pre-assigned v", assigned);
	assigned = foo;
	putvec("post-assigned v", assigned);
	foo.swap(bar);
	putvec("swapped foo bar", foo);
	putvec("swapped bar foo", bar);
	foo.clear();
	bar.clear();
	putvec("'clear()'ed foo", foo);
	putvec("'clear()'ed bar", bar);
	LOG2("vector.at(2)", iv.at(2));
	try
	{
		LOG("\t[expected exception]");
		iv.at(-1);	
		simple.reserve(-1);
	}
	catch (std::exception &e)
	{
		std::cout << "\t\t" <<  e.what() << std::endl;
	}

	LOG2("vector.front()", iv.front());
	LOG2("vector.back()", iv.back());
	LOG2("vector[4]", iv[4]);
	LOG2("vector[-1]", iv[-1]);
	LOG("-------------------------------------------------------------------");
	LOG("#TRICKIEST !!111 (hard modifiers, dire time complexity, inserting and erasing)");
	
	NS::vector<int>vct_two(4);
	NS::vector<int>vct_four;
	
	for (unsigned long int i = 0; i < vct_two.size(); ++i)
		vct_two[i] = (vct_two.size() - i) * 5;

	vct_two.assign(2, 42);
	vct_four.assign(4,21);
	
	std::list<std::string>	abc;
	for( size_t i = 0; i < 1e5; i++)
	{
		abc.push_back(std::string((i % 3) + 1,((i + 1) % 26) + 'a'));
	}
	NS::vector<std::string>	u;
	LOG("\tdire push_back 🙀");
	for(std::list<std::string>::iterator i = abc.begin(); i != abc.end(); ++i)
	{
		u.push_back(*i);
	}
	putvec("tricky vector's content 🙀", u);
	LOG("dire single insert 🙀");
	u.insert(u.end(), "D I R E D I R E D I R E");
	LOG("dire fill insert 🙀");
	u.insert(u.end(), 3 ,"👽D I R E D I R E D I R E👽");
	LOG("dire range insert 🙀");
	u.insert(u.end(), abc.begin(), ++(++(++(abc.begin())))); //		
	putvec("deadly vector's content 🙀", u);
	LOG("dire single erase 🙀");
	u.erase(u.end() - 4);
	putvec("tricky single erase ☠️", u);

	LOG("dire range  erase 🙀");
	// u.erase(u.begin() + 5, u.begin() + 10);//		

	putvec("tricky erase ☠️", u);
	LOG("range vector.assign()");
	u.assign(abc.begin(), ++(++(++(abc.begin()))));//		
	putvec("", u);
	LOG("fill vector.assign()");
	u.assign(10, "ITS OVER!");
	putvec("", u);
	LOG(".-------------------------------------------------------------------.");
	LOG(".-------------------------------------------------------------------.");
	LOG(".-------------------------------------------------------------------.");
}

//	public

void testVector()
{
	performTest("Vector's string push & pop", &testStringPushPop);
	performTest("Vector's Fixed push & pop", &testFixedPushPop);
	performTest("Vector's string insert", &testStringInsert);
	performTest("Vector's int insert", &testInsert);
	performTest("Vector's Fixed erase", &testFixedErase);
	performTest("Vector's constructor", &testConstructor);
	performTest("Vector's assignment", &testAssignment);
	performTest("Vector's assign", &testAssign);
	performTest("Vector's iterators", &testIterators);
	performTest("Vector's capacity", &testCapacity);
	performTest("Vector's resize & at", &testResizeAt);
	performTest("Vector's empty", &testEmpty);
	performTest("Vector's reserve", &testReserve);
	performTest("Vector's access", &testAccess);
	performTest("Vector's inserts", &testInserts);
	performTest("Vector's erases", &testErases);
	performTest("Vector's comparisons", &testComparisons);
	performTest("Vector's swap", &testSwap);
	performTest("Vector's clear", &testClear);
	performTest("Vector's Nico", &testNico);
}
