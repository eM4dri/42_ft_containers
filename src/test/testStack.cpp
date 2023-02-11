/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testStack.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:49:56 by emadriga          #+#    #+#             */
/*   Updated: 2023/02/11 10:01:45 by emadriga         ###   ########.fr       */
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


//	public
	void testStackStringPushPop()
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



