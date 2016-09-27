/*----------------------------------
This program build the rainbow table  for the other program Find.cpp.
------------------------------------*/

#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#include "Build.h"

using namespace std;
SHA1 sha;

Build::Build() {}
//Build::~Build() {}

//----  return the next word to be considered 
unsigned char* Build::nextWord(unsigned char m[3])
{
	m[0] = (unsigned char)(rand() % 256);
	m[1] = (unsigned char)(rand() % 256);
	m[2] = (unsigned char)(rand() % 256);

	return m;
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

	srand(time(NULL));

	for (long i1 = 0; i1 < 100000; i1++)
	{
		unsigned char randomM[3] = { (unsigned char)(rand() % 256), (unsigned char)(rand() % 256), (unsigned char)(rand() % 256) };
		memcpy(m, randomM, 3);

		M[i1][0] = m[0];
		M[i1][1] = m[1];
		M[i1][2] = m[2];

		// build the chain
		for (int k1 = 0; k1 < 240; k1++) {

			if (k1 % 3 == 0) {
				sha.Reset(); sha.Input(m[0]); sha.Input(m[1]); sha.Input(m[2]);
				sha.Result(d);

				m[0] = (unsigned char)((d[0] + k1) % 256); //8 bits
				m[1] = (unsigned char)((d[1] + k1) % 256);   //8 bits 
				m[2] = (unsigned char)((d[2] + k1) % 256);   //8 bits
			}
			else if (k1 % 3 == 1) {
				sha.Reset(); sha.Input(m[0]); sha.Input(m[1]); sha.Input(m[2]);
				sha.Result(d);

				m[0] = (unsigned char)((d[1] - k1) % 256); //8 bits
				m[1] = (unsigned char)((d[2] - k1) % 256);   //8 bits 
				m[2] = (unsigned char)((d[3] - k1) % 256);   //8 bits

			}
			else {
				sha.Reset(); sha.Input(m[0]); sha.Input(m[1]); sha.Input(m[2]);
				sha.Result(d);

				m[0] = (unsigned char)((d[2] + k1) % 256); //8 bits
				m[1] = (unsigned char)((d[3] + k1) % 256);   //8 bits 
				m[2] = (unsigned char)((d[4] + k1) % 256);   //8 bits
			}
		}

		// check whether to keep the chain
		G = HashTable.find(d[0]);

		if (G == HashTable.end()) {
			HashTable[d[0]] = 1;
			D[i1][0] = d[0];
			D[i1][1] = d[1];
			D[i1][2] = d[2];
			D[i1][3] = d[3];
			D[i1][4] = d[4];
		}
		else {
			i1--;
		}
	}

	//---    Write to the output file
	FILE *tableOne = fopen("firstTable", "wb");

	for (long j1 = 0; j1 < 100000; j1++)
	{
		fwrite(&(M[j1][0]), sizeof(unsigned char), 1, tableOne);
		fwrite(&(M[j1][1]), sizeof(unsigned char), 1, tableOne);
		fwrite(&(M[j1][2]), sizeof(unsigned char), 1, tableOne);

		fwrite(&(D[j1][0]), sizeof(unsigned int), 1, tableOne);
	}
	fclose(tableOne);


	// ------------ Table 2 ------------
/*
	for (long i2 = 0; i2 < 100000; i2++)
	{
		unsigned char randomM[3] = { (unsigned char)(rand() % 256), (unsigned char)(rand() % 256), (unsigned char)(rand() % 256) };
		memcpy(m, randomM, 3);

		M[i2][0] = m[0];
		M[i2][1] = m[1];
		M[i2][2] = m[2];

		// build the chain
		for (int k2 = 0; k2 < 80; k2++) {

			SHA1 sha;
			sha.Reset(); sha.Input(m[0]); sha.Input(m[1]); sha.Input(m[2]);
			sha.Result(d);

			m[0] = (unsigned char)((d[2] + k2) % 256); //8 bits
			m[1] = (unsigned char)((d[0]) % 256);   //8 bits 
			m[2] = (unsigned char)((d[4]) % 256);   //8 bits

			sha.Reset(); sha.Input(m[0]); sha.Input(m[1]); sha.Input(m[2]);
			sha.Result(d);

			m[0] = (unsigned char)((d[4]) % 256); //8 bits
			m[1] = (unsigned char)((d[1] + k2) % 256);   //8 bits 
			m[2] = (unsigned char)((d[0]) % 256);   //8 bits

			sha.Reset(); sha.Input(m[0]); sha.Input(m[1]); sha.Input(m[2]);
			sha.Result(d);

			m[0] = (unsigned char)((d[3]) % 256); //8 bits
			m[1] = (unsigned char)((d[2]) % 256);   //8 bits 
			m[2] = (unsigned char)((d[0] + k2) % 256);   //8 bits

			cout << "i2 : " << i2 << "k2 : " << k2 << endl;
		}

		// check whether to keep the chain
		G = HashTable.find(d[0]);

		if (G == HashTable.end()) {
			HashTable.insert(std::pair<unsigned long, unsigned int>(D[i2][0], i2 + 100000));
			D[i2][0] = d[0];
			D[i2][1] = d[1];
			D[i2][2] = d[2];
			D[i2][3] = d[3];
			D[i2][4] = d[4];
		}
		else {
			i2--;
		}

	}

	//---    Write to the output file
	FILE *tableTwo = fopen("secondTable", "wb");

	for (long j2 = 0; j2 < 100000; j2++)
	{
		fwrite(&(M[j2][0]), sizeof(unsigned char), 1, tableTwo);
		fwrite(&(M[j2][1]), sizeof(unsigned char), 1, tableTwo);
		fwrite(&(M[j2][2]), sizeof(unsigned char), 1, tableTwo);

		fwrite(&(D[j2][0]), sizeof(unsigned int), 1, tableTwo);

	}
	fclose(tableTwo);




	// ------------- Table 3 -----------------

	for (long i3 = 0; i3 < 100000; i3++)
	{
		unsigned char randomM[3] = { (unsigned char)(rand() % 256), (unsigned char)(rand() % 256), (unsigned char)(rand() % 256) };
		memcpy(m, randomM, 3);

		M[i3][0] = m[0];
		M[i3][1] = m[1];
		M[i3][2] = m[2];

		// build the chain
		for (int k3 = 0; k3 < 80; k3++) {

			SHA1 sha;
			sha.Reset(); sha.Input(m[0]); sha.Input(m[1]); sha.Input(m[2]);
			sha.Result(d);

			m[0] = (unsigned char)((d[2] - k3) % 256); //8 bits
			m[1] = (unsigned char)((d[4]) % 256);   //8 bits 
			m[2] = (unsigned char)((d[1]) % 256);   //8 bits

			sha.Reset(); sha.Input(m[0]); sha.Input(m[1]); sha.Input(m[2]);
			sha.Result(d);

			m[0] = (unsigned char)((d[1]) % 256); //8 bits
			m[1] = (unsigned char)((d[0] - k3) % 256);   //8 bits 
			m[2] = (unsigned char)((d[4]) % 256);   //8 bits

			sha.Reset(); sha.Input(m[0]); sha.Input(m[1]); sha.Input(m[2]);
			sha.Result(d);

			m[0] = (unsigned char)((d[0]) % 256); //8 bits
			m[1] = (unsigned char)((d[2]) % 256);   //8 bits 
			m[2] = (unsigned char)((d[3] - k3) % 256);   //8 bits

			cout << "i3 : " << i3 << "k3 : " << k3 << endl;

		}

		// check whether to keep the chain
		G = HashTable.find(d[0]);

		if (G == HashTable.end()) {
			HashTable.insert(std::pair<unsigned long, unsigned int>(D[i3][0], i3 + 200000));
			D[i3][0] = d[0];
			D[i3][1] = d[1];
			D[i3][2] = d[2];
			D[i3][3] = d[3];
			D[i3][4] = d[4];
		}
		else {
			i3--;
		}

	}

	//---    Write to the output file
	FILE *tableThree = fopen("thirdTable", "wb");

	for (long j3 = 0; j3 < 100000; j3++)
	{
		fwrite(&(M[j3][0]), sizeof(unsigned char), 1, tableThree);
		fwrite(&(M[j3][1]), sizeof(unsigned char), 1, tableThree);
		fwrite(&(M[j3][2]), sizeof(unsigned char), 1, tableThree);

		fwrite(&(D[j3][0]), sizeof(unsigned int), 1, tableThree);

	}
	fclose(tableThree);
	*/

	return (0);
}

/*int main(int argc, char*argv[])
{
	Build* build = new Build();
	SHA1 sha;

	//----  Setting the parameters

	//----   Build the table.
	build->buildT();
}*/