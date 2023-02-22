#include <stdio.h>
#include <iostream>
#include <list>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <bitset>

using namespace std;

#define SAMPLECOUNT 16
#define BINARY 0

// ____Wav.csv is the samples directly from the Vivado
// .dat file is the output signed decimal file
// ____PDTI.xlsx is the signed decimal file where we make the graph


string hex2bin(string& hex)
{
	//to format hex values as binary
	string temp = "";
	for (int i = 0; i < hex.size(); i++) {
		switch (hex[i]) {
		case '0': temp.append("0000"); break;
		case '1': temp.append("0001"); break;
		case '2': temp.append("0010"); break;
		case '3': temp.append("0011"); break;
		case '4': temp.append("0100"); break;
		case '5': temp.append("0101"); break;
		case '6': temp.append("0110"); break;
		case '7': temp.append("0111"); break;
		case '8': temp.append("1000"); break;
		case '9': temp.append("1001"); break;
		case 'a': temp.append("1010"); break;
		case 'b': temp.append("1011"); break;
		case 'c': temp.append("1100"); break;
		case 'd': temp.append("1101"); break;
		case 'e': temp.append("1110"); break;
		case 'f': temp.append("1111"); break;
		}
	}
	return temp;
}

vector<string> convPacking(string hex) {
#if SAMPLECOUNT == 16
	//cout << hex.size() << endl;
	if (hex.size() != 256) {
#elif SAMPLECOUNT == 12
	if (hex.size() != 192) {
#endif
		//cout << "Hex size is: " << hex.size() << endl;
		//cout << "Error with hexadecimal size\n" << endl;
		return{ "Error" };
	}

	vector<string> result;
	//convert strings into 16 bits
	string str1 = "";
	string str2 = "";
	string str3 = "";
	string str4 = "";
	string str5 = "";
	string str6 = "";
	string str7 = "";
	string str8 = "";
	string str9 = "";
	string str10 = "";
	string str11 = "";
	string str12 = "";
#if SAMPLECOUNT == 16
	string str13 = "";
	string str14 = "";
	string str15 = "";
	string str16 = "";
#endif

	for (int i = 0; i < hex.size(); i++) {
		if (i < 16) {
			str1 = str1 + hex[i];
		}
		else if ((i >= 16)  && (i < 32)){
			str2 = str2 + hex[i];
		}
		else if ((i >= 32) && (i < 48)) {
			str3 = str3 + hex[i];
		}
		else if ((i >= 48) && (i < 64)) {
			str4 = str4 + hex[i];
		}
		else if ((i >= 64) && (i < 80)) {
			str5 = str5 + hex[i];
		}
		else if ((i >= 80) && (i < 96)) {
			str6 = str6 + hex[i];
		}
		else if ((i >= 96) && (i < 112)) {
			str7 = str7 + hex[i];
		}
		else if ((i >= 112) && (i < 128)) {
			str8 = str8 + hex[i];
		}
		else if ((i >= 128) && (i < 144)) {
			str9 = str9 + hex[i];
		}
		else if ((i >= 144) && (i < 160)) {
			str10 = str10 + hex[i];
		}
		else if ((i >= 160) && (i < 176)) {
			str11 = str11 + hex[i];
		}
		else if ((i >= 176) && (i < 192)) {
			str12 = str12 + hex[i];
		}
#if SAMPLECOUNT == 16
		else if ((i >= 192) && (i < 208)) {
			str13 = str13 + hex[i];
		}
		else if ((i >= 208) && (i < 224)) {
			str14 = str14 + hex[i];
		}
		else if ((i >= 224) && (i < 240)) {
			str15 = str15 + hex[i];
		}
		else if ((i >= 240) && (i < 256)) {
			str16 = str16 + hex[i];
		}
#endif
	}

	result.push_back(str1);
	result.push_back(str2);
	result.push_back(str3);
	result.push_back(str4);
	result.push_back(str5);
	result.push_back(str6);
	result.push_back(str7);
	result.push_back(str8);
	result.push_back(str9);
	result.push_back(str10);
	result.push_back(str11);
	result.push_back(str12);
#if SAMPLECOUNT == 16
	result.push_back(str13);
	result.push_back(str14);
	result.push_back(str15);
	result.push_back(str16);
#endif

	return result;
}

int16_t bin2int(string& str) {
	int16_t temp = 0;
	int base = 2;
	//cout << "string -> " << str << "\n" << endl;
	if (str.front() == '0') {
		temp = stoi(str, 0, base);
	}
	else if (str.front() == '1') {
		//cout << "string -> " << str << "\n" << endl;
		string strTemp = "";
		//flip bits
		for (int i = 0; i < str.size(); i++) {
			if (str[i] == '0') {
				strTemp = strTemp + '1';
			}
			else {
				strTemp = strTemp + '0';
			}
		}
		//cout << "flipped string -> " << strTemp << "\n" << endl;
		int size = strTemp.size();
		if (strTemp.back() == 0) {
			strTemp.back() = 1;
		}
		else {
			int i = size - 1;
			while (strTemp[i] == '1') {
				strTemp[i] = '0';
				i--;
			}
			strTemp[i] = '1';
		}
		//cout << "modified string -> " << strTemp << "\n" << endl;
		temp = -1 * (stoi(strTemp, 0, base) );
	}
	//cout << "decimal value -> " << temp << "\n" << endl;
	return temp;
}

int main() {

	fstream file;
	string hexFile;
	string binaryFile;
	string integerFile;
	cout << "Enter input hexacecimal .xlsx file name: ";
	cin >> hexFile;
#if BINARY == 1
	cout << "Enter output binary .dat file name: ";
	cin >> binaryFile;
#endif
	cout << "Enter output signed decimal .dat file name: ";
	cin >> integerFile;
	cout << "Copy from .dat file to .csv file." << endl;

	file.open(hexFile, ios::in | ios::out);
	if (!file.is_open()) {
		cout << "Error open file (1).\n" << endl;
		return 0;
	}

#if BINARY == 1
	fstream fileBin;
	fileBin.open(binaryFile, ios::in | ios::out);
#endif

	vector<string> rawData;

	//extract data from .csv and reverse

	while (!file.eof()) {
		string temp;
		file >> temp;

		auto it = remove_if(temp.begin(), temp.end(), [](char const &c) {
			return !isalnum(c);
		});

		temp.erase(it, temp.end());
		rawData.push_back(temp);
	}

	//test binary 192 or 256 bit data chunks
#if 0
	for (int i = 0; i < 5; i++) {
		cout << rawData[i] << endl;
	}
#endif

	//convert all hex values to bin
	for (int i = 0; i < rawData.size(); i++) {
		rawData[i] = hex2bin(rawData[i]);
	}

	//test binary 192 or 256 bit data chunks
#if 0
	for (int i = 0; i < 5; i++) {
		cout << rawData[i] << endl;
	}
#endif
	
	vector<vector<string>> packedData;

	//for each binary chunk, break into chunks of 16 binary values
	for (int i = 0; i < rawData.size(); i++) {
		vector<string>temp = convPacking(rawData[i]);
		packedData.push_back(temp);
	}
#if BINARY == 1
#if SAMPLECOUNT == 16
	int skip = 0;
#endif
	for (int i = 0; i < packedData.size(); i++) {
		for (int j = packedData[i].size() - 1; j >= 0; j--) {
			fileBin << packedData[i][j] << " ";
		}
		fileBin << endl;
#if SAMPLECOUNT == 16
		skip++;
		if (skip == 3) {
			i++;
			skip = 0;
		}
#endif
}
#endif

	//test 16x16 bit output chunks
#if 0
	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < 1; j++) {
			cout << packedData[i][j] << endl;
		}
		cout << endl;
	}
#endif

	//convert each 16 bit value to integer
	vector<vector<int16_t>> integerData;
	for (int i = 0; i < packedData.size(); i++) {
		vector<int16_t> tempIntData;
		for (int j = 0; j < packedData[i].size(); j++) {
			int temp = bin2int(packedData[i][j]);
			tempIntData.push_back(temp);
		}
		integerData.push_back(tempIntData);
	}

#if 0
	for (int i = 0; i < integerData.size(); i++) {
		for (int j = 0; j < integerData[i].size(); j++) {
			cout << integerData[i][j] << endl;
		}
		cout << endl;
	}
#endif

#if BINARY == 1
	fileBin.close();
#endif
	file.close();

	fstream fileDat;
	fileDat.open(integerFile, ios::in | ios::out);

	if (!fileDat.is_open()) {
		cout << "Error opening file (2).\n" << endl;
		return 0;
	}

	int numDataPoints = 100;

#if SAMPLECOUNT == 16
#if BINARY == 1
	skip = 0;
#else
	int skip = 0;
#endif
#endif
	for (int i = 0; i < integerData.size(); i++) {
		for (int j = integerData[i].size() - 1; j >= 0; j--) {
			fileDat << integerData[i][j] << endl;
		}
#if SAMPLECOUNT == 16
		skip++;
		if (skip == 3) {
			i++;
			skip = 0;
		}
#endif
	}

	fileDat.close();
	cout << "Program finished.\n";

	return 0;
}