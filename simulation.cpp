// Solution for VUT FIT IMS project: Simulation of balistic weapons 10.11.2022
// File:        simulation.cpp
// Authors:     Vojtech Tom Hezcko, Jakub Kuzník, 
// Organization: BUT FIT

/*  Output format on stdin: 
      Name;MoneyBegin;MoneyLost;MoneyDestroyed;DefRatio;OffRatio

    all the logs are on stderr

*/

/* execution examples:  
 ./simulation moneyA offensive:deffensiveA moneyB offensive:deffensiveB  
 ./simulation -ma 1900000000 -ra 3:1 -mb 1900000000 -rb 1:1
 
 ./simulation -ma 10000 -ra 10:50 -mb 100000 -rb 1:2
 ./simulation -ma 10000 -ra 10:50 -mb 100000 -rb 1:2
*/

#include "simulation.hpp"

using namespace std;


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
  long long unsigned price;     
  long long unsigned priceCartridge; // todo smazat komentar - cena za naboj 
  int destruction;
  
  // ANTI_DRONE, ANTI_VEHICLE , ANTI_HELICOPTER, ANTI_ROCKET 
  // DRONE, ATTACKING_VEHICLE, HELICOPTER, ROCKET 
  char type;  

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

    long long unsigned getPrice(){
      return price;
    }
    
    long long unsigned getCartridgePrice(){
      return priceCartridge;
    }

    int getCartridge(){
      return cartridge;
    }

    void decCartirdge(){
      cartridge--;
    }

    int getDestruction(){
      return destruction;
    }

    string getName(){
      return this->name;
    }

    /**
     * @brief buy weapon cartridge 
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

    char getProbAgainstDrone() { return defenseProbability[0]; }

    char getProbAgainstVehicle() { return defenseProbability[1]; }

    char getProbAgainstHelicopter() { return defenseProbability[2]; }

    char getProbAgainstRockets() { return defenseProbability[3]; }
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

};

/**
 * @brief Class State represent one state with it money and weapons. 
 */
class State{

  // In dollars for this simulation 
  unsigned long long moneyBegin;
  unsigned long long money;
  unsigned long long moneyLost;
  unsigned long long moneyDestroyed;
  unsigned long long moneySaved;

  // How do you buy weapons 2:1 ... 
  unsigned long long offRatio;
  unsigned long long defRatio;

  string name;    

  // In which rate is state buying offensive/defensive weapons.  
  // [drone, attackingVehicle, helicopter, rockets]
  int rateOffensive[4] = {25,40,50,10};
  // [antiDrone, antiVehicle, antiHelicopter, antiRockets]
  int rateDeffensive[4] = {50,40,100,50}; 
  
  list<OffensiveWeapon*> offWeapons;
  list<DefensiveWeapon*> defWeapons;

  long long unsigned cheapestWeapon = 333000;

  public:
    /**
     * @brief Constructor
     * example State(10000000, ) 
     */
    State(unsigned long long m, unsigned long long oRatio, \
     unsigned long long dRatio, string n){
      money           = m;
      moneyBegin      = m;
      offRatio        = oRatio;
      defRatio        = dRatio;
      name            = n; 
      moneyLost       = 0;
      moneyDestroyed  = 0;
      moneySaved      = 0; 

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
      for(long unsigned int i = 0; i < size(rateDeffensive); i++){
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
      offWeapons.push_back(oW);

      oW = new OffensiveWeapon("T-64", 1120000, 55000, 125, ATTACKING_VEHICLE);
      offWeapons.push_back(oW);
      
      oW = new OffensiveWeapon("Mi-17", 18300000, 40000, 100, HELICOPTER);
      offWeapons.push_back(oW);

      oW = new OffensiveWeapon("Bayraktar", 5000000, 20000, 100, DRONE);
      offWeapons.push_back(oW);


      /*** Defensive weapons */
      bool b[4] = {false, false, false, true}; char p[4] = {0, 0, 0, 90};
      DefensiveWeapon * dW = new DefensiveWeapon(b, p ,"Iron Dome", 50000000, 125000, 0, ANTI_ROCKETS);
      defWeapons.push_back(dW);

      bool b1[4] = {true, true, true, false}; char p1[4] = {40, 90, 20, 0};
      dW = new DefensiveWeapon(b1, p1, "Javelin", 245000, 78000, 760, ANTI_VEHICLE);
      defWeapons.push_back(dW);

      bool b2[4] = {true, true, true, false}; char p2[4] = {40, 90, 50, 0};
      dW = new DefensiveWeapon(b2, p2, "Stinger", 119000, 38000, 160, ANTI_HELICOPTER);
      defWeapons.push_back(dW);

      bool b3[4] = {true, true, true, false}; char p3[4] = {30, 70, 40, 0};
      dW = new DefensiveWeapon(b3, p3, "Igla-1", 70000, 35000, 72, ANTI_DRONE);
      defWeapons.push_back(dW);
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
      return nullptr;
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
      return nullptr;
    }

    /**
     * @brief  buy one specific weapon 
     * 
     * @param name 
     * @param money 
     * @param offe if weapon is offensive set to true 
     */
    void buyOneWeapon(string name, bool offe, int MAX){
      DefensiveWeapon * defWeapon;
      OffensiveWeapon * offWeapon;
      
      if (offe == true){
        offWeapon = findWeaponOff(name);

        if ((offWeapon->getCartridgePrice() + offWeapon->getPrice()) > money)
          return;

        if (offWeapon->getCartridge() < MAX){
          money = money - offWeapon->getPrice();
        }
        money = money - offWeapon->buyCartridge();
      }
      else{
        defWeapon = findWeaponDef(name);
        if ((defWeapon->getCartridgePrice() + defWeapon->getPrice()) > money)
          return;
          
        if (defWeapon->getCartridge() < MAX){
          money = money - defWeapon->getPrice();
        }
        money = money - defWeapon->buyCartridge();
      }
    }

    void buyWeapons(){

      // ratios are count for each weapon. We can use modulo function for estabilishing good buy. 
      int forModulo = 0;   
      while (money > cheapestWeapon){
        // offensive 
        if ((forModulo % rateOffensive[DRONE]) == 0)
          this->buyOneWeapon("Bayraktar", true, MAX_BAYRAKTAR);
        if ((forModulo % rateOffensive[ATTACKING_VEHICLE]) == 0)
          this->buyOneWeapon("T-64", true, MAX_T64);
        if ((forModulo % rateOffensive[HELICOPTER]) == 0)
          this->buyOneWeapon("Mi-17", true, MAX_MI_17);
        if ((forModulo % rateOffensive[ROCKET]) == 0)
          this->buyOneWeapon("Javelin", true, MAX_JAVELIN);
        // deffensive 
        if ((forModulo % rateDeffensive[ANTI_DRONE]) == 0)
          this->buyOneWeapon("Igla-1", false, MAX_IGLA_1);
        if ((forModulo % rateDeffensive[ANTI_VEHICLE]) == 0)
          this->buyOneWeapon("Javelin", false, MAX_JAVELIN);
        if ((forModulo % rateDeffensive[ANTI_HELICOPTER]) == 0)
          this->buyOneWeapon("Stinger", false, MAX_STINGER);
        if ((forModulo % rateDeffensive[ANTI_ROCKETS]) == 0)
          this->buyOneWeapon("Iron Dome", false, MAX_IRON_DOME);

        forModulo++;        
      }
    }

    /**
     * @brief Defending state will try to defend agains weapon.
     * 
     * @param defending State which is trying to defend. 
     * @param attackingWeapon 
     * @return True if succesfully defend.
     */
    bool defend(State * defending, OffensiveWeapon * attackingWeapon){
      DefensiveWeapon  * defW = nullptr;

      int ran      = (int)(100*Random());
      string name  = attackingWeapon->getName();
      char defProb = 0; // probability of deffensive weapon to destroy offensive 

      if (name == "Bayraktar"){
        defW = defending->findWeaponDef("Igla-1");
        defProb = defW->getProbAgainstDrone();
      }
      else if (name == "T-64"){
        defW = defending->findWeaponDef("Javelin");
        defProb = defW->getProbAgainstVehicle();
      }
      else if (name == "Mi-17"){
        defW = defending->findWeaponDef("Stinger");
        defProb = defW->getProbAgainstHelicopter();
      }
      else if (name == "Javelin"){
        defW = defending->findWeaponDef("Iron Dome"); 
        defProb = defW->getProbAgainstRockets();
      }
      else{
        return false;
      }

      // if there is no cartridge in defensive weapon 
      if (defW->getCartridge() < 1){
        return false;
      }

      // use cartirdge 
      defW->decCartirdge();
      // def prob can be (0, 70)
      if (ran > defProb)
        return false;
      
      return true;
    }

    /**
     * @brief attack with one specific weapon it is called from attackEnemy
     * 
     * @param enemy 
     * @param weaponName 
     */
    void attackWithWeapon(State * enemy, string weaponName){
      OffensiveWeapon * enemyOffW; 
      DefensiveWeapon * enemydefW; 
      string enemyWeaponName; 
      
      OffensiveWeapon * offW = findWeaponOff(weaponName);
      if (offW->getCartridge() < 1)
        return;

      // random numbers 
      int ran      = (int)(100*Random());
      int ranCivil = (int)(100*Random());
      int normal   = (int)Normal(100, 10);

      int damageDealth = 0;

      ranCivil        = (int)(100*Random());
      ran             = (int)(10000*Random());
      normal          = 0;
      damageDealth    = 0;
      enemyOffW       = nullptr;
      enemydefW       = nullptr; 
      enemyWeaponName = "";

      // always try to defend (you don't know if it hits the target )
      // if defend == True (enemy did defend)
      bool def = defend(enemy, offW);

      offW->decCartirdge();

      // CIVIL PLACES 
      if ((ranCivil >= P_CIVIL_FROM) && (ranCivil < P_CIVIL_TO)){
          
        if ((ran >= P_ROAD_FROM) && (ran < P_ROAD_TO))
          normal = (int)Normal(MI_ROAD, MI_ROAD*0.15);
        else if ((ran >= P_HOUSE_FROM) && (ran < P_HOUSE_TO))
          normal = (int)Normal(MI_HOUSE,  MI_HOUSE*0.15);
        else if ((ran >= P_BLOCK_H_FROM) && (ran < P_BLOCK_H_TO))
          normal = (int)Normal(MI_BLOCK_H, MI_BLOCK_H*0.15);
        else if ((ran >= P_VEHICLES_FROM) && (ran < P_VEHICLES_TO))
          normal = (int)Normal(MI_VEHICLES, MI_VEHICLES*0.15);
        else if ((ran >= P_BRIDGES_FROM) && (ran < P_BRIDGES_TO))
          normal = (int)Normal(MI_BRIDGES, MI_BRIDGES*0.15);
        else if ((ran >= P_IMPORTANT_FROM) && (ran < P_IMPORTANT_TO))
          normal = (int)Normal(MI_IMPORTANT, MI_IMPORTANT*0.15);
        else if ((ran >= P_AGRO_FROM) && (ran < P_AGRO_TO))
          normal = (int)Normal(MI_AGRO, MI_AGRO*0.15);

        damageDealth += normal;
      }
      // MILITARY FRONT 
      else{
        if ((int)(100*Random()) < 20){
          enemyWeaponName = getRandomWeapon(enemy);
          if (enemyWeaponName == ""){
            def = 0;
          }
          else {
            enemydefW = enemy->findWeaponDef(enemyWeaponName);
            if (enemydefW == nullptr || enemydefW->getCartridge() < 1){
              enemyOffW = enemy->findWeaponOff(enemyWeaponName);
              enemyOffW->decCartirdge();
              damageDealth += enemyOffW->getCartridgePrice();
            }
            else {
              enemydefW->decCartirdge();
              damageDealth += enemydefW->getCartridgePrice();
            } 
          }
        }
      }
      if (def == true){
        enemy->moneySaved += damageDealth;
        return;
      }
      this->moneyDestroyed += damageDealth;
      enemy->moneyLost += damageDealth;
  }

    /**
     * @brief Main function for simulation. 
     */
    void attackEnemy(State * enemy){
      attackWithWeapon(enemy, "Bayraktar");
      attackWithWeapon(enemy, "T-64");
      attackWithWeapon(enemy, "Mi-17");
      attackWithWeapon(enemy, "Javelin");
    }

    bool stateHasOffCartridge(State *state){
      list<OffensiveWeapon*>::iterator it;
      for (it = state->offWeapons.begin(); it != state->offWeapons.end(); ++it){
        if ((*it)->getCartridge() > 0)
          return true;
      }
      return false;
    }

    /**
     * @brief Find if state has any cartiridge 
     * @param state 
     * @return true if state has cartridge of any weapon
     * @return false 
     */
    bool stateHasCartridge(State *state){
      list<OffensiveWeapon*>::iterator it;
      for (it = state->offWeapons.begin(); it != state->offWeapons.end(); ++it){
        if ((*it)->getCartridge() > 0)
          return true;
      }
      
      list<DefensiveWeapon*>::iterator i;
      for (i = state->defWeapons.begin(); i != state->defWeapons.end(); ++i){
        if ((*i)->getCartridge() > 0)
          return true;
      }
      return false;
      
    }

    /**
     * @brief Get the Random Weapon object that is in inventory
     * @return weapon name or "" if there is no weapon left  
     */
    string getRandomWeapon(State *state){
      // todo maybe consider weapons not cartridge 
      int ran      = (int)(100*Random());
      int ran2     = (int)(100*Random());
      string name  = "";
      bool def     = false;

      // if state has no resources left  
      if (stateHasCartridge(state) == false)
        return name;

      int i = 0;
      while (true){
        def = false;
        // offensive
        if (ran < 50){
          if (ran2 < 25)
            name = "Bayraktar";
          else if (ran2 < 50)
            name = "T-64";
          else if (ran2 < 75)
            name = "Mi-17";
          else
            name = "Javelin";
        }
        // defensive
        else{
          def = true;
          if (ran2 < 25)
            name = "Igla-1";
          else if (ran2 < 50)
            name = "Javelin";
          else if (ran2 < 75)
            name = "Stinger";
          else
            name = "Iron Dome";
        }

        if (def == true){
          if (state->findWeaponDef(name)->getCartridge() > 0)
            return name;
        }
        else{
          if (state->findWeaponOff(name)->getCartridge() > 0)
            return name;
        }
        if (++i == 500) return "";
      }
    }

    void debugState(){
      cerr << name << endl;
      cerr << "..money: ........... " << money << endl;
      cerr << "..money lost: ...... " << moneyLost << endl;
      cerr << "..money destroyed: . " << moneyDestroyed << endl;
      cerr << "..ratio: ........... " << offRatio << ":" << defRatio << endl;

      cerr << ".................. Weapon Cartridge " << endl;
      cerr << "....Javelin Off .... " << MAX_JAVELIN << "  " << findWeaponOff("Javelin")->getCartridge() << endl;
      cerr << "....Javelin Deff ... " << MAX_JAVELIN << "  " << findWeaponDef("Javelin")->getCartridge() << endl;
      cerr << "....Iron Dome ...... " << MAX_IRON_DOME << "     " << findWeaponDef("Iron Dome")->getCartridge() << endl;
      cerr << "....t64 ............ " << MAX_T64 << "    " << findWeaponOff("T-64")->getCartridge() << endl;
      cerr << "....Stinger ........ " << MAX_STINGER << "   " << findWeaponDef("Stinger")->getCartridge() << endl;
      cerr << "....mi17 ........... " << MAX_MI_17 << "    " << findWeaponOff("Mi-17")->getCartridge() << endl;
      cerr << "....igla1 .......... " << MAX_IGLA_1 << "   " << findWeaponDef("Igla-1")->getCartridge() << endl;
      cerr << "....bayraktar ...... " << MAX_BAYRAKTAR << "    " << findWeaponOff("Bayraktar")->getCartridge() << endl;
      cerr << "=====================================" << endl;
    }

    void output(){
      cout << name << ";" << moneyBegin << ";" << moneyLost \
        << ";" << moneyDestroyed << ";" << defRatio << ";" << offRatio ;
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

  // arg parsing 
  unsigned long long set[6] = {0,0,0,0,0,0};
  argParse(argc, argv, set);

  // init states 
  State * stateA = new State(set[0], set[1], set[2], "stateA");
  State * stateB = new State(set[3], set[4], set[5], "stateB");
  
  
  // initialize random values 
  RandomSeed(time(NULL));

  // buy weapons 
  stateA->buyWeapons();
  stateB->buyWeapons();
  
  stateA->debugState();
  stateB->debugState();

  // run simulation while there is a munition
  while (stateA->stateHasOffCartridge(stateA) ||
        stateB->stateHasOffCartridge(stateB)){
    
    stateA->attackEnemy(stateB);
    stateB->attackEnemy(stateA);
  }

  cerr << "\nAfter battle:" << endl;

  stateA->debugState();
  stateB->debugState();

  // output format  
  cerr << "Name" << ";" << "MoneyBegin" << ";" << "MoneyLost" \
    << ";" << "MoneyDestroyed" << ";" << "DefRatio" << ";" << "OffRatio" << endl;
  
  // output 
  stateA->output();
  cout << ";";
  stateB->output();
  cout << endl; 

  return 0;

}