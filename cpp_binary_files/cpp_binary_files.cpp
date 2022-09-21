#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<float> data_init = {};
vector<float> data_read = {};

int main()
{
	
	//1 - make array
	for (int i = 0; i < 10; i++)
	{
		data_init.push_back((float)i);
		float val = 10 * pow((float)i, 2);
		data_init.push_back(val);
		printf("%d) %f; %f;\n",i,(float)i,val);
	}
	
	//2 - write array in binary
	ofstream dataWriter("numbers.bin",ios::out|ios::binary);
	if (!dataWriter.is_open()) return -1;
	
	int l = data_init.size();

	dataWriter.write((char*)&l, sizeof(int));

	for (int i = 0; i < l; i++)
	{
		dataWriter.write(reinterpret_cast<const char*>(&data_init[i]), sizeof(float));
	}

	dataWriter.close();

	//3 - read array from binary
	ifstream dataReader("numbers.bin", ios::in | ios::binary);
	if (!dataReader.is_open()) return -1;

	dataReader.seekg(0, ios::beg);
	
	dataReader.read((char*)&l,sizeof(int));

	for (int i = 0; i < l; i++)
	{
		float v = 0.0f;
		dataReader.read((char*)&v, sizeof(float));
		data_read.push_back(v);
	}

	dataReader.close();

	//4 - output read data
	printf("\nFinal output:\n]");
	for (int i = 0; i < (l-1); i+=2)
	{
		printf("%d) %f; %f;\n", i, data_read[i], data_read[i+1]);
	}

	system("pause");

	return 0;
}