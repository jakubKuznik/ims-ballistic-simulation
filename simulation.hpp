// Solution for VUT FIT IMS project: Simulation of balistic weapons 10.11.2022
// File:        simulation.hpp
// Authors:     Vojtech Tom Hezcko, Jakub Kuzník, 
// Organization: BUT FIT

#include <iostream>
#include <list>
#include <string.h>
#include <algorithm>
#include <simlib.h>



#define DRONE 0
#define ATTACKING_VEHICLE 1
#define HELICOPTER 2
#define ROCKET 3

#define ANTI_DRONE 0
#define ANTI_VEHICLE 1
#define ANTI_HELICOPTER 2
#define ANTI_ROCKETS 3

// @return int[moneyA, offensiveRatioA, deffensiveRatioA, moneyB, offensiveRatioB, deffensiveRatioB] 
#define MONEY_A 0
#define OFF_RATIO_A 1 
#define DEF_RATIO_A 2
#define MONEY_B 3
#define OFF_RATIO_B 4 
#define DEF_RATIO_B 5


// from [https://www.aljazeera.com/news/2022/6/15/infographic-what-weapons-has-ukraine-received-from-the-us-and-al]
#define MAX_JAVELIN 600 
#define MAX_IRON_DOME 2

#define MAX_T64 50
#define MAX_MI_17 10

#define MAX_IGLA_1 200
#define MAX_BAYRAKTAR 50

#define MAX_STINGER 100

// probabilities
#define P_ROAD_FROM 0 
#define P_ROAD_TO 2500
#define P_HOUSE_FROM 2500
#define P_HOUSE_TO 4000
#define P_BLOCK_H_FROM 4000
#define P_BLOCK_H_TO 4300
#define P_VEHICLES_FROM 4300
#define P_VEHICLES_TO 4500 
#define P_BRIDGES_FROM 4500
#define P_BRIDGES_TO 4510
#define P_IMPORTANT_FROM 4500
#define P_IMPORTANT_TO 4501 
#define P_AGRO_FROM 4501 
#define P_AGRO_TO 9490
#define P_CIVIL_FROM 0 
#define P_CIVIL_TO 10

#define MI_ROAD 42000
#define MI_HOUSE 170000 
#define MI_BLOCK_H 300000 
#define MI_VEHICLES 75000 
#define MI_BRIDGES 1500000 
#define MI_IMPORTANT 5000000
#define MI_AGRO 500