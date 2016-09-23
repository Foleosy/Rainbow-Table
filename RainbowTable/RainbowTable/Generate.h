#pragma once

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "sha1.h"

class Generate
{
public:
	Generate();
	~Generate();

	unsigned int  d[5];   // 32 x 5 = 160 bits  digest
	unsigned char m[3];   // 24-bit word

	int getrandom(unsigned char m[3], int seed);
	int Hash(unsigned char m[3], unsigned int d[5]);
};