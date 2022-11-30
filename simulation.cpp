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
#include <algorithm>

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

// TODO 200 iq zanedbat cas raket 

/**
 * @brief class Weapon is parent of DefensiveWeapon and OffensiveWeapon 
 */
class Weapon{

  string name; 
  int price;     
  int priceCartridge; // todo smazat komentar - cena za naboj 
  int destruction;
  
  // ANTI_DRONE, ANTI_VEHICLE , ANTI_HELICOPTER, ANTI_ROCKET 
  // DRONE, ATTACKING_VEHICLE, HELICOPTER, ROCKET 
  char type;  

  // num of ra
  int cartridge = 0; 

  public:
    
    /**
     * @brief Construct a new Weapon object
     */
    Weapon(string n, int p, int pC, \
          int d, char t){
      name            = n;
      price           = p;
      priceCartridge  = pC;
      destruction     = d;
      type            = t;
    }

    int getPrice(){
      return price;
    }
    
    int getCartridgePrice(){
      return priceCartridge;
    }

    /**
     * @brief 
     */
    void foo(){
      cout << "kk" << endl;
    }

    string getName(){
      return this->name;
    }

    /**
     * @brief buy weapon cartridge 
     * 
     * @return int how much did it cost.
     */
    int buyCartridge(){
      cartridge++;
      return priceCartridge;
    }

};

/**
 * @brief Defensive Weapon is weapon that is used for defense on your area.
 *          For example drone is flying over your area -> 
 *                 -> u will activate defensive system  
 */
class DefensiveWeapon : public  Weapon{

  // DRONE, VEHICLE, HELICOPTER, ROCKETS
  bool goodAgainst[4];
  
  // 0-100
  char defenseProbability[4]; 
  
  public:
    
    /**
     * @brief Construct a new Defensive Weapon object
     */
    DefensiveWeapon(bool gA[], char dP[], string n, int p, int pC, \
              int d, char t) : Weapon(n, p, pC, d, t){

      goodAgainst[ANTI_DRONE]       = gA[ANTI_DRONE];
      goodAgainst[ANTI_VEHICLE]     = gA[ANTI_VEHICLE];
      goodAgainst[ANTI_HELICOPTER]  = gA[ANTI_HELICOPTER];
      goodAgainst[ANTI_ROCKETS]     = gA[ANTI_ROCKETS];

      defenseProbability[ANTI_DRONE]      = dP[ANTI_DRONE];
      defenseProbability[ANTI_VEHICLE]    = dP[ANTI_VEHICLE];
      defenseProbability[ANTI_HELICOPTER] = dP[ANTI_HELICOPTER];
      defenseProbability[ANTI_ROCKETS]    = dP[ANTI_ROCKETS];
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
class OffensiveWeapon: public  Weapon{

  public:
    /**
     * @brief Construct a new Defensive Weapon object
     */
    OffensiveWeapon(string n, int p, int pC, \
      int d, char t) : Weapon(n, p, pC, d, t){
    }

    /**
     * @brief 
     */
    void qoo(){
      cout << "soo" << endl;
    }

    // TODO do damage 
    // with p=0.5 ... this kind of damage .... etc...

};

/**
 * @brief Class State represent one state with it money and weapons. 
 */
class State{

  // In dollars for this simulation 
  unsigned long long money;
  unsigned long long moneyLost;
  unsigned long long moneyDestroyed;

  // How do you buy weapons 2:1 ... 
  unsigned long long offRatio;
  unsigned long long defRatio;

  string name;    

  // In which rate is state buying offensive/defensive weapons.  
  // [drone, attackingVehicle, helicopter, rockets]
  int rateOffensive[4] = {10,1,2,30};
  // [antiDrone, antiVehicle, antiHelicopter, antiRockets]
  int rateDeffensive[4] = {5,1,2,300}; 
  
  list<OffensiveWeapon*> offWeapons;
  list<DefensiveWeapon*> defWeapons;

  int javelin   = 0;
  int ironDome  = 0;

  int cheapestWeapon = 333000;

  public:
    /**
     * @brief Constructor
     * example State(10000000, ) 
     */
    State(unsigned long long m, unsigned long long oRatio, \
     unsigned long long dRatio, string n){
      cerr << ".......money: ........... " << money << endl;
      money           = m;
      cerr << ".......money: ........... " << m << endl;
      cerr << ".......money: ........... " << money << endl;
      offRatio        = oRatio;
      defRatio        = dRatio;
      name            = n; 
      moneyLost       = 0;
      moneyDestroyed  = 0; 

      this->countRatios(oRatio, dRatio);
      this->initWeapons();
    }

    /**
     * @brief Count in what rate should we buy each weapon. 
     * 
     * will consider offRatio and defRatio and recalculate rateOffensive[] and rateDeffensive[]
     *  
     */
    void countRatios(unsigned long long offRatio, unsigned long long defRatio){
      // for better accuracy we need to multiply each number with something big 
      //   and then divide by ratio 
      int big = 100; 
      for(int i = 0; i < size(rateDeffensive); i++){
        rateDeffensive[i] = (rateDeffensive[i] * big) / defRatio; 
        rateOffensive[i] = (rateOffensive[i] * big) / offRatio; 
      }
    }

    /**
     * @brief Init existing weapons here.  
     */
    void initWeapons(){
      /*** Offensive weapons */
      OffensiveWeapon * oW = new OffensiveWeapon("Javelin", 245000, 78000, 760, ROCKET);
      offWeapons.push_front(oW);


      /*** Defensive weapons */
      bool b[4] = {false, true, true, false}; char p[4] = {0, 0, 0, 90};
      DefensiveWeapon * dW = new DefensiveWeapon(b, p ,"Iron Dome", 50000000, 125000, 0, ANTI_ROCKETS);
      defWeapons.push_front(dW);

    }

    /**
     * @brief find Defensive weapon using name. 
     * 
     * @param name 
     * @return DefensiveWeapon* 
     */
    DefensiveWeapon * findWeaponDef(string name){
      list<DefensiveWeapon*>::iterator it;
      string temp;
      for (it = defWeapons.begin(); it != defWeapons.end(); ++it){
        temp = (*it)->getName();
        if (temp == name)
          return *it;
      }
    }

    /**
     * @brief find offensive weapon using name. 
     * 
     * @param name 
     * @return DefensiveWeapon* 
     */
    OffensiveWeapon * findWeaponOff(string name){
      list<OffensiveWeapon*>::iterator it;
      string temp;
      for (it = offWeapons.begin(); it != offWeapons.end(); ++it){
        temp = (*it)->getName();
        if (temp == name)
          return *it;
      }
    }
    
    void buyWeapons(){
      cout << "buying weapons" << endl;
      cout << findWeaponDef("Iron Dome") << endl;

      DefensiveWeapon * defWeapon;
      OffensiveWeapon * offWeapon;

      // ratios are count for each weapon. We can use modulo function for estabilishing good buy. 
      int forModulo = 0;   
      while (money > cheapestWeapon){
        // offensive 
        if ((forModulo % rateOffensive[DRONE]) == 0){
          ;
        }
        if ((forModulo % rateOffensive[ATTACKING_VEHICLE]) == 0){
          ;
        }
        if ((forModulo % rateOffensive[HELICOPTER]) == 0){
          ;
        }
        if ((forModulo % rateOffensive[ROCKET]) == 0){
          cout << "J ";
          cout << forModulo << " " << rateOffensive[ROCKET] << endl;
          
          offWeapon = findWeaponOff("Javelin");

          if ((offWeapon->getCartridgePrice() + offWeapon->getPrice()) > money)
            break;

          if (javelin < MAX_JAVELIN){
            money = money - offWeapon->getPrice();
          }
          money = money - offWeapon->buyCartridge();
          this->javelin++; 

        }
        // deffensive 
        if ((forModulo % rateDeffensive[ANTI_DRONE]) == 0){
          ;
        }
        if ((forModulo % rateDeffensive[ANTI_VEHICLE]) == 0){
          ; 
        }
        if ((forModulo % rateDeffensive[ANTI_HELICOPTER]) == 0){
          ;
        }
        if ((forModulo % rateDeffensive[ANTI_ROCKETS]) == 0){
          cout << "D ";
          cout << forModulo << " " << rateDeffensive[ANTI_ROCKETS] << endl;

          defWeapon = findWeaponDef("Iron Dome");
          if ((defWeapon->getCartridgePrice() + defWeapon->getPrice()) > money)
            break;
          
          
          if (ironDome < MAX_IRON_DOME){
            money = money - defWeapon->getPrice();
          }
          money = money - defWeapon->buyCartridge();
          this->ironDome++; 
        }

        forModulo++;        
      }

      cerr << "Rocket_ratio: ....... " << rateOffensive[ROCKET] << endl;
      cerr << "anti_rocket_ratio: .. " << rateDeffensive[ANTI_ROCKETS] << endl;

    }

    void debugState(){
      cerr << name << endl;
      cerr << "..money: ........... " << money << endl;
      cerr << "..money lost: ...... " << moneyLost << endl;
      cerr << "..money destroyed: . " << moneyDestroyed << endl;
      cerr << "..ratio: ........... " << offRatio << ":" << defRatio << endl;

      cerr << "....Javelin ........ " << javelin << endl;
      cerr << "....Iron Dome ...... " << ironDome << endl;
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
void argParse(int argc, char **argv, unsigned long long set[6]){
  
  char * temp;  

  for (int i = 1; i < argc; i++){
    if (strcmp(argv[i],"-ma") == 0){
      set[MONEY_A] = stoull(argv[++i]);
    }
    else if (strcmp(argv[i],"-mb") == 0){
      set[MONEY_B] = stoull(argv[++i]);
    }
    else if (strcmp(argv[i],"-ra") == 0){
      temp = strtok(argv[++i], ":");
      set[OFF_RATIO_A] = stoull(temp);
      temp = strtok(NULL, ":");
      set[DEF_RATIO_A] = stoull(temp);
    }
    else if (strcmp(argv[i],"-rb") == 0){
      temp = strtok(argv[++i], ":");
      set[OFF_RATIO_B] = stoull(temp);
      temp = strtok(NULL, ":");
      set[DEF_RATIO_B] = stoull(temp);
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
  unsigned long long set[6] = {0,0,0,0,0,0};
  argParse(argc, argv, set);

  // init
  State * stateA = new State(set[0], set[1], set[2], "stateA");
  State * stateB = new State(set[3], set[4], set[5], "stateB");
  

  stateA->debugState();
  stateB->debugState();

    /*
    OffensiveWeapon(string n, int p, int pC, int sN, \
    int sPM, int d, char t) : Weapon(n, p, pC, sN, sPM, d, t){
    */


  // buy weapons 
  stateA->buyWeapons();
  stateB->buyWeapons();
  
  stateA->debugState();
  stateB->debugState();


  // run simulation   

  return 0;

}