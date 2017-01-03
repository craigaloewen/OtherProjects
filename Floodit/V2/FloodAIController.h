#ifndef FLOODAICONTROLLER_H
#define FLOODAICONTROLLER_H

#include <vector>
#include <math.h>>

#include "CNeuralNet.h"
#include "CParams.h"
#include "floodIt.hpp"
#include "iostream"

class FloodAIController {
	
	public:
		
		double fitness;
		
		CNeuralNet AIBrain;
		
		floodIt game;
		
		FloodAIController();
		
		bool makeTurn();
		
		bool Reset();
		
		
		void  PutWeights(vector<double> &w){AIBrain.PutWeights(w);}
		
		
		int getNumberOfWeights()const{return AIBrain.GetNumberOfWeights();}
		
		double calculateFitness();
		
		
		
	
	
	
};

#endif //FLOODAICONTROLLER_H
