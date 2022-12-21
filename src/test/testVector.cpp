/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testVector.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:49:56 by emadriga          #+#    #+#             */
/*   Updated: 2022/12/21 20:28:29 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test/testVector.hpp"

//	public
	template<typename T >
	static void printVectorSize(NS::vector<T> & vector){
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
	static void printVectorIterator(NS::vector<T> & vector){
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
	static void printVectorReverseIterator(NS::vector<T> & vector){
		std::cout << "Print vector using reverse iterator" << std::endl;
		for (typename NS::vector<T>::reverse_iterator it  = vector.rbegin();
		it != vector.rend(); it++)
		{
			std::cout << *it << "\t\t" << &(*it) << std::endl;
			// std::cout << *it << std::endl;
		}
		std::cout << "\t-------------\t" << std::endl;
	}

//	private
	void testVectorStringPushPop()
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

	void testVectorFixedPushPop()
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

	void testVectorStringInsert()
	{
		NS::vector<std::string> vector;
		vector.push_back("1 ycarro");
		vector.push_back("2 jmatute");
		vector.push_back("3 jalvarad");
		vector.push_back("4 tomartin");
		vector.push_back("5 crisfern");
		vector.push_back("6 agallipo");
		// printVectorIterator(vector);

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
		std::cout << *it2 << "\t\t" << &(*it2) << std::endl;
		printVectorSize(vector);
		// printVectorIterator(vector);
		// printVectorReverseIterator(vector);
	}

	void testVectorIntInsert()
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
		std::cout << '\n';
	}
