#include "FloodAIController.h"

FloodAIController::FloodAIController() {
		
	fitness = 0;
	gameID = 0;

	
	
}

void  FloodAIController::PutWeights(vector<double> &w) {

	weightList = w;

}

int FloodAIController::selectColorRoulette(vector<double> weights) {

	double slice = (double)(RandFloat() * CParams::iNumOutputs);

	double totalSum = 0;

	int chosenVal = 0;

	for (int i = 0; i < CParams::iNumOutputs; i++) {

		totalSum += weights[i];

		if (totalSum >= slice) {

			chosenVal = i;
			break;

		}

	}

	switch (chosenVal) {

	case 0:
		return game.findMostTouching();
		break;

	case 1:
		return game.findBottomRightColor();

	case 2: 
		return game.findMostUsedColor();

	case 3: 
		return game.findLeastUsedColor();


	}

}

bool FloodAIController::makeTurn() {

	if (game.isWon()) {
		return false;
	}
	
	int turnInput = selectColorRoulette(weightList);

	
	game.makeTurn(turnInput);
	
	return true;
	
	
}

bool FloodAIController::Reset() {
	
	fitness = 0;
	
	game.randomize();
	
	return true;
	
}

double FloodAIController::calculateFitness() {
	
	if (game.isWon()) {
		fitness = 1000;
	} else {
		fitness = game.countSolvedTiles()*1.0;
	}


	
	return fitness;
	
	
}


