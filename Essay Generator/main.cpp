#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include <list>

#include "essayGraph.hpp"




using namespace std;



int main() {
	
	ifstream myfile("SampleEssay.txt"); 
	
	
	essayGraph graph1;

	string word;
	int counter = 0;

	
	while (myfile >> word) {
		graph1.addWord(word);
		counter++;
		
		if (counter % 1000 == 0) {
			cout << "Added 1000 words" << endl;
		}
	}
	
	cout << "Finished adding in words" << endl;
	
	
	
	graph1.printGraph();
	graph1.generateEssay(1000);
	
	cout << "Finished output" << endl;
	
	
}
