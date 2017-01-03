#ifndef FLOODIT_HPP
#define FLOODIT_HPP


#include <iostream>
#include <cstdlib>
#include <cmath>
#include <stdlib.h>
#include <ctime>
#include <algorithm>
#include <string>
#include <list>
#include <fstream>

#define STRINGNULL "#$NULL$#"




class essayGraph
{

public:
	
	essayGraph();
	
	struct graphNode {
		
		graphNode(std::string newWord) {
			word = newWord;
		}
		
		std::string word;
		
		std::list<graphNode*> edgeList;
		
	};
	
	bool addWord(std::string newWord);
	bool searchList(std::list<graphNode*>* test, graphNode* x);
	graphNode* findWordNode(std::string newWord);
	void printGraph();
	void generateEssay(int wordCount);
	
	
	
  
private:
	
	int numWords;
	graphNode* root;
	std::string wordBefore;
	

	
	
	

	
  
};

#endif  //WORD_HPP
