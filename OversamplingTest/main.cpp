#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <fstream>
#include <math.h>

using namespace std;

const int dataLength = 100;


void generateData(int bitNum, short data[]) {
	
	int maxNum = 1;
	
	int addNum;
	
	maxNum = maxNum << (bitNum);
	
	for (int i = 0; i < dataLength; i++) {
		//data[i] = (rand() % maxNum) ;	
		//data[i] = (i * maxNum) / dataLength;
		
		
		data[i] = maxNum / 2.5 * sin(i*2*3.14159265/dataLength*2) + maxNum / 2; 
		
		addNum = rand() % 2;
		
		if (rand() % 2 == 0) {
			data[i] += addNum;
		} else {
			data[i] -= addNum;
		}
		
		if (data[i] > maxNum) {
			data[i] = maxNum;
		}
		if (data[i] < 0) {
			data[i] = 0;
		}
		
		//data[i] = 5+i/10;
		
		
		
	}
}

void overSample(int bitShift,short data[], short overSampledData[]) {
	
	int overSampleSum = 0; 
	
	for (int i = 0; i < dataLength; i++) {
		overSampleSum = 0;
		for (int j = 0; j < 4*bitShift; j++) {
			if ((i - j) >= 0) {
				overSampleSum += data[i-j];
			} else {
				overSampleSum += data[0];
			}
		}
		overSampleSum = overSampleSum >> bitShift;
			
		overSampledData[i] = overSampleSum; 
	}
}

void printDataToFile(int dataBits, int overSampledBits, short data[], short overSampledData[]) {
	ofstream myFile;
	myFile.open("OutputData.csv");
	
	int dataMaxNum = 1 << dataBits; 
	int sampledMaxNum = 1 << overSampledBits;
	
	myFile << "RawSample;OverSampled;RawNumber;OverNumber" << endl;
	
	for (int i = 0; i < dataLength; i++) {
		myFile << data[i] / 1.0 / dataMaxNum << ";" << overSampledData[i] / 1.0 / sampledMaxNum << ";" << data[i] << ";" << overSampledData[i] << endl;
	}
	
	myFile.close();
	
	
}



int main() {
	srand(time(NULL));
	
	int dataBits = 5;
	int sampleIncrease = 1;
	short data[dataLength];
	short overSampledData[dataLength];
	
//	generateData(dataBits,data);
//	overSample(sampleIncrease,data,overSampledData);
//	printDataToFile(dataBits,dataBits+sampleIncrease, data,overSampledData);
	
	generateData(dataBits,data);
	overSample(sampleIncrease,data,overSampledData);
	printDataToFile(dataBits,dataBits+sampleIncrease+1,data,overSampledData);
	
	
	
	
	
	
}
