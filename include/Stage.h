//Edited by Yixuan Xu on 04/10


#ifndef _STAGE_H_
#define _STAGE_H_

#include <SFML/Graphics.hpp>
#include "Tower.h"
#include "Virus.h"
#include <math.h>

#include <list>
#include <iostream>
using namespace std;
class Stage {
    public:
        Stage();
        Stage(int); // Just for testing
        Stage(int, int);
        //void StartStage();
        int getGold();
        void setGold(int);
        int* getMap();
        int getValueOnMap(int , int);
        void setValueOnMap(int, int, int);
        void allAttack();
        bool build(Tower::Towers, int, int);
        std::list<Tower*>* getTowerList();
        std::list<std::pair<Virus*, Int64>*>* getVirusList();
        void update(Int64);
        static Vector2i pixelToGrid(Vector2f);
        static Vector2f gridToPixelMiddle(Vector2i);
    protected:
        int width;
        int height;
        int level;
        //int difficulty;
        int map[192];                           //might need to import the size of screen from other files instead of hardcoding
        int tower_count;
        int virus_count;
        std::list<std::pair<Virus*, Int64>*>::iterator cur_virus_pair;
        std::list<Tower*> tower_list;
        std::list<std::pair<Virus*, Int64>*> virus_list;                 //the list of enemies/towers for this level
        void attackFirstVirus(Tower*);          //choose the enemy to attack
        void updateTowers();              //check all towers if they can attack an enemy
        sf::Int64 virus_timer;
        int gold;                           //used to build defense, increase when enemies are killed (maybe has a static growth rate)
        int start1;                         //where enemies are spawned
        int start2;
        sf::Vector2i base_loc;
        void spawnVirus();
};

#endif /* _STAGE_H_ */
