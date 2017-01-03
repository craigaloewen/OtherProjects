#include "FloodGameRunner.h"

FloodGameRunner::FloodGameRunner() {
	
	numberOfGames = CParams::iNumGames;
	numberActiveGames = numberOfGames;
	ticks = 0;
	generations = 0;
	running = true;
	
	for (int i = 0; i < numberOfGames; i++) {
		floodAIGame.push_back(FloodAIController());
		activeFloodGames.push_back(i);
	}
	
	
	numWeightsInNN = CParams::iNumInputs;
	
	genAlg_p = new CGenAlg(numberOfGames, CParams::dMutationRate, CParams::dCrossoverRate, numWeightsInNN);
	
	vecPopulation = genAlg_p->GetChromos();
	
	for (int i = 0; i < numberOfGames; i++) {
		floodAIGame[i].PutWeights(vecPopulation[i].vecWeights);
		floodAIGame[i].Reset();
		floodAIGame[i].gameID = i;
	}
	
	
}

bool FloodGameRunner::runGames() {
	bool doneGeneration = false;
	
	 if (running) {
		
		updateGames();
		
		if (activeFloodGames.size() == 0) {
			doneGeneration = true;
		}
		
		if (!(ticks < CParams::maxTurns)) {
			doneGeneration = true;
		}
		
		ticks++;

		if (doneGeneration) {

			vector<int>::iterator activeIterator;

			activeIterator = activeFloodGames.begin();

			for (; activeIterator != activeFloodGames.end(); ) {
				removeGame(activeIterator);
			}



			Reset();
			running = true; 
			generations++;


			// Create new Generation once games are finished
			vecPopulation = genAlg_p->Epoch(vecPopulation);

			for (int i = 0; i < numberOfGames; i++) {
				floodAIGame[i].PutWeights(vecPopulation[i].vecWeights);
			}
			//

			return true;



		}

	}
	
	
	return true;
	
	
	
	
}

void FloodGameRunner::Reset() {
	
	running = false;
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
	
	return true;
	
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

void FloodGameRunner::ToggleStarted() {

	if (running) {
		running = false;
	}
	else {
		running = true;
	}

}

bool FloodGameRunner::Started() {
	return running;
}

void FloodGameRunner::Render(HDC &surface) {

	SelectObject(surface, GetStockObject(HOLLOW_BRUSH));

	//Render all boards
	int startx = 0;
	int starty = 0;
	int endx = 0;
	int endy = 0;

	int numberToDraw = 10;


	int padding = 10;
	int numInRow = 10;
	int areaPBoard = (CParams::WindowWidth - padding*2)/numberToDraw - padding;
	int incrementValue = areaPBoard + padding;

	

	starty = 100;
	endy = starty + areaPBoard;
	startx = padding;
	endx = padding + areaPBoard;
	
	

	for (int i = 0; i < numberToDraw; i++) {

		floodAIGame[i].game.Render(surface, startx,starty,endx,endy);
		startx += incrementValue;
		endx += incrementValue;

	}

	SetBkMode(surface, TRANSPARENT);


	string s = "Generation: " + itos(generations);
	TextOut(surface, 5, 5, s.c_str(), s.size());

	s = "Best Fitness:       " + ftos(genAlg_p->BestFitness());
	TextOut(surface, 5, CParams::WindowHeight - 100, s.c_str(), s.size());

	s = "Average Fitness: " + ftos(genAlg_p->AverageFitness());
	TextOut(surface, 300, CParams::WindowHeight - 100, s.c_str(), s.size());


	s = "Weight[0]:" + ftos(floodAIGame[0].weightList[0]);
	TextOut(surface, 5, CParams::WindowHeight - 130, s.c_str(), s.size());

	s = "Weight[1]:" + ftos(floodAIGame[0].weightList[1]);
	TextOut(surface, 200, CParams::WindowHeight - 130, s.c_str(), s.size());

	s = "Weight[2]:" + ftos(floodAIGame[0].weightList[2]);
	TextOut(surface, 400, CParams::WindowHeight - 130, s.c_str(), s.size());

	s = "Weight[3]:" + ftos(floodAIGame[0].weightList[3]);
	TextOut(surface, 600, CParams::WindowHeight - 130, s.c_str(), s.size());

}


void FloodGameRunner::tickIncrease() {
	ticks++;
}