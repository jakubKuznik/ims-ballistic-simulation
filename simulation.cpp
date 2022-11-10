// Solution for VUT FIT IMS project: Simulation of balistic weapons 10.11.2022
// File:        simulation.cpp
// Authors:     Vojtech Tom Hezcko, Jakub Kuzník, 
// Organization: BUT FIT


//#include <simlib.h>
#include <getopt.h>
#include <iostream>
#include "simulation.hpp"

using namespace std;

/* GLOBAL VARIABLES */
int t;




/**********************************************
*                  ----------                 *
*                  | Weapon |                 *
*                  ----------                 *
*                  |        |                 *
*  -------------------    ------------------- *
*  | DefensiveWeapon |    | OffensiveWeapon | *
*  -------------------    ------------------- *
***********************************************/

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
 * @brief TODO
 */
class DefensiveWeapon : private Weapon{
  int j; 
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
 * @brief TODO
 */
class OffensiveWeapon: private Weapon{
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