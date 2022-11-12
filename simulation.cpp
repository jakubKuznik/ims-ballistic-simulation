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
 * @brief TODO
 */
class Weapon{
  int i;
  
  public:
    
    /**
     * @brief Construct a new Weapon object
     * @param i 
     */
    Weapon(int i){
      i = 1; 
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
  
  int j; 
  // [anti_drone, anti_vehicle, anti_helicopter, anti_rockets]
  bool goodAgainst[4];
  
  public:
    
    /**
     * @brief Construct a new Defensive Weapon object
     * @param j 
     */
    DefensiveWeapon(int j) : Weapon(j){
      j = j;
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
  
  // DRONE, ATTACKING_VEHICLE, HELICOPTER, ROCKET 
  char type;  
  int k; 

  public:
    
    /**
     * @brief Construct a new Defensive Weapon object
     * @param j 
     */
    OffensiveWeapon(int k) : Weapon(k){
      k = k;
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
  // ratio [offensive, deffensive]
  int SpendRatio[2]; 
  
  // In which rate is state buying offensive/defensive weapons.  
  int rateOffensive[4];  // [antiDrone, antiVehicle, antiHelicopter, antiRockets]
  int raetDeffensive[4]; // [drone, attackingVehicle, helicopter, rockets]

  
  list<OffensiveWeapon> offWeapons[4];
  list<DefensiveWeapon> defWeapons[4];

  public:
    /**
     * @brief Constructor
     * example State(10000000, ) 
     */
    State(int m, int spendRatio[2]){
      money = m;
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
int * argParse(int argc, char **argv){
  
  int out[6] = {0, 0, 0, 0, 0, 0}; // output variable 
  char * temp;  

  for (int i = 1; i < argc; i++){
    if (strcmp(argv[i],"-ma") == 0){
      out[MONEY_A] = stoi(argv[++i]);
    }
    else if (strcmp(argv[i],"-mb") == 0){
      out[MONEY_B] = stoi(argv[++i]);
    }
    else if (strcmp(argv[i],"-ra") == 0){
      temp = strtok(argv[++i], ":");
      out[OFF_RATIO_A] = stoi(temp);
      temp = strtok(NULL, ":");
      out[DEF_RATIO_A] = stoi(temp);
    }
    else if (strcmp(argv[i],"-rb") == 0){
      temp = strtok(argv[++i], ":");
      out[OFF_RATIO_B] = stoi(temp);
      temp = strtok(NULL, ":");
      out[DEF_RATIO_B] = stoi(temp);
    }
    else{
      goto errorArgs;
    }
  }


  for (int i = 0; i < 6; i++)
    cout << out[i] << " ";

  return out; 

errorArgs:
  cerr << "Error bad args" << endl;
  exit(1);
}

int main(int argc, char **argv){

  argParse(argc, argv);

  // init
   
  // buy weapons 

  // run simulation   

  return 0;

}