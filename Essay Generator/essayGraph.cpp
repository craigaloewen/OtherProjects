#include "essayGraph.hpp"





using namespace std; 




essayGraph::essayGraph() {
	
	numWords = 0;
	root = 0;
	wordBefore = STRINGNULL;
}

bool essayGraph::searchList(list<graphNode*>* test, graphNode* x) {
	
	return (find(test->begin(), test->end(),x) != test->end());
}

essayGraph::graphNode* essayGraph::findWordNode(string newWord) {
	
	if (root == 0) {
		return 0; 
	} else {
		
		graphNode* visitor = root; 
		list<graphNode*> visited; 
		list<graphNode*> toVisit; 
		
		
		toVisit.insert(toVisit.end(),visitor->edgeList.begin(),visitor->edgeList.end());
		toVisit.push_front(visitor);
		
		while (toVisit.size() > 0) {
			
			visitor = toVisit.front();
			if (searchList(&visited,visitor)) {
				toVisit.pop_front();
			} else {
				toVisit.pop_front();
				
				if (visitor->word == newWord) {
					return visitor; 
				}
				visited.push_front(visitor);
				toVisit.insert(toVisit.end(),visitor->edgeList.begin(),visitor->edgeList.end());
			}
		}
		return 0;
	}
	
	
	
	
}

void essayGraph::printGraph() {
	
	ofstream myfile;
	myfile.open("NodeOutput.txt");
	
	
	if (root == 0) {
		myfile << "Graph is Empty" << endl;
		return;
	} else {
		
		graphNode* visitor = root; 
		list<graphNode*> visited; 
		list<graphNode*> toVisit; 
		
		int visitedNum = 1;
		
		toVisit.insert(toVisit.end(),visitor->edgeList.begin(),visitor->edgeList.end());
		toVisit.push_front(visitor);
		
		
		myfile << "--Graph--" << endl;
		
		while (toVisit.size() > 0) {
			
			visitor = toVisit.front();
			if (searchList(&visited,visitor)) {
				toVisit.pop_front();
			} else {
				toVisit.pop_front();
				
				myfile << "Node: " << visitedNum << " has " << visitor->edgeList.size() << " connections;word: " << visitor->word << endl;
				visitedNum++;
				visited.push_front(visitor);
				toVisit.insert(toVisit.end(),visitor->edgeList.begin(),visitor->edgeList.end());
			}
		}
		myfile << "--End--" << endl;
		myfile.close();
		return;
	}
	
}

bool essayGraph::addWord(string newWord) {
	
	if (root == 0) {
		
		graphNode* newNode = new graphNode(newWord);
		numWords++;
		root = newNode;
		wordBefore = newWord;
		return true;
	} else {
		
		
		graphNode* oldWordVisitor = findWordNode(wordBefore);
		
		if (oldWordVisitor == 0) {
			cout << "This shouldn't happen!" << endl;
			return false;
		}
		
		graphNode* inWordVisitor = findWordNode(newWord);
		
		if (inWordVisitor) {
			oldWordVisitor->edgeList.push_front(inWordVisitor);
			wordBefore = newWord;
			return true;
		} else {
			inWordVisitor = new graphNode(newWord);
			numWords++;
			
			oldWordVisitor->edgeList.push_front(inWordVisitor);
			wordBefore = newWord;
			return true;
		}
		
		cout << "Also shouldn't happen..." << endl;
		return false;
	}
	
}
	
void essayGraph::generateEssay(int wordCount) {
	
	ofstream myfile;
	myfile.open("DataOutput.txt");
	
	if (root == 0) {
		myfile << "Graph is Empty" << endl;
		return;
	} else {
		
		graphNode* visitor = root; 
		int connectionNum = 0;
		int currentWords = 0;
		int selectChoice = 0;
		srand(time(NULL));	
		
		
		while (currentWords < wordCount) {
			
			myfile << " " << visitor->word << " "; 
			
			connectionNum = visitor->edgeList.size();
			
			selectChoice = rand() % connectionNum;
			
			
			list<graphNode*>::iterator it = visitor->edgeList.begin();
			advance(it,selectChoice);
			
			visitor = *it;
			
			currentWords++;
		}
		
		myfile.close();
		
		
		
		
		
	}

}
	


