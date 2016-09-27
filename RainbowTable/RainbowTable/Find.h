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

	int rows = 100000;
	int chainLength = 240;
	unsigned long totalSHA = 0;
	unsigned int readDigests[5000][5] = { 0 };
	unsigned char wordsFromFile[300000][3] = { 0 };
	unsigned int digestsFromFile[300000][5] = { 0 };
	unsigned int d[5] = { 0 };
	unsigned char currentAnswer[3] = { 0 };
	
	//-----------    Hash     ----------------------------//
	int hash(unsigned char word[], unsigned int digest[]);

	//-----------    Reduce  -----------------------------//
	//   word:			output word
	//   digest:		input digest
	//   iterator:		the index of the reduce function 
	//---------------------------------------------------//
	int reduceOneFirst(unsigned char word[], unsigned int digest[], int iterator);
	int reduceTwoFirst(unsigned char word[], unsigned int digest[], int iterator);
	int reduceThreeFirst(unsigned char word[], unsigned int digest[], int iterator);
	int reduceOneSecond(unsigned char word[], unsigned int digest[], int iterator);
	int reduceTwoSecond(unsigned char word[], unsigned int digest[], int iterator);
	int reduceThreeSecond(unsigned char word[], unsigned int digest[], int iterator);
	int reduceOneThird(unsigned char word[], unsigned int digest[], int iterator);
	int reduceTwoThird(unsigned char word[], unsigned int digest[], int iterator);
	int reduceThreeThird(unsigned char word[], unsigned int digest[], int iterator);

	int reductionFunctionSorting(int reductionType, int tableNum, unsigned char word[][3], unsigned int digest[][5], int j);


	//-------------------  Read in the Table ------------------//
	//  Store the result in wordsFromFile and digestsFromFile  //
	int readT();
	void readFile(FILE * fileToRead, int tableNumber);

	//------------------------------------------------------------------------------------
	//      Given a digest,  search for the pre-image   answer_m[3].
	//------------------------------------------------------------------------------------
	//int search(unsigned int target_d[5], unsigned char answer_m[3]);
	int search();

	//-----------   reading the next digest from the standard input  ----------------//
	void readNextD(unsigned int d[], int i);

	void readInput();
};