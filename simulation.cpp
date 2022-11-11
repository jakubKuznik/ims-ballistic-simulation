// Solution for VUT FIT IMS project: Simulation of balistic weapons 10.11.2022
// File:        simulation.cpp
// Authors:     Vojtech Tom Hezcko, Jakub Kuzník, 
// Organization: BUT FIT

/* execution examples:  
 
 ./simulation 70:30 30:70

*/


//#include <simlib.h>
#include <getopt.h>
#include <iostream>
#include "simulation.hpp"

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
 * @brief 
 */
class State{
  
  // TODO - 2:5:1:1 1:5:2:0
  // TODO - obe strany budou kupovat ve stejnem pomeru, ale musim to specifikovat 

  // In dollars for this simulation 
  int money; 

  public:
    /**
     * @brief Constructor  
     */
    State(int m){
      money = m;
    }

};


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


int main(int argc, char** argv){

  

  cout << "---" << endl;
  cout << HOVNO << endl;
  return 0;

}