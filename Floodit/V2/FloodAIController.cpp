#include "FloodAIController.h"

FloodAIController::FloodAIController() {
		
	fitness = 0;
	
}

bool FloodAIController::makeTurn() {
	
	if (game.isWon()) {
		return false;
	}
	
	vector<double> inputs;
	
	inputs.push_back(game.findMostTouching()*1.0);
	inputs.push_back(game.findBottomRightColor()*1.0);
	inputs.push_back(game.findLeastUsedColor()*1.0);
	
	vector<double> outputs = AIBrain.Update(inputs);
	
	int turnInput = round(outputs[0]*7);
	
	game.printBoard();
	std::cout << " Choice: " << turnInput << std::endl; 
	
	game.makeTurn(turnInput);
	
	return true;
	
	
}

bool FloodAIController::Reset() {
	
	fitness = 0;
	
	game.randomize();
	
	return true;
	
}

double FloodAIController::calculateFitness() {
	
	fitness = game.countSolvedTiles()*1.0;
	
	return fitness;
	
	
}


