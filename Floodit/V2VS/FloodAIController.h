#ifndef FLOODAICONTROLLER_H
#define FLOODAICONTROLLER_H

#include <vector>
#include <math.h>

#include "CNeuralNet.h"
#include "CParams.h"
#include "floodIt.hpp"
#include "iostream"

class FloodAIController {
	
	public:
		
		double fitness;

		int gameID; 

		vector<double> weightList;
		
		floodIt game;
		
		FloodAIController();
		
		bool makeTurn();
		
		bool Reset();
		
		
		void  PutWeights(vector<double> &w);
		
		
		int getNumberOfWeights()const{return CParams::iNumInputs;}
		
		double calculateFitness();

		int selectColorRoulette(vector<double> weights);
		
		
		
	
	
	
};

#endif //FLOODAICONTROLLER_H
