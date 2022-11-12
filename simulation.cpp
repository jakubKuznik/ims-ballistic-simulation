// Solution for VUT FIT IMS project: Simulation of balistic weapons 10.11.2022
// File:        simulation.cpp
// Authors:     Vojtech Tom Hezcko, Jakub Kuzník, 
// Organization: BUT FIT

/* execution examples:  
 
 ./simulation money offensive:deffensive  

*/


//#include <simlib.h>
#include <getopt.h>
#include <iostream>
#include "simulation.hpp"
#include <list>

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
  
  // In which rate is state buying offensive/defensive weapons.  
  int rateOffensive[4];  // [antiDrone, antiVehicle, antiHelicopter, antiRockets]
  int raetDeffensive[4]; // [drone, attackingVehicle, helicopter, rockets]

  
  list<OffensiveWeapon> offWeapons[4];
  list<DefensiveWeapon> defWeapons[4];

  public:
    /**
     * @brief Constructor
     * example State(10000000, [1,1,1,3], [4,2,2,1])   
     */
    State(int m, int rateOff[], int rateDeff[]){
      money = m;
    }

};


int argParse(int argc, char **argv){
  cout << argc << " neco " << argv << endl;
}

int main(int argc, char **argv){

  argParse(argc, argv);
  

  cout << "---" << endl;
  cout << HOVNO << endl;
  return 0;

}