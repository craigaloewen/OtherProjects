#ifndef FLOODIT_HPP
#define FLOODIT_HPP


#include <iostream>
#include <cstdlib>
#include <cmath>
#include <stdlib.h>
#include <ctime>
#include <algorithm>
#include <vector>

#include "CParams.h"

#include "BinarySearchTree.hpp"

#define HEIGHT 12
#define WIDTH 12
#define COLORNUM 7




class floodIt
{

public:
	
	floodIt();
	int makeTurn(int colorNum);
	int randomize();
	void printBoard();
	bool isWon();
	void decodeTreeValue(int treeVal, int &i, int &j);
	int encodeTreeValue(int i, int j);
	void getFloodTiles(BinarySearchTree* tree,int i,int j);
	void getFloodTiles(BinarySearchTree* tree,BinarySearchTree* touching,int i,int j);
	int findBottomRightColor();
	int findMostTouching();
	int findLeastUsedColor();
	int findMostUsedColor();
	void makeObstacles();
	int countSolvedTiles();

	void Render(HDC &surface, int startx, int starty, int endx, int endy);
	
	void solve();
	
	
	
	int getLeftCornerDistance(int i, int j);
	
	void copyBoard(int newBoard[][HEIGHT]);
	
	int getTurnNumber() { return turnNumber; }
	
	int colorChosenAmount[COLORNUM];
  
private:
	
	int board[66][66];

	
	int turnNumber;
	
	int boardHeight;
	int  boardWidth;
	
	BinarySearchTree* internalTree;
	
	

	
  
};

#endif  //WORD_HPP
