#include "floodIt.hpp"




using namespace std; 

floodIt::floodIt() {
	
	boardHeight = 12;
	boardWidth = 12;
	
	turnNumber = 0;
	
	for (int i = 0; i < COLORNUM; i++) {
		colorChosenAmount[i] = 0;
	}

	
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

	return 0;
}

void floodIt::makeObstacles() {
	
	board[1][1] = 100;
	board[1][2] = 100;
	board[1][3] = 100;
	board[1][4] = 100;
	board[3][1] = 100;
	board[4][1] = 100;
}

int floodIt::countSolvedTiles() {
	
	BinarySearchTree* countTree = new BinarySearchTree();
	
	getFloodTiles(countTree,0,0);
	
	int returnVal = countTree->size();
	
	delete countTree;
	
	return returnVal;
	
	
	
	
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



int floodIt::makeTurn(int inColorNum) {
	
	 BinarySearchTree* visitedValues = new BinarySearchTree();
	  
	 
	 getFloodTiles(visitedValues,0,0);
	 
	 
	 int i,j;
	 int treeValue;
 	 while (visitedValues->size() > 0) {
 		treeValue = visitedValues->maxFunction();
 		decodeTreeValue(treeValue,i,j);
 	
 		//
 		board[i][j] = inColorNum;
 		//
 	
	 	
	 	visitedValues->remove(treeValue);
	 }
	 
	 colorChosenAmount[inColorNum]++;
	 turnNumber++;
	 
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
	 	treeValue = touchingValues->maxFunction();
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
	 	treeValue = touchingValues->maxFunction();
	 	decodeTreeValue(treeValue,i,j);
	 	
	 	//
	 	getFloodTiles(countingTree,i,j);
	 	
	 	while (countingTree->size() > 0) {
	 		treeValue2 = countingTree->maxFunction();
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

void floodIt::solve() {
	
	for (int j = 0; j < boardHeight; j++) {
		for (int i = 0; i < boardWidth; i++) {
			board[i][j] = 0;
		}
	}
	
}

int floodIt::findLeastUsedColor() {
	
	int minColorAmount = 9999999; 
	int minColorVal = 0;
	
	for (int i = 0; i < COLORNUM; i++) {
		
		if (colorChosenAmount[i] < minColorAmount) {
			minColorAmount = colorChosenAmount[i];
			minColorVal = i;
		}
		
		
	}
	return minColorVal;
	
	
}

int floodIt::findMostUsedColor() {

	int maxColorAmount = 0;
	int maxColorVal = 0;

	for (int i = 0; i < COLORNUM; i++) {

		if (colorChosenAmount[i] > maxColorAmount) {
			maxColorAmount = colorChosenAmount[i];
			maxColorVal = i;
		}


	}
	return maxColorVal;


}

void floodIt::Render(HDC &surface, int startx, int starty, int endx, int endy) {

	HBRUSH blueBrush = CreateSolidBrush(RGB(0, 0, 255));
	HBRUSH greenBrush = CreateSolidBrush(RGB(0, 255, 0));
	HBRUSH tealBrush = CreateSolidBrush(RGB(0, 255, 255));
	HBRUSH redBrush = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH purpleBrush = CreateSolidBrush(RGB(255, 0, 255));
	HBRUSH yellowBrush = CreateSolidBrush(RGB(255, 255, 0));
	HBRUSH darkGreenBrush = CreateSolidBrush(RGB(0, 100, 0));

	SelectObject(surface, redBrush);


	int blockWidth = (endx - startx) / boardWidth;
	int blockHeight = (endy - starty) / boardHeight;

	int blockPainterStart = startx; 

	int topleftx, toplefty, bottomrightx, bottomrighty;

	for (int j = 0; j < boardHeight; j++) {
		for (int i = 0; i < boardWidth; i++) {

			switch(board[i][j]) {

			case 0 :
				SelectObject(surface, redBrush);
				break;

			case 1:
				SelectObject(surface, blueBrush);
				break;

			case 2:
				SelectObject(surface, greenBrush);
				break;

			case 3:
				SelectObject(surface, tealBrush);
				break;

			case 4:
				SelectObject(surface, purpleBrush);
				break;

			case 5:
				SelectObject(surface, yellowBrush);
				break;

			case 6:
				SelectObject(surface, darkGreenBrush);
				break;
			}


			topleftx = startx + blockWidth*i;
			toplefty = starty + blockHeight*j;
			bottomrightx = startx + blockWidth*(i + 1);
			bottomrighty = starty + blockHeight*(j + 1);

			Rectangle(surface, topleftx, toplefty, bottomrightx, bottomrighty);
			
		}
	}



	//tidy up

	DeleteObject(redBrush);
	DeleteObject(blueBrush);
	DeleteObject(greenBrush);
	DeleteObject(tealBrush);
	DeleteObject(purpleBrush);
	DeleteObject(yellowBrush);
	DeleteObject(darkGreenBrush);


}

