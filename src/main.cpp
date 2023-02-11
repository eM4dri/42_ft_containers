/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:49:56 by emadriga          #+#    #+#             */
/*   Updated: 2023/02/11 10:03:45 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
// #include "vector.hpp"
// #include "Fixed.hpp"
#include "test/testVector.hpp"
#include "test/testStack.hpp"
#include "test/testCompare.hpp"
#include "test/testMap.hpp"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// #include "red_black_tree.hpp"
// #include "node.hpp"
// #include <vector>
// #include <cctype>

// #define DEFAULT_NAME "Anonimous"

// #define NS ft
enum logLevel { LEAKS = 0x1, VECTOR = 0x2, STACK = 0x4, MAP = 0x8, FIXED = 0x10, INSERT = 0x20, COMPARE = 0x40, ERASE = 0x80  };
static const char *logLevel[] =
	{ "leaks", "vector", "stack", "map", "fixed", "insert", "compare", "erase" };
#define COUNT_LEVELS 7
#define ALL_LEVELS_MASK 0x7E
#define ALL_LEVELS_LEAKS_MASK 0x7F

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
		testVectorStringPushPop();
	if (tests & VECTOR || tests & FIXED)
		testVectorFixedPushPop();
	if (tests & VECTOR || tests & INSERT)
		testVectorStringInsert();
	if (tests & VECTOR || tests & INSERT)
		testVectorIntInsert();
	if (tests & VECTOR || tests & ERASE)
		testVectorFixedErase();
	if (tests & COMPARE)
		testLexicographicalCompare();
	if (tests & STACK)
		testStackStringPushPop();
	if (tests & MAP)
	{
		testMapIntInsertDelete();
		testMapStringInsertDelete();
		testMapStringInsertDelete2();
		testMapFixedInsertDelete();
	}
	return 0;
}
