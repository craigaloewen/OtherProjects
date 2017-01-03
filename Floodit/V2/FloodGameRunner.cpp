#include "FloodGameRunner.h"

FloodGameRunner::FloodGameRunner(int numGames) {
	
	numberOfGames = numGames;
	numberActiveGames = numberOfGames;
	ticks = 0;
	
	for (int i = 0; i < numGames; i++) {
		floodAIGame.push_back(FloodAIController());
		activeFloodGames.push_back(i);
	}
	
	
	numWeightsInNN = floodAIGame[0].getNumberOfWeights();
	
	genAlg_p = new CGenAlg(numGames, CParams::dMutationRate, CParams::dCrossoverRate, numWeightsInNN);
	
	vecPopulation = genAlg_p->GetChromos();
	
	for (int i = 0; i < numberOfGames; i++) {
		floodAIGame[i].PutWeights(vecPopulation[i].vecWeights);
		floodAIGame[i].Reset();
	}
	
	
}

bool FloodGameRunner::runGames() {
	
	bool runningGames = true;
	
	while (runningGames) {
		
		updateGames();
		
		if (activeFloodGames.size() == 0) {
			runningGames = false;
		}
		
		if (!(ticks < CParams::maxTurns)) {
			runningGames = false;
		}
		
		ticks++;
	}
	
	//Offload the rest 
	
	vector<int>::iterator activeIterator;
	
	activeIterator = activeFloodGames.begin();
	
	for ( ; activeIterator != activeFloodGames.end(); ) {
		removeGame(activeIterator);	
	}
	
	
	std::cout << "Ticks: " << ticks << std::endl;
	
	reset();
	
	for (int i = 0; i < numberOfGames; i++) {
		std::cout << "Game: " << i << std::endl;
		floodAIGame[i].game.printBoard();
	}
	
	
    // Create new Generation once games are finished
	vecPopulation = genAlg_p->Epoch(vecPopulation);
	
	for (int i = 0; i < numberOfGames; i++) {
		floodAIGame[i].PutWeights(vecPopulation[i].vecWeights);
	}	
	//
	
	return true;
	
	
	
	
}

void FloodGameRunner::reset() {
	
	
	ticks = 0;
	for (int i = 0; i < numberOfGames; i++) {
		floodAIGame[i].Reset();
		activeFloodGames.push_back(i);
	}
	
	
}

bool FloodGameRunner::removeGame(vector<int>::iterator &activeIterator) {
	
	vecPopulation[(*activeIterator)].dFitness = floodAIGame[(*activeIterator)].calculateFitness();
	std::cout << "Removing Game: " << (*activeIterator) << " Fitness: " << floodAIGame[(*activeIterator)].fitness << std::endl;
	activeIterator = activeFloodGames.erase(activeIterator);
	
	
	
}

bool FloodGameRunner::updateGames() {	

	vector<int>::iterator activeIterator;
	
	activeIterator = activeFloodGames.begin();
	
	for ( ; activeIterator != activeFloodGames.end(); ) {
		
		if (!floodAIGame[(*activeIterator)].makeTurn()) {
			removeGame(activeIterator);
		} else {
			++activeIterator;
		}
		
		
	}
	
	return true;

	
	
}


