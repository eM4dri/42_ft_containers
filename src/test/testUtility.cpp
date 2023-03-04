/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testUtility.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:49:56 by emadriga          #+#    #+#             */
/*   Updated: 2023/03/04 11:56:07 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "test/testUtility.hpp"

//	private
static bool mycomp (char c1, char c2)
{ return std::tolower(c1)<std::tolower(c2); }

static void testLexicographicalCompare()
{
	char foo[]="Apple";
	char bar[]="apartment";
	std::cout << "Comparing foo and bar lexicographically (foo<bar):"<< std::endl;
	std::cout << "Using default comparison (operator<): ";
	std::cout << NS::lexicographical_compare(foo,foo+5,bar,bar+9);
	std::cout << std::endl;
	std::cout << "Using mycomp as comparison object: ";
	std::cout << NS::lexicographical_compare(foo,foo+5,bar,bar+9,mycomp) << std::endl;
	std::cout << "\t-------------\t" << std::endl;
}


// 1. the return type (bool) is only valid if T is an integral type:
template <typename T>
static typename ft::enable_if<ft::is_integral<T>::value,bool>::type is_odd (T i)
	{	return bool(i%2);	}

// 2. the second template argument is only valid if T is an integral type:
template <	typename T >
static bool is_even (	T i,
				typename ft::enable_if<ft::is_integral<T>::value,bool>::type* = NULL
				)
	{	return !bool(i%2);	}

static void testEnableIf()
{
	short int i = 1;    // code does not compile if type of i is not integral

	std::cout << std::boolalpha;
	std::cout << "i is odd: " << is_odd(i) << std::endl;
	std::cout << "i is even: " << is_even(i) << std::endl;
}

static void testIsIntegral()
{
	std::cout << std::boolalpha;
	std::cout << "is_integral:" << std::endl;
	std::cout << "\t- char: " << ft::is_integral<char>::value << std::endl;
	std::cout << "\t- int: " << ft::is_integral<int>::value << std::endl;
	std::cout << "\t- float: " << ft::is_integral<float>::value << std::endl;
}

static void testEqual()
{
	int myints[] = {20,40,60,80,100};               //   myints: 20 40 60 80 100
	NS::vector<int>myvector (myints,myints+5);     // myvector: 20 40 60 80 100

	// using default comparison:
	if ( NS::equal (myvector.begin(), myvector.end(), myints) )
		std::cout << "The contents of both sequences are equal." << std::endl;
	else
		std::cout << "The contents of both sequences differ." << std::endl;

	myvector[3]=81;                                 // myvector: 20 40 60 81 100

	// using predicate comparison:
	if ( NS::equal (myvector.begin(), myvector.end(), myints) )
		std::cout << "The contents of both sequences are equal." << std::endl;
	else
		std::cout << "The contents of both sequences differ." << std::endl;
}

static void testPairRelational()
{
	NS::pair<int,char> foo (10,'z');
	NS::pair<int,char> bar (90,'a');

	if (foo==bar)
		std::cout << "foo and bar are equal" << std::endl;
	if (foo!=bar)
		std::cout << "foo and bar are not equal" << std::endl;
	if (foo< bar)
		std::cout << "foo is less than bar" << std::endl;
	if (foo> bar)
		std::cout << "foo is greater than bar" << std::endl;
	if (foo<=bar)
		std::cout << "foo is less than or equal to bar" << std::endl;
	if (foo>=bar)
		std::cout << "foo is greater than or equal to bar" << std::endl;
}

static void testPairConstructor()
{
	NS::pair <std::string,double> product1;                     // default constructor
	NS::pair <std::string,double> product2 ("tomatoes",2.30);   // value init
	NS::pair <std::string,double> product3 (product2);          // copy constructor

	product1 = NS::make_pair(std::string("lightbulbs"),0.99);   // using make_pair (move)

	product2.first = "shoes";                  // the type of first is string
	product2.second = 39.90;                   // the type of second is double

	std::cout << "The price of " << product1.first << " is $" << product1.second << std::endl;
	std::cout << "The price of " << product2.first << " is $" << product2.second << std::endl;
	std::cout << "The price of " << product3.first << " is $" << product3.second << std::endl;
}

static void testPairMakePair()
{
	NS::pair <int,int> foo;
	NS::pair <int,int> bar;

	foo = NS::make_pair (10,20);
	bar = NS::make_pair (10.5,'A'); // ok: implicit conversion from pair<double,char>

	std::cout << "foo: " << foo.first << ", " << foo.second << std::endl;
	std::cout << "bar: " << bar.first << ", " << bar.second << std::endl;
}

static void testCopy()
{
	int myints[]={10,20,30,40,50,60,70};
	NS::vector<int> myvector (7);

	NS::copy ( myints, myints+7, myvector.begin() );

	std::cout << "myvector contains:";
	for (NS::vector<int>::iterator it = myvector.begin(); it!=myvector.end(); ++it)
		std::cout << ' ' << *it;

	std::cout << std::endl;
}

//	public

void testUtility()
{
	performTest("Utility's lexicographical_compare", &testLexicographicalCompare);
	performTest("Utility's enable_if", &testEnableIf);
	performTest("Utility's is_integral ", &testIsIntegral);
	performTest("Utility's equal ", &testEqual);
	performTest("Utility's pair constructor ", &testPairConstructor);
	performTest("Utility's pair relational ", &testPairRelational);
	performTest("Utility's pair make_pair ", &testPairMakePair);
	performTest("Utility's copy", &testCopy);
}
