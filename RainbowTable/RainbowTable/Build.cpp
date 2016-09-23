/*----------------------------------
This program build the rainbow table  for the other program Find.cpp.
------------------------------------*/

#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#include "Build.h"

using namespace std;

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

	for (long i = 0; i < 40000; i++)
	{
		unsigned char randomM[3] = { (unsigned char)(rand() % 256), (unsigned char)(rand() % 256), (unsigned char)(rand() % 256) };
		memcpy(m, randomM, 3);

		// build the chain
		for (int k = 25 * i; k < (25 * i + 25); k++) {
			M[k][0] = m[0];
			M[k][1] = m[1];
			M[k][2] = m[2];
			
			SHA1 sha;
			sha.Reset(); sha.Input(m[0]); sha.Input(m[1]); sha.Input(m[2]);
			sha.Result(d);

			D[k][0] = d[0];
			D[k][1] = d[1];
			D[k][2] = d[2];
			D[k][3] = d[3];
			D[k][4] = d[4];

			m[0] = (unsigned char)((d[0] + i) % 256); //8 bits
			m[1] = (unsigned char)((d[1]) % 256);   //8 bits 
			m[2] = (unsigned char)((d[2]) % 256);   //8 bits

			
		}

	}

	//---    Write to the output file
	ofstream hashFile("Hash.txt");
	
	cout.rdbuf(hashFile.rdbuf());
	cout.setf(ios::hex, ios::basefield);    // format the output to be hex
	cout.setf(ios::uppercase);
	
	for (long j = 0; j < 1999998; j += 25)
	{
	
		cout << setw(8) << setfill('0') << D[j][0]          // setw(8) set the width to be 8.
			<< "  " << setw(8) << D[j][4] << endl;

	}

	for (long j = 0; j < 1999998; j += 25)
	{

		cout << M[j][0] << " " << M[j][1] << " " << M[j][2] << endl;

	}
	hashFile.close();

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