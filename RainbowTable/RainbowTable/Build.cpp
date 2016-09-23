/*----------------------------------
This program build the rainbow table  for the other program Find.cpp.
------------------------------------*/

#define _CRT_SECURE_NO_DEPRECATE
#include "Build.h"

using namespace std;

Build::Build() {}
//Build::~Build() {}

//----  return the next word to be considered 
void Build::next_word(unsigned char m[3])
{
	int seed = 5000;
	Generate* generate = new Generate();
	generate->getrandom(m, seed);
}

//-------   Hash 
int Build::Hash(unsigned char m[3], unsigned int d[5])
{
	SHA1 sha;
	sha.Reset(); sha.Input(m[0]); sha.Input(m[1]); sha.Input(m[2]);
	sha.Result(d);
	return(0);
}

//-------  Reduce
int Build::Reduce(unsigned int d[5], unsigned char m[3], int i)
{
	m[0] = (unsigned char)((d[0] + i) % 256); //8 bits
	m[1] = (unsigned char)((d[1]) % 256);   //8 bits 
	m[2] = (unsigned char)((d[2]) % 256);   //8 bits

	return(0);
}

//------- Check hash table
bool Build::checkHashTable(unsigned int d[5], long i) {
	for (long j = 0; j < HashTable.size(); j++) {
		if ((*d == (HashTable[j])) && (i != j)) {
			return false;
		}
	}
	return true;
}

int Build::buildT()
{
	unsigned int  d[5];
	unsigned char m[3];


	for (long i = 0; i < 1000; i++)
	{
		next_word(m);
		
		// build the chain
		for (int k = 100 * i; k < (100 * i + 100); k++) {
			M[k][0] = m[0];
			M[k][1] = m[1];
			M[k][2] = m[2];
			Hash(m, d);
			D[k][0] = d[0];
			D[k][1] = d[1];
			D[k][2] = d[2];
			D[k][3] = d[3];
			D[k][4] = d[4];
			Reduce(d, m, k);
		}

		// check whether to keep the chain. 
		if (checkHashTable(d, i)) {
			HashTable[i] = (*d);
		}
		
		// You may want to drop the chain, for e.g. if the digest is already in the table.
		// This form the main component of your program.
	}

	//---    Write to the output file
	//note that to reduce the size of the table, it is not neccessary to write the full digest.

	FILE * hashFile;
	hashFile = fopen("Hashes.txt", "w");
	for (long j = 0; j < 99999; j++)
	{
	//	fwrite(&(M[i][0]), sizeof(unsigned char), 1, stdout);
	//	fwrite(&(M[i][1]), sizeof(unsigned char), 1, stdout);
	//	fwrite(&(M[i][2]), sizeof(unsigned char), 1, stdout);

		fwrite(&(D[0][0]), sizeof(unsigned int), 1, hashFile);
		fwrite(&(D[1][1]), sizeof(unsigned int), 1, hashFile);
		fwrite(&(D[2][2]), sizeof(unsigned int), 1, hashFile);
		fwrite(&(D[3][3]), sizeof(unsigned int), 1, hashFile);
		fwrite(&(D[4][4]), sizeof(unsigned int), 1, hashFile);

	}

	
	


	return(0);
}

int main(int argc, char*argv[])
{
	Build* build = new Build();
	SHA1 sha;

	//----  Setting the parameters

	//----   Build the table.
	build->buildT();
}

