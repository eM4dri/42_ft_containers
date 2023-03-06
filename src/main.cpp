/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:49:56 by emadriga          #+#    #+#             */
/*   Updated: 2023/03/06 18:15:41 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test/testVector.hpp"
#include "test/testStack.hpp"
#include "test/testUtility.hpp"
#include "test/testMap.hpp"
#include "test/testSet.hpp"
#include "test/testTree.hpp"
#include <stdio.h>					//	printf with flags
#include <string.h>					//	strcmp
#include <stdlib.h>					//	system

enum logLevel
	{ LEAKS = 0x1, VECTOR = 0x2, STACK = 0x4, MAP = 0x8, SET = 0x10, UTILITY = 0x20, TREE = 0x40};
static const char *logLevel[] =
	{ "leaks", "vector", "stack", "map", "set", "utility", "tree"};
#ifndef LOGTREE
# define COUNT_LEVELS 6
# define ALL_LEVELS_MASK 0x3E
# define ALL_LEVELS_LEAKS_MASK 0x3F
#else
# define COUNT_LEVELS 7
# define ALL_LEVELS_MASK 0x7E
# define ALL_LEVELS_LEAKS_MASK 0x7F
#endif

void ft_exit(void)
{
	system("leaks containers");
}

int evalArgs(int argc, char **argv)
{
	int out;
	int bit;

	out = 0;
	if (argc == 1)
		return (ALL_LEVELS_MASK);
	if (argc == 2 && !strcmp( argv[1], *logLevel))
		return (ALL_LEVELS_LEAKS_MASK);
	while (--argc)
	{
		bit = 0;
		while (bit < COUNT_LEVELS)
		{
			if (!(out & (1<<bit)) && !strcmp( argv[argc], logLevel[bit]))
				out |= (1<<bit);
			bit++;
		}
	}
	return (out);
}

int main(int argc, char **argv)
{
	const int tests = evalArgs(argc, argv);
	int bit;

	printf("TestMask\t%x\nTest to perform:\n", tests);
	bit = 0;
	while (bit < COUNT_LEVELS)
	{
		if (tests & (1<<bit))
			printf("\t· %s\n", logLevel[bit]);
		bit++;
	}
	std::cout << "\t-------------\t" << std::endl;
	if (tests & LEAKS)
		atexit(ft_exit);
	if (tests & VECTOR)
		testVector();
	if (tests & STACK)
		testStack();
	if (tests & MAP)
		testMap();
	if (tests & SET)
		testSet();
	if (tests & UTILITY)
		testUtility();
	if (tests & TREE)
		testTree();

	return 0;
}
//valgrind --leak-check=yes ../workplace/42_ft_containers/./containers  > ../workplace/42_ft_containers/containers_log
