#ifndef FLOODGAMERUNNER_H
#define FLOODGAMERUNNER_H


#include "FloodAIController.h"
#include "CGenAlg.h"
#include "CParams.h"

class FloodGameRunner {
	
	public:
		
		int numberOfGames;
		int numberActiveGames;
		
		bool running;

		int ticks;
		int generations;
		
		vector<FloodAIController> floodAIGame; 
		
		vector<int> activeFloodGames;
		
		vector<SGenome> vecPopulation;
		
		CGenAlg* genAlg_p;
		
		int numWeightsInNN;
		
		
		
		
		FloodGameRunner();
		
		bool runGames();
		
		bool updateGames();
		
		bool removeGame(vector<int>::iterator &activeIterator);
		
		void Reset();
		

		void Render(HDC &surface);

		void ToggleStarted();

		bool Started();

		void tickIncrease();
		
		
	
	
	
};

#endif //FLOODGAMERUNNER_H
