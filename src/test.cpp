/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:49:56 by emadriga          #+#    #+#             */
/*   Updated: 2022/09/19 17:00:03 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "vector.hpp"
#include "Fixed.hpp"
#include "red_black_tree.hpp"
#include "node.hpp"
#include <vector>
#include <string>
#include <cctype>

#define DEFAULT_NAME "Anonimous"

#define NS ft

enum logLevel { VECTOR, MAP, FIXED, INSERT, LEXICOGRAPHICAL_COMPARE };
static const char *logLevel[] =
	{ "vector", "map", "fixed", "insert", "compare" };

void ft_exit(void)
{
	system("leaks containers");
}

template<typename T >
void printVectorSize(NS::vector<T> & vector){
	std::cout << "Print vector using [] & size" << std::endl;
	std::cout << "Vector size "<< vector.size() << std::endl;
	for (size_t i = 0; i < vector.size(); i++)
	{
		std::cout << vector[i] << "\t\t" << &vector[i] << std::endl;
		//std::cout << vector[i] << std::endl;
	}
	std::cout << "\t-------------\t" << std::endl;
}

template<typename T >
void printVectorIterator(NS::vector<T> & vector){
	std::cout << "Print vector using iterator" << std::endl;
	for (typename NS::vector<T>::iterator it  = vector.begin();
	it != vector.end(); it++)
	{
		std::cout << *it << "\t\t" << &(*it) << std::endl;
		// std::cout << *it << std::endl;
	}
	std::cout << "\t-------------\t" << std::endl;
}

template<typename T >
void printVectorReverseIterator(NS::vector<T> & vector){
	std::cout << "Print vector using reverse iterator" << std::endl;
	for (typename NS::vector<T>::reverse_iterator it  = vector.rbegin();
	it != vector.rend(); it++)
	{
		std::cout << *it << "\t\t" << &(*it) << std::endl;
		// std::cout << *it << std::endl;
	}
	std::cout << "\t-------------\t" << std::endl;
}

bool mycomp (char c1, char c2)
{ return std::tolower(c1)<std::tolower(c2); }

int main(int argc, char **argv)
{
	if (0)
		atexit(ft_exit);

	if (argc == 1 || !strcmp( argv[1], logLevel[VECTOR] ) )
	{
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
	}


	if (argc == 1 || !strcmp(argv[1], logLevel[VECTOR]) || !strcmp(argv[1], logLevel[FIXED] ) )
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


	if (argc == 1 || !strcmp(argv[1], logLevel[VECTOR]) || !strcmp(argv[1], logLevel[INSERT] ) )
	{
		{
			NS::vector<std::string> vector;
			vector.push_back("1 ycarro");
			vector.push_back("2 jmatute");
			vector.push_back("3 jalvarad");
			vector.push_back("4 tomartin");
			vector.push_back("5 crisfern");
			vector.push_back("6 agallipo");
			printVectorIterator(vector);

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
			std::cout << *it2 << "\t\t" << &(*it2) << std::endl;
			printVectorSize(vector);
			printVectorIterator(vector);
			printVectorReverseIterator(vector);
		}
	}

	// if (argc == 1 || !strcmp(argv[1], logLevel[VECTOR]) || !strcmp(argv[1], logLevel[INSERT] ) )
	// {
	// 	{
	// 		NS::vector<int> myvector;
	// 		myvector.push_back(3);
	// 		myvector.push_back(100);
	// 		NS::vector<int>::iterator it = myvector.begin();

	// 		it = myvector.insert ( it , 200 );

	// 		myvector.insert (it,2,300);

	// 		// "it" no longer valid, get a new one:
	// 		it = myvector.begin();

	// 		NS::vector<int> anothervector;
	// 		myvector.push_back(2);
	// 		myvector.push_back(400);
	// 		it++;
	// 		it++;
	// 		myvector.insert (it, anothervector.begin(),anothervector.end());

	// 		int myarray [] = { 501,502,503 };
	// 		myvector.insert (myvector.begin(), myarray, myarray+3);

	// 		std::cout << "myvector contains:";
	// 		for (it=myvector.begin(); it != myvector.end(); it++)
	// 			std::cout << ' ' << *it;
	// 		std::cout << '\n';
	// 	}
	// }

	if (argc == 1 || !strcmp(argv[1], logLevel[LEXICOGRAPHICAL_COMPARE]))
	{
		{
			char foo[]="Apple";
			char bar[]="apartment";
			std::cout << std::boolalpha;
			std::cout << "Comparing foo and bar lexicographically (foo<bar):\n";
			std::cout << "Using default comparison (operator<): ";
			std::cout << NS::lexicographical_compare(foo,foo+5,bar,bar+9);
			std::cout << '\n';
			std::cout << "Using mycomp as comparison object: ";
			std::cout << NS::lexicographical_compare(foo,foo+5,bar,bar+9,mycomp);
			std::cout << '\n';
		}
	}

	if (argc == 1 || !strcmp(argv[1], logLevel[MAP]))
	{
		{
			ft::red_black_tree<int> tree;

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
			tree.printLevelOrder();

			std::cout << std::endl << "Deleting 18, 11, 3, 10, 22" << std::endl;

			tree.deleteByVal(18);
			tree.deleteByVal(11);
			tree.deleteByVal(3);
			tree.deleteByVal(10);
			tree.deleteByVal(22);

			tree.printInOrder();
			tree.printLevelOrder();
		}
		{
			ft::red_black_tree<std::string> tree;

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
			tree.printLevelOrder();

			std::cout << std::endl << "Deleting 18, 11, 3, 10, 22" << std::endl;

			tree.deleteByVal("18");
			tree.deleteByVal("11");
			tree.deleteByVal("3");
			tree.deleteByVal("10");
			tree.deleteByVal("22");

			tree.printInOrder();
			tree.printLevelOrder();
		}
	}
	return 0;
}
