/*--------
(1) Read in a Rainbow table (built using B.cpp)
(2) Read 1000 digests from standard input and  output the preimage.
------------*/

#define _CRT_SECURE_NO_DEPRECATE
#include "Find.h"

using namespace std;

unsigned long TOTAL_SHA = 0;       // Count the number of hashes performed.
unsigned int readDigests[5000][5];
unsigned char M[1000000][3];    // array to store the word read from the table (head of chain)
unsigned int  D[1000000][5];    // array to store the digest read from the table  (end of chain)


Find::Find() {}

int Find::Hash(unsigned char m[3], unsigned int d[5])
{
	SHA1 sha;
	sha.Reset(); sha.Input(m[0]); sha.Input(m[1]); sha.Input(m[2]);
	sha.Result(d);

	TOTAL_SHA = TOTAL_SHA + 1;
	return(0);
}

int Find::Reduce(unsigned int d[5], unsigned char m[3], int i)
{
	m[0] = (unsigned char)((d[0] + i) % 256);   //8 bits
	m[1] = (unsigned char)((d[1]) % 256);   //8 bits
	m[2] = (unsigned char)((d[2]) % 256);   //8 bits

	return(0);
}

int Find::ReadT()
{
	ifstream oldTable("Hash.txt");
	char nextChar;
	string line;
	string nextInputPart;
	string a, e;
	stringstream ss;
	for (int j = 0; j < 20000; j++)
	{
	//	getline(oldTable, line);
		oldTable >> a;
		oldTable >> e;
		D[j][0] = strtoul(a.c_str(), NULL, 16);
		D[j][4] = strtoul(e.c_str(), NULL, 16);
	}
	
	for (int j = 0; j < 20000; j++)
	{
		getline(oldTable, line);
		if (line.length() >= 5) {
			M[j][0] = line.at(0);
			M[j][1] = line.at(2);
			M[j][2] = line.at(4);
		}
	}

	return(0);
}


int Find::search(unsigned int target_d[5], unsigned char answer_m[3])
{
	unsigned int j = 0;
	unsigned int i = 0;
	long y = 0;
	unsigned char Colour_m[5000][3];
	unsigned int  Colour_d[5000][5];
	bool isDigestFound = false;

	for (j = 0; j< 50; j++)
	{
		Colour_d[j][0] = target_d[0];
		Colour_d[j][1] = target_d[1];
		Colour_d[j][2] = target_d[2];
		Colour_d[j][3] = target_d[3];
		Colour_d[j][4] = target_d[4];
	}

	for (j = 0; j< 50; j++)
	{
		for (int k = 0; k< j + 1; k++)
		{
			Reduce(Colour_d[k], Colour_m[k], j);
			Hash(Colour_m[k], Colour_d[k]);

			//-------- search for the digest Colour_d[k] in the data structure. 
			for (y = 0; y < 999999; y += 50){
				
				if ((Colour_d[k][0] == D[y][0]) && (Colour_d[k][4] == D[y][4])) {
					isDigestFound = true;
					break;
				}
			}

			//-------- if found, call transverse the chain starting from the head to find the pre-image.
			if (isDigestFound) {
				for (int z = 0; z < 50; z++) {
					Hash(M[y - 50 + z], D[y - 50 + z]);
					if ((D[y - 50 + z][0] == D[y][0]) && (D[y - 50 + z][4] == D[y][4])) {
						answer_m = M[y - 50 + z];
						return 1;
					}
				}

			}

		}
	}
	return (0);
}


void Find::readnextd(unsigned  int d[5], int i)
{
	d[0] = D[i][0];
	d[1] = D[i][1];
	d[2] = D[i][2];
	d[3] = D[i][3];
	d[4] = D[i][4];
}

void Find::readInput(unsigned int readDigests[5000][5]) {
	ifstream sampleInput("SAMPLE_INPUT.data");
	string line;
	string a, b, c, d, e;
	
	for (int j = 0; j < 5000; j++)
	{
		sampleInput >> a;
		readDigests[j][0] = strtoul(a.c_str(), NULL, 16);

		sampleInput >> b;
		readDigests[j][1] = strtoul(b.c_str(), NULL, 16);

		sampleInput >> c;
		readDigests[j][2] = strtoul(c.c_str(), NULL, 16);

		sampleInput >> d;
		readDigests[j][3] = strtoul(d.c_str(), NULL, 16);

		sampleInput >> e;
		readDigests[j][4] = strtoul(e.c_str(), NULL, 16);
	}

}

int main()
{
	Find* find = new Find();
	int found = 0;
	int total_found = 0;
	int total_not_found = 0;

	SHA1        sha;
	unsigned int d[5] = { 0 };   // 32 x 5 = 160 bits
	unsigned char m2[3] = { 0 };

	//------------ R E A D     R A I N B O W    T A B L E  --------//
	find->ReadT();       cout << "READ DONE" << endl;

	find->readInput(readDigests);
	//--------  PROJECT  INPUT/OUTPUT FORMAT ----------------//

	total_found = 0;
	total_not_found = 0;

	cout.setf(ios::hex, ios::basefield);       //   setting display to Hexdecimal format.  (this is the irritating part of using C++).
	cout.setf(ios::uppercase);

	for (int i = 0; i<5000; i++)
	{
		find->readnextd(d, i);
		if (find->search(d, m2))
		{
			total_found++;
			//------   print the word in hexdecimal format   -----------
			cout << setw(1) << (unsigned int)m2[0] / 16;
			cout << setw(1) << (unsigned int)m2[0] % 8;
			cout << setw(1) << (unsigned int)m2[1] / 16;
			cout << setw(1) << (unsigned int)m2[1] % 8;
			cout << setw(1) << (unsigned int)m2[2] / 16;
			cout << setw(1) << (unsigned int)m2[2] % 8 << endl;
		}
		else
		{
			total_not_found++;
			cout << setw(6) << 0 << endl;
		}
	}

	cout.setf(ios::dec);
	cout << "Accuracy       C is: " << total_found / 5000.0 << endl;
	cout << "Speedup factor F is: " << (5000.0 / TOTAL_SHA) * 8388608 << endl;

}