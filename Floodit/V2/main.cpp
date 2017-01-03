#include <iostream>
#include <ctime>
#include <cmath>
#include <stdlib.h>

#include "FloodGameRunner.h"
#include "CParams.h"

using namespace std;

CParams g_Params;

int main() {

//	srand(time(NULL));
//	
//	clock_t t1,t2;
//	t1=clock();
//	
//	game1.randomize();
//	//playHumanGame();
//	playMultipleGamesMostTouching();
//
//	t2 = clock();
//	
//	float diff ((float)t2-(float)t1);
//	cout << diff << endl;

srand(time(NULL));

FloodGameRunner mainRunner(1);

for (int i = 0; i < 10000; i++) {
	mainRunner.runGames();
}




	
}
