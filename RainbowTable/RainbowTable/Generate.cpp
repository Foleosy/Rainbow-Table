/*--------
This program generates random digests

to compile:
g++ Generate.cpp sha1.cpp -o Generate

to run
./Generate 0 5000

------------*/

#include "Generate.h"

Generate::Generate() {}

Generate::~Generate() {}

using namespace std;
//-----   H A S H      ------------------------------------------------
//   getrandom (m) :     generate a random word. 
//---------------------------------------------------------------------
int Generate::getrandom(unsigned char  m[3], int seed)
{
	srand(seed);
	m[0] = (unsigned char)(rand() % 256);
	m[1] = (unsigned char)(rand() % 256);
	m[2] = (unsigned char)(rand() % 256);

	return(0);
}

//-----   H A S H      ------------------------------------------------
//   Hash (m, d) :      compute the hash of m. The digest is stored in d.
//---------------------------------------------------------------------
int Generate::Hash(unsigned char m[3], unsigned int d[5])
{
	SHA1 sha;

	sha.Reset(); sha.Input(m[0]); sha.Input(m[1]); sha.Input(m[2]);
	sha.Result(d);
	return(0);
}
/*
void initialiseGenerator(int a, int b)
{
	
	Generate generate;
	SHA1          sha;
	unsigned int  d[5];   // 32 x 5 = 160 bits  digest
	unsigned char m[3];   // 24-bit word

	int seed = a;
	int number = b;
	srand(seed);

	cout.setf(ios::hex, ios::basefield);    // format the output to be hex
	cout.setf(ios::uppercase);
	
	for (int i = 0; i < number; i++)
	{
		generate.getrandom(m); generate.Hash(m, d);
		cout << "  " << setw(8) << setfill('0') << d[0]          // setw(8) set the width to be 8.
			<< "  " << setw(8) << d[1]
			<< "  " << setw(8) << d[2]
			<< "  " << setw(8) << d[3]
			<< "  " << setw(8) << d[4] << endl;
	}
}*/


