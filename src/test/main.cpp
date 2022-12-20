/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 17:49:56 by emadriga          #+#    #+#             */
/*   Updated: 2022/12/20 20:44:19 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
// #include "vector.hpp"
// #include "Fixed.hpp"
#include "testVector.hpp"
#include "testCompare.hpp"
#include "testMap.hpp"
#include <stdio.h>
// #include "red_black_tree.hpp"
// #include "node.hpp"
// #include <vector>
// #include <cctype>
// #include <string.h>
// #include <stdlib.h>

// #define DEFAULT_NAME "Anonimous"

// #define NS ft
// 0001
// 0010
// 0100
// 1000 
// 0001 0000
// 0010 0000
// 0100 0000
// 1000 1000

// 1000 1000 1000 1000 1000

// 0011
// 1111
enum logLevel { VECTOR = 0x1, MAP = 0x2, FIXED = 0x4, INSERT = 0x8, COMPARE = 0x10, LEAKS = 0x20 };
static const char *logLevel[] =
	{ "vector", "map", "fixed", "insert", "compare", "leaks" };
#define COUNT_LEVELS 6
#define ALL_LEVELS_MASK 0xFF
#define ALL_LEVELS_LEAKS_MASK 0x3F

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
	if (argc == 2 && !strcmp( argv[1], logLevel[COUNT_LEVELS - 1]))
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
	if (argc != 1 && tests & LEAKS)
		atexit(ft_exit);
	if (tests & VECTOR)
		testVectorStringPushPop();
	if (tests & VECTOR || tests & FIXED)
		testVectorFixedPushPop();
	if (tests & VECTOR || tests & INSERT)
		testVectorStringInsert();
	if (tests & VECTOR || tests & INSERT)
		testVectorIntInsert();
	if (tests & COMPARE)
		testLexicographicalCompare();
	if (tests & MAP)
	{
		testMapIntInsertDelete();
		testMapStringInsertDelete();
		testMapStringInsertDelete2();
	}
	return 0;
}
