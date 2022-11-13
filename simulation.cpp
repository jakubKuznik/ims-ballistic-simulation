// Solution for VUT FIT IMS project: Simulation of balistic weapons 10.11.2022
// File:        simulation.cpp
// Authors:     Vojtech Tom Hezcko, Jakub Kuzník, 
// Organization: BUT FIT

/* execution examples:  
 
 ./simulation moneyA offensive:deffensiveA moneyB offensive:deffensiveB  
 ./simulation -ma 10000 -ra 10:50 -mb 100000 -rb 1:2
*/


//#include <simlib.h>
#include <getopt.h>
#include <iostream>
#include "simulation.hpp"
#include <list>
#include <string.h>

using namespace std;

/* GLOBAL VARIABLES */
int t; //simulation time 


/** Classes ************************************************
*                  ----------                 ---------    *
*                  | Weapon |                 | State |    *
*                  ----------                 ---------    *
*                  |        |                              *
*  -------------------    -------------------              *
*  | DefensiveWeapon |    | OffensiveWeapon |              *
*  -------------------    -------------------              *
************************************************************/





/**
 * @brief class Weapon is parent of DefensiveWeapon and OffensiveWeapon 
 */
class Weapon{

  string name; 
  int price;     
  int priceCartridge; // todo smazat komentar - cena za naboj 
  int shotsNumber;
  int shotsPMinute;
  int destruction;
  
  // ANTI_DRONE, ANTI_VEHICLE , ANTI_HELICOPTER, ANTI_ROCKET 
  // DRONE, ATTACKING_VEHICLE, HELICOPTER, ROCKET 
  char type;  

  public:
    
    /**
     * @brief Construct a new Weapon object
     */
    Weapon(string n, int p, int pC, \
          int sN, int sPM, int d, char t){
      name            = n;
      price           = p;
      priceCartridge  = pC;
      shotsNumber     = sN;
      shotsPMinute    = sPM;
      destruction     = d;
      type            = t;
    }

    /**
     * @brief 
     */
    void foo(){
      cout << "kk" << endl;
    }
};

/**
 * @brief Defensive Weapon is weapon that is used for defense on your area.
 *          For example drone is flying over your area -> 
 *                 -> u will activate defensive system  
 */
class DefensiveWeapon : private Weapon{

  // 0-100
  char defenseProbability; 
  
  public:
    
    /**
     * @brief Construct a new Defensive Weapon object
     */
    DefensiveWeapon(string n, int p, int pC, int sN, \
      int sPM, int d, char t) : Weapon(n, p, pC, sN, sPM, d, t){
      printf("kk");
    }

    /**
     * @brief 
     */
    void soo(){
      cout << "soo" << endl;
    }

};

/**
 * @brief Offensive weapon is weapon that is used for dealing damage to enemy.
 *          For example sending rockets to enemy area 
 */
class OffensiveWeapon: private Weapon{
  
  char type;  

  public:
    
    /**
     * @brief Construct a new Defensive Weapon object
     */
    OffensiveWeapon(string n, int p, int pC, int sN, \
      int sPM, int d, char t) : Weapon(n, p, pC, sN, sPM, d, t){
      printf("dd");
    }

    /**
     * @brief 
     */
    void qoo(){
      cout << "soo" << endl;
    }

};

/**
 * @brief Class State represent one state with it money and weapons. 
 */
class State{

  // In dollars for this simulation 
  int money;
  int moneyLost;
  int moneyDestroyed;

  // How do you buy weapons 2:1 ... 
  int offRatio;
  int defRatio;

  string name;    

  // In which rate is state buying offensive/defensive weapons.  
    // [antiDrone, antiVehicle, antiHelicopter, antiRockets]
  int rateOffensive[4] = {10,1,2,30};
    // [drone, attackingVehicle, helicopter, rockets]
  int rateDeffensive[4] = {5,1,2,30}; 

  
  list<OffensiveWeapon> offWeapons[4];
  list<DefensiveWeapon> defWeapons[4];

  public:
    /**
     * @brief Constructor
     * example State(10000000, ) 
     */
    State(int m, int oRatio, int dRatio, string n){
      money           = m;
      offRatio        = oRatio;
      defRatio        = dRatio;
      name            = n; 
      moneyLost       = 0;
      moneyDestroyed  = 0; 
    }

    void buyWeapons(){
      cout << "buying weapons" << endl;
    }

    void debugState(){
      cerr << name << endl;
      cerr << "..money: ........... " << money << endl;
      cerr << "..money lost: ...... " << moneyLost << endl;
      cerr << "..money destroyed: . " << moneyDestroyed << endl;
      cerr << "..ratio: ........... " << offRatio << ":" << defRatio << endl;

      // TODO - print weapon list 
    }
};

/**
 * @brief Arg parser that returns int[6] 
 * 
 * @param argc 
 * @param argv 
 * @return int[moneyA, offensiveRatioA, deffensiveRatioA, moneyB, offensiveRatioB, deffensiveRatioB] 
 * 
 * example:
 * ./simulation -ma 10000 -ra 10:50 -mb 100000 -rb 1:2
 */
void argParse(int argc, char **argv, int set[6]){
  
  char * temp;  

  for (int i = 1; i < argc; i++){
    if (strcmp(argv[i],"-ma") == 0){
      set[MONEY_A] = stoi(argv[++i]);
    }
    else if (strcmp(argv[i],"-mb") == 0){
      set[MONEY_B] = stoi(argv[++i]);
    }
    else if (strcmp(argv[i],"-ra") == 0){
      temp = strtok(argv[++i], ":");
      set[OFF_RATIO_A] = stoi(temp);
      temp = strtok(NULL, ":");
      set[DEF_RATIO_A] = stoi(temp);
    }
    else if (strcmp(argv[i],"-rb") == 0){
      temp = strtok(argv[++i], ":");
      set[OFF_RATIO_B] = stoi(temp);
      temp = strtok(NULL, ":");
      set[DEF_RATIO_B] = stoi(temp);
    }
    else{
      goto errorArgs;
    }
  }

  for (int i = 0; i < 6; i++){
    if (set[i] == 0)
      goto errorArgs;
  }

  return;

errorArgs:
  cerr << "Error bad args" << endl;
  exit(1);
}


int main(int argc, char **argv){
  int set[6] = {0,0,0,0,0,0};
  argParse(argc, argv, set);

  // init
  State * stateA = new State(set[0], set[1], set[2], "stateA");
  State * stateB = new State(set[3], set[4], set[5], "stateB");
  

  stateA->debugState();
  stateB->debugState();

  // buy weapons 

  // run simulation   

  return 0;

}