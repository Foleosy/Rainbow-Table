#pragma once

#include <iostream>
#include <fstream>
#include <unordered_map>
#include "sha1.h"
#include "Generate.h"

class Build
{
public:
	Build();

	unsigned char* nextWord(unsigned char m[3]);
	int Hash(unsigned char m[3], unsigned int d[5]);
	int Reduce(unsigned int d[5], unsigned char m[3], int i);
	bool checkHashTable(unsigned int d[5], long i);
	int buildT();

	//  A table to store all the words and digests. 
	//    infeasible to have such large table in practice.   
	//    for programming convenient, we store the whole table in memory. 
	unsigned char M[1048576][3];
	unsigned int  D[1048576][5];

	std::unordered_map <unsigned long, unsigned int> HashTable;
	std::unordered_map <unsigned long, unsigned int>::const_iterator G;

};

