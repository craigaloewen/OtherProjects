
#include <iostream>

#include "zombieSim.hpp"


using namespace std;


int main() {
	
  //75 11 is max?
  zombieSim sim(20,10);
  //sim.makeObstacleArena();
  
  sim.addHumans(sim.arenaWidth-1,sim.arenaHeight-1,1);
  sim.addZombies(0,0,1);
  
  int input;
  int counter = 0; 
  
  
  while (!sim.checkVictory()) {
  	
  	sim.tick();
  	if ( counter % 20 == 0) {
  		sim.printArena();
  	}
  	
  	counter++;
  	
  }
  
  sim.tick();
  sim.printArena();
  cout << counter << endl;
  
//  for (int i = 0; i < 10000000; i++) {
//  	
//  	sim.tick();
//  	
//  	if ( i % 1000 == 0) {
//  		sim.printArena();
//  	}
//  	
//  	if ( i % 10000 == 0) {
//  		cin >> input;
//  	}
//
//
//  	//cin >> input;
//  	
//  	
//  	
//  }

  //Yes
	
	
	
}
