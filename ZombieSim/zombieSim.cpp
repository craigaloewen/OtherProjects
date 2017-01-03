#include "zombieSim.hpp"




using namespace std; 



void zombieSim::printArena() {
	system("cls");
	cout << "----Arena----" << endl;
	for (int j = 0; j < arenaHeight; j++) {
		cout << "|";
		for (int i = 0; i < arenaWidth; i++) {
			
			switch (arena[i][j]) {
				
				case 0:
					cout << " ";
					break;
				case 3:
					cout << "H";
					break;
				case 4:
					cout << "Z";
					break;
				case 10:
					cout << "0";
					break;
				default:
					cout << arena[i][j];
					break;
				
				
			}
		}
		cout << "|" << endl;
	}
	cout << "----End----" << endl;
	
}	

void zombieSim::tick() {
	
	simTime++;
	
	updateArena();
	
	list<creature*>::iterator zp;
	
	for (zp = creatureList.begin(); zp != creatureList.end(); ++zp) {
		creatureAction(*zp);
	}
	
}

void zombieSim::updateArena() {
	
	list<creature*>::iterator zp;
	
	for (int i = 0; i < arenaWidth; i++) {
		for (int j = 0; j < arenaHeight; j++) {
			arena[i][j] = map[i][j];
		}
	}
	
	for (zp = creatureList.begin(); zp != creatureList.end(); ++zp) {
		arena[(*zp)->x][(*zp)->y] = (*zp)->id;
	}
	
}

void zombieSim::makeObstacleArena() {
	
	if (arenaWidth >= 10 && arenaHeight >= 10) {
		
		map[3][3] = 10;
		map[4][3] = 10;
		map[6][3] = 10;
		map[7][3] = 10;
		
		map[3][7] = 10;
		map[4][7] = 10;
		map[6][7] = 10;
		map[7][7] = 10;
		
		map[3][4] = 10;
		map[3][6] = 10;
		
		map[7][4] = 10;
		map[7][6] = 10;
		
		map[8][3] = 10;
		map[2][3] = 10;
		
		
		
	}
	
	
	
	
}


bool zombieSim::enemyIsNear(creature* inCreature) {
	
	updateArena();
	
	int selectx = inCreature->x;
	int selecty = inCreature->y;
	
	short enemyId;
	
	if (inCreature->id == 3) {
		enemyId = 4;
	} else {
		enemyId = 3;
	}
	
	selectx = inCreature->x-1;
	if (selectx >= 0) {
		
		if (arena[selectx][selecty] == enemyId ) {
			return true;
		}
		
		
	}
	selectx = inCreature->x+1;
	if (selectx < arenaHeight ) {
		
		if (arena[selectx][selecty] == enemyId ) {
			return true;
		}
		
	}
	selectx = inCreature->x;
	selecty = inCreature->y-1;
	if (selecty >= 0) {
		
		if (arena[selectx][selecty] == enemyId ) {
			return true;
		}
		
	}
	selecty = inCreature->y+1;
	if (selecty < arenaHeight ) {
		
		if (arena[selectx][selecty] == enemyId ) {
			return true;
		}
			
	}
	
	return false;
	
	
}


bool zombieSim::creatureMoveCheck(creature* inCreature) {
	
	bool enemyNear = enemyIsNear(inCreature);
	
	if (inCreature->hp <= inCreature->runHp) {
		return true;
	}
	
	
	if (enemyNear) {
		return false;
	} else {
		return true;
	}
	
	
	
}

void zombieSim::creatureAction(creature* inCreature) {
	
	updateArena();
	
	if (inCreature->hp <= 0) {
		list<creature*>::iterator zp;

		for (zp = creatureList.begin(); zp != creatureList.end(); ++zp) {
			if ((*zp) == inCreature) {
				creatureList.remove((*zp));
				
				if (inCreature->id == 3) {
					humanAmount--;
				}
				if (inCreature->id == 4) {
					zombieAmount--;
				}
				
				delete inCreature;
				return;
			}
				
		}
	}
	
	
	
	bool wantsToMove = creatureMoveCheck(inCreature);
	
	if ((inCreature->lastMoveTime+inCreature->moveSpeed) < simTime) {
		if (wantsToMove) {
			creatureMove(inCreature);
			inCreature->lastMoveTime = simTime;
			return;
		}
	}
	
	if ((inCreature->lastAttackTime+inCreature->attackSpeed) < simTime) {
		if (!wantsToMove) {
			creatureAttack(inCreature);
			inCreature->lastAttackTime = simTime;
			return;
		}
	}
	
	
}

void zombieSim::addHumans(int inx, int iny, int amount) {
	
	for (int i = 0; i < amount; i++) {
		human* addHuman = new human(inx,iny,numCreatures);
		addHuman->y = iny;
		creatureList.push_front(addHuman);
	}
	
	humanAmount += amount;
	
}

void zombieSim::addZombies(int inx, int iny, int amount) {
	
	for (int i = 0; i < amount; i++) {
		zombie* addZombie = new zombie(inx,iny,numCreatures);
		addZombie->y = iny;
		creatureList.push_front(addZombie);
	}
	
	zombieAmount += amount;
	
}

bool zombieSim::checkVictory() {
	if (humanAmount <= 0 || zombieAmount <= 0) {
		return true;
	}
	return false;
}



void zombieSim::modifyMoveProbabilityObstacles(creature* inCreature, short moveList[]) {
	
	int selectx = inCreature->x;
	int selecty = inCreature->y;
	
	int probDecrease = 1000000;
	
	selectx = inCreature->x-1;
	if (selectx >= 0) {
		
		if (arena[selectx][selecty] >= 3 ) {
			moveList[2] = 0;//moveList[0]/probDecrease;
		}
		
		
	}
	selectx = inCreature->x+1;
	if (selectx < arenaHeight ) {
		
		if (arena[selectx][selecty] >= 3 ) {
			moveList[3] = 0;//moveList[0]/probDecrease;
		}
		
	}
	selectx = inCreature->x;
	selecty = inCreature->y-1;
	if (selecty >= 0) {
		
		if (arena[selectx][selecty] >= 3) {
			moveList[1] = 0;//moveList[1]/probDecrease;
		}
		
	}
	selecty = inCreature->y+1;
	if (selecty < arenaHeight ) {
		
		if (arena[selectx][selecty] >= 3 ) {
			moveList[0] = 0;//moveList[0]/probDecrease;
		}	
	}
	
	
	
	
	
}

void printMoveList(short moveList[]) {
	
	cout << "---MoveList---";
	cout << "D: " << moveList[0] << " U: " <<  moveList[1] << " L: " <<  moveList[2] << " R: " <<  moveList[3] << " S: " <<  moveList[4] << " ----MoveList---" << endl;
	
	
}

creature* zombieSim::findTargetCreature(creature* inCreature) {
	
	short enemyId;
	
	if (inCreature->id == 3) {
		enemyId = 4;
	} else {
		enemyId = 3;
	}
	
	list<creature*>::iterator zp;
	
	for (zp = creatureList.begin(); zp != creatureList.end(); ++zp) {
		
		if ((*zp)->id == enemyId) {
			
			if (((*zp)->x == inCreature->x+1 || (*zp)->x == inCreature->x-1) && (*zp)->y == inCreature->y ) {
				return (*zp);
			}
			
			if (((*zp)->y == inCreature->y+1 || (*zp)->y == inCreature->y-1) && (*zp)->x == inCreature->x ) {
				return (*zp);
			}
			
			
		}
		
		
	}
	
	cout << "We have a problem!" << endl;
	return 0;
	
	
	
}

void zombieSim::creatureAttack(creature* inCreature) {
	
	creature* targetCreature = findTargetCreature(inCreature);
	
	if (targetCreature == 0) {
		return;
	}
	
	unsigned short hitDice = rand() % 100;
	
	if (hitDice <= inCreature->hitChance) {
		targetCreature->hp -= 20;
	}
	
	
	
	
}

void zombieSim::modifyMoveProbabilityPathFinding(creature* inCreature, short moveList[]) {
	
	unsigned short searchId;
	unsigned short nearestCreature;
	
	if (inCreature->id == 3) {
		nearestCreature = 0;
	} else {
		nearestCreature = 22;
	}
	
	
	int distancex, distancey;
	
	decodeBoardValue(nearestCreature,distancex,distancey);
	
	distancex = distancex - inCreature->x;
	distancey = distancey - inCreature->y;
	
	if (moveList[0] != 0) {
		if (distancey > 0) {
			moveList[0] += 1000;
		}
	}
	if (moveList[1] != 0) {
		if (distancey < 0) {
			moveList[1] += 1000;
		}
	}
	if (moveList[2] != 0) {
		if (distancex < 0) {
			moveList[2] += 1000;
		}
	}
	if (moveList[3] != 0) {
		if (distancex > 0) {
			moveList[3] += 1000;
		}
	}
}

void zombieSim::creatureMove(creature* inCreature) {
	creaturePathGet(inCreature,inCreature->moveList);
	modifyMoveProbabilityObstacles(inCreature, inCreature->moveList);
	//modifyMoveProbabilityPathFinding(inCreature,inCreature->moveList);
	
	
	short totalProbability = inCreature->moveList[0] + inCreature->moveList[1] + inCreature->moveList[2] + inCreature->moveList[3] + inCreature->moveList[4];
	
	
	
	short moveNum = rand() % totalProbability;
	int moveSum = -1;
	
	
	moveSum += inCreature->moveList[0];
	if (moveNum <= moveSum) {
		inCreature->y++;
		return;
	}
	
	moveSum += inCreature->moveList[1];
	if (moveNum <= moveSum) {
		inCreature->y--;
		return;
	}
	
	moveSum += inCreature->moveList[2];
	if (moveNum <= moveSum) {
		inCreature->x--;
		return;
	}
	
	moveSum += inCreature->moveList[3];
	if (moveNum <= moveSum) {
		inCreature->x++;
		return;
	}
	
	moveSum += inCreature->moveList[4];
	if (moveNum <= moveSum) {
		return;
	}
}

void zombieSim::creaturePathGet(creature* inCreature, short moveList[]) {
	 
	//Down Up left Right
	if ((inCreature->x-1) >= 0) {
		moveList[2] = 100;
	}
	if ((inCreature->y-1) >= 0) {
		moveList[1] = 100;
	}
	if ((inCreature->x+1) < arenaWidth) {
		moveList[3] = 100;
	}
	if ((inCreature->y+1) < arenaHeight) {
		moveList[0] = 100;
	}
	moveList[4] = 1;
}


void zombieSim::decodeBoardValue(int decodeVal, int &i, int &j) {
	i = decodeVal % arenaWidth;
	j = decodeVal / arenaHeight;	
}

int zombieSim::encodeBoardValue(int i, int j) {
	return j*arenaWidth + i;
}

bool doesListContain(list<int>* searchList, int val) {
	
	list<int>::iterator zp;
	
	for (zp = searchList->begin(); zp != searchList->end(); zp++) {
		if ((*zp) == val) {
			return true;
		}
	}
	return false;	
}


int zombieSim::findNearestCreature(creature* inCreature, unsigned short searchId) {
	
	list<int> searchList; 
	list<int> visitedList;
	
	int visitor; 
	int xcord,ycord;
	
	searchList.push_front(encodeBoardValue(inCreature->x,inCreature->y));
	
	while (searchList.size() > 0) {
		
		visitor = searchList.front();
		visitedList.push_back(visitor);
		searchList.pop_front();
		
		
		decodeBoardValue(visitor,xcord,ycord);
		
		
		
		
		if (arena[xcord][ycord] == searchId) {
			return visitor;
		}
		
		
		if ((xcord-1) >= 0) {
			
			if (!doesListContain(&visitedList,encodeBoardValue(xcord-1,ycord))) {
				searchList.push_back(encodeBoardValue(xcord-1,ycord));
			}		
			
		}
		if ((ycord-1) >= 0) {
			
			if (!doesListContain(&visitedList,encodeBoardValue(xcord,ycord-1))) {
				searchList.push_back(encodeBoardValue(xcord,ycord-1));
			}
			
		}
		if ((xcord+1) < arenaWidth) {
			
			if (!doesListContain(&visitedList,encodeBoardValue(xcord+1,ycord))) {
				searchList.push_back(encodeBoardValue(xcord+1,ycord));
			}

			
		}
		if ((ycord+1) < arenaHeight) {
			
			if (!doesListContain(&visitedList,encodeBoardValue(xcord,ycord+1))) {
				searchList.push_back(encodeBoardValue(xcord,ycord+1));
			}
			
		}
	}
	
	cout << "PATH problem!" << endl;
	return 0;
	
	
}



