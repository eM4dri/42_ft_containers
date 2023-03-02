/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testStack.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:49:56 by emadriga          #+#    #+#             */
/*   Updated: 2023/03/02 18:10:52 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test/testStack.hpp"

//	private
template<typename T >
static void printStackSize(NS::stack<T> & stack){
	size_t 	 size;
	
	size = stack.size();
	std::cout << "Stack size "<< size << std::endl;
	std::cout << "Print stack using top & pop" << std::endl;
	
	while (size --)
	{
		std::cout << stack.top() << std::endl;
		stack.pop();
	}
	std::cout << "\t-------------\t" << std::endl;
}

static void testStringPushPop()
{
	NS::stack<std::string> stack;
	stack.push("1 ycarro");
	stack.push("2 jmatute");
	stack.push("3 jalvarad");
	stack.push("4 tomartin");
	stack.push("5 crisfern");
	stack.push("6 agallipo");
	stack.pop();
	printStackSize(stack);
}

static void testFixedPushPop()
{
	NS::stack<Fixed> stack;
	stack.push(42.42f);
	stack.push(0);
	stack.push(5.2f);
	stack.push(0);
	stack.pop();
	printStackSize(stack);
}

static void testConstructor()
{
	std::vector<int> myvector (2,200);        // vector with 2 elements

	NS::stack<int> first;                    // empty stack

	NS::stack<int,std::vector<int> > second;  // empty stack using vector
	NS::stack<int,std::vector<int> > third (myvector);

	std::cout << "size of first: " << first.size() << std::endl;
	std::cout << "size of second: " << second.size() << std::endl;
	std::cout << "size of third: " << third.size() << std::endl;

}

static void testEmptySizeTop()
{
	NS::stack<int> mystack;
	int sum (0);

	for (int i=1;i<=10;i++) 
		mystack.push(i);

	std::cout << "1. size: " << mystack.size() << std::endl;
	
	while (!mystack.empty())
	{
		sum += mystack.top();
		mystack.pop();
	}

	std::cout << "total: " << sum << std::endl;
	std::cout << "2. size: " << mystack.size() << std::endl;
}

//	public

void testStack()
{	
	performTest("Stack's string push & pop", &testStringPushPop);
	performTest("Stack's constructor", &testConstructor);
	performTest("Stack's empty, size & top", &testEmptySizeTop);
	performTest("Stack's Fixed push & pop", &testFixedPushPop);
}
