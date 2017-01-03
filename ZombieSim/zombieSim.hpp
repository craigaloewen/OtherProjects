#ifndef FLOODIT_HPP
#define FLOODIT_HPP

#include <list>
#include <iostream>
#include <ctime>
#include <cmath>
#include <stdlib.h>

class creature {
	
	public: 
		int x,y;
		int id;
		int creatureNum;
		int hp;
		unsigned int moveSpeed;
		unsigned int attackSpeed;
		unsigned int lastAttackTime;
		unsigned int lastMoveTime;
		unsigned int runHp;
		unsigned short hitChance; 
		unsigned int damage;
		short moveList[5];

		creature(int inx, int iny, int &numCreatures) {
			x = inx;
			y = iny;
			id = 999;
			moveSpeed = 100;
			attackSpeed = 100; 
			hp = 100;
			runHp = 100;
			hitChance = 100;
			damage = 100;
			lastAttackTime = 0; 
			lastMoveTime = 0;
			creatureNum = numCreatures;
			numCreatures++;
			moveList[5] = {0};
		}
		
		creature() {
			x = 0;
			y = 0;
			id = 999;
		}
	
};

class human: public creature 
{

	public: 
		int z;
		human(int inx, int iny, int &numCreatures) {
			x = inx;
			y = iny;
			id = 3; 
			moveSpeed = 100;
			attackSpeed = 50; 
			hp = 100;
			runHp = 20;
			hitChance = 80;
			damage = 5;
			lastAttackTime = 0; 
			lastMoveTime = 0;
			creatureNum = numCreatures;
			numCreatures++;
			moveList[5] = {0};
		}
		
		
	
};

class zombie: public creature
{

	public:
		int z;
		
		zombie(int inx, int iny, int &numCreatures) {
			x = inx;
			y = iny;
			id = 4;
			moveSpeed = 300;
			attackSpeed = 100; 
			hp = 300;
			runHp = 0;
			hitChance = 40;
			damage = 10;
			lastAttackTime = 0; 
			lastMoveTime = 0;
			creatureNum = numCreatures;
			numCreatures++;
			moveList[5] = {0};
		}
};





class zombieSim
{

public:
	
	short** arena;
	short** map;
	
	int arenaHeight;
	int arenaWidth;
	
	int numCreatures = 0;
	
	int humanAmount;
	int zombieAmount;
	
	unsigned int simTime;
	
	std::list<creature*> creatureList;
	
	zombieSim(int x, int y) {
		
		arenaHeight = y; 
		arenaWidth = x;
		humanAmount = 0;
		zombieAmount = 0;
		simTime = 0;
		
		arena = new short*[x];
		map = new short*[x];
		for (int i = 0; i < x; i++) {
			arena[i] = new short[y];
			map[i] = new short[y];
		}
		for (int i = 0; i < x; i++) {
			for (int j = 0; j < y; j++) {
				arena[i][j] = 0;
				map[i][j] = 0;
			}
		}
		srand(time(NULL));
	}
	
	void printArena();
	void creatureAction(creature* inCreature);
	void creatureMove(creature* inCreature);
	void modifyMoveProbabilityObstacles(creature* inCreature, short moveList[]);
	void modifyMoveProbabilityPathFinding(creature* inCreature, short moveList[]);
	bool creatureMoveCheck(creature* inCreature);
	bool enemyIsNear(creature* inCreature);
	void creaturePathGet(creature* inCreature,short moveList[]);
	int findNearestCreature(creature* inCreature, unsigned short searchId);
	
	int encodeBoardValue(int i, int j);
	void decodeBoardValue(int decodeVal, int &i, int &j);
	
	void makeObstacleArena();
	
	void creatureAttack(creature* inCreature);
	creature* findTargetCreature(creature* inCreature);
	
	bool checkVictory();
	
	void addHumans(int inx, int iny, int amount);
	void addZombies(int inx, int iny, int amount);
	
	void updateArena();
	
	void tick();
	
	
	
	
	
	
	
	
	
  
private:

  
};

#endif  //WORD_HPP
