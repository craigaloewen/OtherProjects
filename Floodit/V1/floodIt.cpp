#include "floodIt.hpp"




using namespace std; 

floodIt::floodIt() {
	
	boardHeight = 12;
	boardWidth = 12;

	
	for (int j = 0; j < boardHeight; j++) {
		for (int i = 0; i < boardWidth; i++) {
			board[i][j] = 0;
		}
	}
		
}

int floodIt::randomize() {
	
	for (int j = 0; j < boardHeight; j++) {
		for (int i = 0; i < boardWidth; i++) {
			board[i][j] = rand() % COLORNUM;
		}
	}
}

void floodIt::makeObstacles() {
	
	board[1][1] = 100;
	board[1][2] = 100;
	board[1][3] = 100;
	board[1][4] = 100;
	board[3][1] = 100;
	board[4][1] = 100;
}

void floodIt::printBoard() {
	cout << "----Board----" << endl;
	for (int j = 0; j < boardHeight; j++) {
		for (int i = 0; i < boardWidth; i++) {
			
			if (board[i][j] > 9) {
				cout << "X";
			} else {
				cout << board[i][j];
			}
		}
		cout << endl;
	}
	cout << "----End----" << endl;
	
}

bool floodIt::isWon() {
	
	int mainColor = board[0][0];
	
	for (int j = 0; j < boardHeight; j++) {
		for (int i = 0; i < boardWidth; i++) {
			if (board[i][j] != 100) {
				if (board[i][j] != mainColor) {
					return false;
				}
			}
		}
	}
	
	return true;
	
	
	
}



int floodIt::makeTurn(int colorNum) {
	
	 BinarySearchTree* visitedValues = new BinarySearchTree();
	 
	 getFloodTiles(visitedValues,0,0);
	 
	 
	 int i,j;
	 int treeValue;
	 while (visitedValues->size() > 0) {
	 	treeValue = visitedValues->max();
	 	decodeTreeValue(treeValue,i,j);
	 	
	 	//
	 	board[i][j] = colorNum;
	 	//
	 	
	 	
	 	visitedValues->remove(treeValue);
	 }
	 
	 free(visitedValues);
	 
	 return 1; 	
}

void floodIt::decodeTreeValue(int treeVal, int &i, int &j) {
	i = treeVal % boardWidth;
	j = treeVal / boardHeight;	
}

int floodIt::encodeTreeValue(int i, int j) {
	return j*boardHeight + i;
}

void floodIt::getFloodTiles(BinarySearchTree* tree, int i, int j) {
	
	int mainColor = board[i][j];
	int searchx, searchy;
	int encodedValue;
	
	encodedValue = encodeTreeValue(i,j);
	tree->insert(encodedValue);
	
	
	searchx = i+1; 
	searchy = j;
	
	if (searchx < boardWidth && !(tree->exists(encodeTreeValue(searchx,searchy)))) {
		if (board[searchx][searchy] == mainColor) {
			getFloodTiles(tree,searchx,searchy);	
		}
	}
	
	searchx = i-1; 
	searchy = j;
	
	if (searchx >= 0 && !(tree->exists(encodeTreeValue(searchx,searchy)))) {
		if (board[searchx][searchy] == mainColor) {
			getFloodTiles(tree,searchx,searchy);	
		}
	}
	
	searchx = i; 
	searchy = j-1;
	
	if (searchy >= 0 && !(tree->exists(encodeTreeValue(searchx,searchy)))) {
		if (board[searchx][searchy] == mainColor) {
			getFloodTiles(tree,searchx,searchy);	
		}
	}
	
	searchx = i; 
	searchy = j+1;
	
	if (searchy < boardHeight && !(tree->exists(encodeTreeValue(searchx,searchy)))) {
		if (board[searchx][searchy] == mainColor) {
			getFloodTiles(tree,searchx,searchy);	
		}
	}
}

void floodIt::getFloodTiles(BinarySearchTree* tree, BinarySearchTree* touching, int i, int j) {
	
	int mainColor = board[i][j];
	
	if (mainColor == 100) {
		return;
	}
	
	
	int searchx, searchy;
	int encodedValue;
	
	encodedValue = encodeTreeValue(i,j);
	tree->insert(encodedValue);
	
	
	searchx = i+1; 
	searchy = j;
	
	if (searchx < boardWidth && !(tree->exists(encodeTreeValue(searchx,searchy)))) {
		if (board[searchx][searchy] == mainColor) {
			getFloodTiles(tree,touching,searchx,searchy);	
		} else if (!touching->exists(encodeTreeValue(searchx,searchy))) {
			touching->insert(encodeTreeValue(searchx,searchy));
		}
	}
	
	searchx = i-1; 
	searchy = j;
	
	if (searchx >= 0 && !(tree->exists(encodeTreeValue(searchx,searchy)))) {
		if (board[searchx][searchy] == mainColor) {
			getFloodTiles(tree,touching,searchx,searchy);	
		} else if (!touching->exists(encodeTreeValue(searchx,searchy))) {
			touching->insert(encodeTreeValue(searchx,searchy));
		}
	}
	
	searchx = i; 
	searchy = j-1;
	
	if (searchy >= 0 && !(tree->exists(encodeTreeValue(searchx,searchy)))) {
		if (board[searchx][searchy] == mainColor) {
			getFloodTiles(tree,touching,searchx,searchy);	
		} else if (!touching->exists(encodeTreeValue(searchx,searchy))) {
			touching->insert(encodeTreeValue(searchx,searchy));
		}
	}
	
	searchx = i; 
	searchy = j+1;
	
	if (searchy < boardHeight && !(tree->exists(encodeTreeValue(searchx,searchy)))) {
		if (board[searchx][searchy] == mainColor) {
			getFloodTiles(tree,touching,searchx,searchy);	
		} else if (!touching->exists(encodeTreeValue(searchx,searchy))) {
			touching->insert(encodeTreeValue(searchx,searchy));
		}
	}
}


int floodIt::findBottomRightColor() {
	 
	 BinarySearchTree* visitedValues = new BinarySearchTree();
	 BinarySearchTree* touchingValues = new BinarySearchTree();
	 
	 getFloodTiles(visitedValues,touchingValues,0,0);
	 
	 int maxScore,colorAnswer; 
	 maxScore = 0;
	 colorAnswer = 0;
	 
	 int i,j;
	 int treeValue;
	 while (touchingValues->size() > 0) {
	 	treeValue = touchingValues->max();
	 	decodeTreeValue(treeValue,i,j);
	 	
	 	//
	 	if (getLeftCornerDistance(i,j) > maxScore) {
	 		maxScore = getLeftCornerDistance(i,j);
	 		colorAnswer = board[i][j];
	 	}
	 	//
	 	
	 	
	 	touchingValues->remove(treeValue);
	 }
	 
	 free(visitedValues);
	 free(touchingValues);
	 
	 return colorAnswer; 	
}

int floodIt::findMostTouching() {
	 
	 BinarySearchTree* visitedValues = new BinarySearchTree();
	 BinarySearchTree* touchingValues = new BinarySearchTree();
	 BinarySearchTree* countingTree = new BinarySearchTree();
	 
	 int touchingNumber[COLORNUM] = {0};
	 
	 getFloodTiles(visitedValues,touchingValues,0,0);
	 
	 int colorAnswer, maxValue;
	 colorAnswer = 0;
	 maxValue = 0; 
	 
	 int i,j,i2,j2;
	 int treeValue,treeValue2;
	 while (touchingValues->size() > 0) {
	 	treeValue = touchingValues->max();
	 	decodeTreeValue(treeValue,i,j);
	 	
	 	//
	 	getFloodTiles(countingTree,i,j);
	 	
	 	while (countingTree->size() > 0) {
	 		treeValue2 = countingTree->max();
	 		decodeTreeValue(treeValue2,i2,j2);
	 		
	 		if (touchingValues->exists(treeValue2) && i != i2 && j != j2) {
	 			touchingValues->remove(treeValue2);
	 		}
	 		
	 		touchingNumber[board[i2][j2]] += 1;
	 		
	 		countingTree->remove(treeValue2);

	 	}	 	
	 	//
	 	
	 	
	 	touchingValues->remove(treeValue);
	 }
	 
	 free(visitedValues);
	 free(touchingValues);
	 
	 for (int i = 0; i < COLORNUM; i++) {
	 	if (touchingNumber[i] > maxValue) {
	 		maxValue = touchingNumber[i];
	 		colorAnswer = i;
	 	}
	 }
	 
	 
	 return colorAnswer; 	
}

int floodIt::getLeftCornerDistance(int i, int j) {
	return i + j;
}

