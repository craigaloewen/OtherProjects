#ifndef FLOODIT_HPP
#define FLOODIT_HPP


#include <iostream>
#include <cstdlib>
#include <cmath>
#include <stdlib.h>
#include <ctime>
#include <algorithm>

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
	void makeObstacles();
	
	int getLeftCornerDistance(int i, int j);
	
	
	
	
  
private:
	
	int board[66][66];
	
	int boardHeight;
	int  boardWidth;
	
	BinarySearchTree* internalTree;
	
	

	
  
};

#endif  //WORD_HPP
