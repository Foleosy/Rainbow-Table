/*--------
(1) Read in a Rainbow table (built using B.cpp)
(2) Read 1000 digests from standard input and  output the preimage.
------------*/

#define _CRT_SECURE_NO_DEPRECATE
#include "find.h"

Find::Find() {};

int Find::hash(unsigned char word[], unsigned int digest[])
{
	SHA1 sha;
	sha.Reset();
	sha.Input(word[0]);
	sha.Input(word[1]);
	sha.Input(word[2]);
	sha.Result(digest);

	totalSHA += 1;
	return(0);
}

int Find::reduceOneFirst(unsigned char word[], unsigned int digest[], int iterator)
{
	word[0] = (unsigned char)((digest[0] + iterator) % 256);
	word[1] = (unsigned char)((digest[1]) % 256);
	word[2] = (unsigned char)((digest[2]) % 256);

	return(0);
}

int Find::reduceTwoFirst(unsigned char word[], unsigned int digest[], int iterator)
{
	word[0] = (unsigned char)((digest[2] + iterator) % 256);
	word[1] = (unsigned char)((digest[0]) % 256);
	word[2] = (unsigned char)((digest[4]) % 256);

	return(0);
}

int Find::reduceThreeFirst(unsigned char word[], unsigned int digest[], int iterator)
{
	word[0] = (unsigned char)((digest[2] + iterator) % 256);
	word[1] = (unsigned char)((digest[4]) % 256);
	word[2] = (unsigned char)((digest[1]) % 256);

	return(0);
}

int Find::reduceOneSecond(unsigned char word[], unsigned int digest[], int iterator)
{
	word[0] = (unsigned char)((digest[1]) % 256);
	word[1] = (unsigned char)((digest[2] + iterator) % 256);
	word[2] = (unsigned char)((digest[3]) % 256);

	return(0);
}

int Find::reduceTwoSecond(unsigned char word[], unsigned int digest[], int iterator)
{
	word[0] = (unsigned char)((digest[4]) % 256);
	word[1] = (unsigned char)((digest[1] + iterator) % 256);
	word[2] = (unsigned char)((digest[0]) % 256);

	return(0);
}

int Find::reduceThreeSecond(unsigned char word[], unsigned int digest[], int iterator)
{
	word[0] = (unsigned char)((digest[1]) % 256);
	word[1] = (unsigned char)((digest[0] + iterator) % 256);
	word[2] = (unsigned char)((digest[4]) % 256);

	return(0);
}

int Find::reduceOneThird(unsigned char word[], unsigned int digest[], int iterator)
{
	word[0] = (unsigned char)((digest[2]) % 256);
	word[1] = (unsigned char)((digest[3]) % 256);
	word[2] = (unsigned char)((digest[4] + iterator) % 256);

	return(0);
}

int Find::reduceTwoThird(unsigned char word[], unsigned int digest[], int iterator)
{
	word[0] = (unsigned char)((digest[3]) % 256);
	word[1] = (unsigned char)((digest[2]) % 256);
	word[2] = (unsigned char)((digest[0] + iterator) % 256);

	return(0);
}

int Find::reduceThreeThird(unsigned char word[], unsigned int digest[], int iterator)
{
	word[0] = (unsigned char)((digest[0]) % 256);
	word[1] = (unsigned char)((digest[2]) % 256);
	word[2] = (unsigned char)((digest[3] + iterator) % 256);

	return(0);
}

int Find::reductionFunctionSorting(int reductionType, int tableNum, unsigned char word[][3], unsigned int digest[][5], int j)
{
	switch (reductionType)
	{
		case 1:
			{
				switch (tableNum)
				{
					case 0:
						{
							reduceOneFirst(word[j], digest[j], j);
							break;
						}
					case 1:
						{
							reduceTwoFirst(word[j], digest[j], j);
							break;
						}
					case 2:
						{
							reduceThreeFirst(word[j], digest[j], j);
							break;
						}
				}
				reductionType = 2;
				break;
			}
		case 2:
			{
				switch (tableNum)
				{
					case 0:
						{
							reduceOneSecond(word[j], digest[j], j);
							break;
						}
					case 1:
						{
							reduceTwoSecond(word[j], digest[j], j);
							break;
						}
					case 2:
						{
							reduceThreeSecond(word[j], digest[j], j);
							break;
						}
				}
				reductionType = 3;
				break;
			}
		case 3:
			{
				switch (tableNum)
				{
					case 0:
						{
							reduceOneThird(word[j], digest[j], j);
							break;
						}
					case 1:
						{
							reduceTwoThird(word[j], digest[j], j);
							break;
						}
					case 2:
						{
							reduceThreeThird(word[j], digest[j], j);
							break;
						}
				}
				reductionType = 1;
				break;
			}
	}
	return reductionType;
}

void Find::readFile(FILE* fileToRead, int tableNumber) {
	for (int i = 0 + this->rows * tableNumber; i < this->rows * (tableNumber + 1); i++)
	{
		fread(&(wordsFromFile[i][0]), sizeof(unsigned char), 1, fileToRead);
		fread(&(wordsFromFile[i][1]), sizeof(unsigned char), 1, fileToRead);
		fread(&(wordsFromFile[i][2]), sizeof(unsigned char), 1, fileToRead);

		fread(&(digestsFromFile[i][0]), sizeof(unsigned int), 1, fileToRead);
	}
}

int Find::readT()
{
	FILE *theFirstTable = fopen("firstTable", "rb");
	readFile(theFirstTable, 0);

	/*	FILE *theSecondTable = fopen("secondTable", "rb");
		readFile(theSecondTable, 1);

		FILE *theThirdTable = fopen("thirdTable", "rb");
		readFile(theThirdTable, 2);
		*/
	return(0);
}

int Find::search()
{
	unsigned int j = 0;
	unsigned int i = 0;
	long y = 0;
	unsigned char Colour_m[5000][3];
	unsigned int  Colour_d[5000][5];
	unsigned int newDigest[241][5];
	int isDigestFound = 0;
	unsigned char newWord[240][3];

	for (int tableNum = 0; tableNum < 3; tableNum++) {
		for (int startReduction = 1; startReduction < 4; startReduction++) {
			int reductionType = startReduction;

			Colour_d[0][0] = d[0];
			Colour_d[0][1] = d[1];
			Colour_d[0][2] = d[2];
			Colour_d[0][3] = d[3];
			Colour_d[0][4] = d[4];

			for (j = 0; j < chainLength; j++)
			{
				isDigestFound = 0;

				reductionType = reductionFunctionSorting(reductionType, tableNum, Colour_m, Colour_d, j);

				hash(Colour_m[j], Colour_d[j + 1]);

				for (y = 0; y < 100000; y++) {
					if ((Colour_d[j + 1][0] == digestsFromFile[y][0])) {
						isDigestFound = 1;
						break;
					}
				}

				if (isDigestFound == 1) {

					for (int startingReductionType = 1; startingReductionType < 4; startingReductionType++) {
						int reductionTypeTwo = startingReductionType;
						newWord[0][0] = wordsFromFile[y][0];
						newWord[0][1] = wordsFromFile[y][1];
						newWord[0][2] = wordsFromFile[y][2];

						SHA1 sha;
						sha.Reset(); sha.Input(newWord[0][0]); sha.Input(newWord[0][1]); sha.Input(newWord[0][2]);
						sha.Result(newDigest[0]);
						totalSHA = totalSHA + 1;

						for (int z = 0; z < 240; z++) {
							if ((newDigest[z][0] == Colour_d[0][0]) && (newDigest[z][1] == Colour_d[0][1]) && (newDigest[z][2] == Colour_d[0][2]) 
								&& (newDigest[z][3] == Colour_d[0][3]) && (newDigest[z][4] == Colour_d[0][4])) {
								currentAnswer[0] = newWord[z][0];
								currentAnswer[1] = newWord[z][1];
								currentAnswer[2] = newWord[z][2];
								return 1;
							}
							else {
								reductionTypeTwo = reductionFunctionSorting(reductionTypeTwo, tableNum, newWord, newDigest, z);

								hash(newWord[z], newDigest[z + 1]);

							}
						}
					}
				}
			}
		}
	}
	return (0);
}


void Find::readNextD(unsigned  int d[], int i)
{
	d[0] = readDigests[i][0];
	d[1] = readDigests[i][1];
	d[2] = readDigests[i][2];
	d[3] = readDigests[i][3];
	d[4] = readDigests[i][4];
}

void Find::readInput() {
	std::ifstream sampleInput("SAMPLE_INPUT.data");
	std::string line;
	std::string a, b, c, d, e;

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
	Find* find = new Find();;
	SHA1 sha;

	int totalFound = 0;
	int totalNotFound = 0;

	//------------ R E A D     R A I N B O W    T A B L E  --------//
	find->readT();
	std::cout << "READ DONE" << std::endl;

	find->readInput();

	//--------  PROJECT  INPUT/OUTPUT FORMAT ----------------//
	std::cout.setf(std::ios::hex, std::ios::basefield);       //   setting display to Hexdecimal format.  (this is the irritating part of using C++).
	std::cout.setf(std::ios::uppercase);

	for (int i = 0; i < 5000; i++)
	{
		find->readNextD(find->d, i);

		if (find->search() == 1)
		{
			totalFound++;
			//------   print the word in hexdecimal format   -----------
			std::cout << std::setw(1) << (unsigned int)find->currentAnswer[0] / 16;
			std::cout << std::setw(1) << (unsigned int)find->currentAnswer[0] % 8;
			std::cout << std::setw(1) << (unsigned int)find->currentAnswer[1] / 16;
			std::cout << std::setw(1) << (unsigned int)find->currentAnswer[1] % 8;
			std::cout << std::setw(1) << (unsigned int)find->currentAnswer[2] / 16;
			std::cout << std::setw(1) << (unsigned int)find->currentAnswer[2] % 8 << std::endl;
		}
		else
		{
			totalNotFound++;
			std::cout << std::setw(6) << 0 << std::endl;
		}
	}

	std::cout.setf(std::ios::dec);
	std::cout << "S is: " << find->totalSHA << std::endl;
	std::cout << "C is: " << totalFound / 50.0 << std::endl;
	std::cout << "F is: " << (5000.0 / find->totalSHA) * 8388608 << std::endl;

	delete find;
}