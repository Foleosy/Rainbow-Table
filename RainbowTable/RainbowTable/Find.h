#pragma once

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <iomanip>
#include "sha1.h"

class Find
{
public:
	Find();
	//~Find();
	
	//-----------    Hash     ----------------------------//
	int Hash(unsigned char m[3], unsigned int d[5]);

	//-----------    Reduce  -----------------------------//
	//   d:   input digest
	//   m:   output word
	//   i:   the index of the reduce function 
	//---------------------------------------------------//
	int Reduce(unsigned int d[5], unsigned char m[3], int i);

	//------------  Read in the Table ------------------//
	//   Store the result in M and D                    //
	int ReadT();

	//------------------------------------------------------------------------------------
	//      Given a digest,  search for the pre-image   answer_m[3].
	//------------------------------------------------------------------------------------
	int search(unsigned int target_d[5], unsigned char answer_m[3]);

	//-----------   reading the next digest from the standard input  ----------------//
	void readnextd(unsigned int d[5], int i);

	void readInput(unsigned int readDigests[5000][5]);


	std::unordered_map <unsigned int, unsigned int> HashTable;
	std::unordered_map <unsigned int, unsigned int>::const_iterator G;	//-------   Data Structure for searching    -----------//

};

