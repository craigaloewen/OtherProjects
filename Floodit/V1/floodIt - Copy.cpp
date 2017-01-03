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

void floodIt::printBoard() {
	cout << "----Board----" << endl;
	for (int j = 0; j < boardHeight; j++) {
		for (int i = 0; i < boardWidth; i++) {
			cout << board[i][j];
		}
		cout << endl;
	}
	cout << "----End----" << endl;
	
}

bool floodIt::isWon() {
	
	int mainColor = board[0][0];
	
	for (int j = 0; j < boardHeight; j++) {
		for (int i = 0; i < boardWidth; i++) {
			if (board[i][j] != mainColor) {
				return false;
			}
		}
	}
	
	return true;
	
	
	
}



int floodIt::makeTurn(int colorNum) {
	 
	 BinarySearchTree visitedValues;
	 internalTree = &visitedValues;
	 
	 int mainColor = board[0][0];
	 
	 if (colorNum == mainColor) {
	 	return 0;
	 }
	 
	 recursiveFlood(mainColor,colorNum,0,0);


	 
	 
	 return 1; 
	 
	 
}

void floodIt::checkNode(int searchx, int searchy, int newColor, int mainColor) {
	BinarySearchTree* visitedValues = internalTree;
	
	if ((searchx) < boardWidth && (searchy < boardHeight) && (searchx >= 0) && (searchy >= 0)) {
		if (board[searchx][searchy] == mainColor) {
			if (!visitedValues->exists(searchy*boardWidth+searchx)) {
				visitedValues->insert(searchy*boardWidth+searchx);
				recursiveFlood(mainColor,newColor,searchx,searchy);
			}
		}
	}
	
}

void floodIt::recursiveFlood(int mainColor, int newColor, int i, int j) {
	
	int searchx,searchy;
	board[i][j] = newColor;
	
	searchx = i+1;
	searchy = j;
	
	checkNode(searchx,searchy,newColor,mainColor);
	
	searchx = i-1;
	searchy = j;
	
	checkNode(searchx,searchy,newColor,mainColor);
	
	searchx = i;
	searchy = j+1;
	
	checkNode(searchx,searchy,newColor,mainColor);
	
	searchx = i;
	searchy = j-1;
	
	checkNode(searchx,searchy,newColor,mainColor);
	
	
}


