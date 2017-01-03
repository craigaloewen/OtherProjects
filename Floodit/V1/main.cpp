#include <iostream>
#include <ctime>
#include <cmath>
#include <stdlib.h>

#include "floodIt.hpp"
#include "BinarySearchTree.hpp"

using namespace std;


BinarySearchTree tree1;
floodIt game1;

int turns = 0;
int minturns = 1000;
double averageturn = 0; 
int TESTNUM = 1000;

int printNUM = TESTNUM/10;

int colorpick = 0; 


void doManualTurn(int selection) {
	game1.makeTurn(selection);
}

void bottomRightTurn() {
	colorpick = game1.findBottomRightColor();
	game1.makeTurn(colorpick);
}

void mostTouchingTurn() {
	//game1.printBoard();
	colorpick = game1.findMostTouching();
	game1.makeTurn(colorpick);
}

void playMultipleGamesMostTouching() {
	
	turns = 0;
	averageturn = 0; 
	minturns = 1000;
	for (int i = 0; i < TESTNUM; i++) {
	
		if (i % printNUM == 0) {
			cout << "Done " << i/printNUM*10 << "% of " << TESTNUM << endl;
		}
		
		turns = 0;
		game1.randomize();
	
		while (!game1.isWon()) {
			mostTouchingTurn();
			turns++;
		}
		
		if (turns < minturns) {
			minturns = turns;
		}
		
		averageturn += turns * 1.0 / TESTNUM;
	}
	
	cout << "Minturns: " << minturns << " Average: " << averageturn << endl;
	
}

void playMultipleGamesBottomRight() {
	
	turns = 0;
	minturns = 1000;
	averageturn = 0;
	for (int i = 0; i < TESTNUM; i++) {
	
		if (i % printNUM == 0) {
			cout << "Done " << i/printNUM << endl;
		}
		
		turns = 0;
		game1.randomize();
	
		while (!game1.isWon()) {
			bottomRightTurn();
			turns++;
		}
		
		if (turns < minturns) {
			minturns = turns;
		}
		averageturn += turns * 1.0 / TESTNUM;
	}
	
	cout << "Minturns: " << minturns;
	cout << "Minturns: " << minturns << " Average: " << averageturn << endl;
	
}

void playHumanGame() {
	
	turns = 0;
	colorpick = 0;
	while (!game1.isWon()){
		game1.printBoard();
		cout << game1.findMostTouching() << endl;
		cin >> colorpick;
		doManualTurn(colorpick);
		turns++;
	}
	cout << "Done in: " << turns;
	
	
}

int main() {

	srand(time(NULL));
	
	clock_t t1,t2;
	t1=clock();
	
	game1.randomize();
	//playHumanGame();
	playMultipleGamesMostTouching();

	t2 = clock();
	
	float diff ((float)t2-(float)t1);
	cout << diff << endl;

	
}
