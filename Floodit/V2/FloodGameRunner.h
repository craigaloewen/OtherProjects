#ifndef FLOODGAMERUNNER_H
#define FLOODGAMERUNNER_H


#include "FloodAIController.h"
#include "CGenAlg.h"
#include "CParams.h"

class FloodGameRunner {
	
	public:
		
		int numberOfGames;
		int numberActiveGames;
		
		int ticks;
		
		vector<FloodAIController> floodAIGame; 
		
		vector<int> activeFloodGames;
		
		vector<SGenome> vecPopulation;
		
		CGenAlg* genAlg_p;
		
		int numWeightsInNN;
		
		
		
		
		FloodGameRunner(int numGames);
		
		bool runGames();
		
		bool updateGames();
		
		bool removeGame(vector<int>::iterator &activeIterator);
		
		void reset();
		
		
		
	
	
	
};

#endif //FLOODGAMERUNNER_H
