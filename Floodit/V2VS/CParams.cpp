#include "CParams.h"


//because we will always be loading in the settings from an ini file
//we can just initialize everything to zero
double CParams::dPi                 = 3.14159265358979;
double CParams::dHalfPi             = dPi / 2;
double CParams::dTwoPi              = dPi * 2;
int CParams::WindowWidth            = 900;
int CParams::WindowHeight           = 400;
int CParams::iFramesPerSecond       = 0;
int CParams::iNumInputs             = 4;
int CParams::iNumOutputs            = 4;
int CParams::iNumGames              = 50;
double CParams::dCrossoverRate      = 0.7;
double CParams::dMutationRate       = 0.3;
double CParams::dMaxPerturbation    = 0.2;
int CParams::iNumElite              = 4; //4
int CParams::iNumCopiesElite        = 1;
int CParams::maxTurns               = 15;


  
  
