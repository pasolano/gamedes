//Edited by Yixuan Xu on 04/10


#ifndef _STAGE_H_
#define _STAGE_H_

#include <SFML/Graphics.hpp>
#include <Virus.h>
#include <Tower.h>
class Stage{
    public:
    Stage(void);
    void draw(sf::RenderWindow &window);
    //void StartStage();
    int getGold();
    void setGold(int g);
    int* getMap();
    void build(/*Tower tower*/);        //trigger build event
    int getValueOnMap(int x,int y);
    void setValueOnMap(int x, int y, int v);
    void allAttack();
    bool build(/*Tower1 tower, int posx,int posy */);
    protected:
    int width;
    int height;
    int level;
    //int difficulty;
    int* map;                           //might need to import the size of screen from other files instead of hardcoding
    Virus::Virus* viruslist;                 //the list of enemeies/towers for this level
    Tower::Tower* towerlist;
    void attackFirstEnemy();          //choose the enemy to attack   
    void updateTowers();              //check all towers if they can attack an enemy
    int gold;                           //used to build defense, increase when enemies are killed (maybe has a static growth rate)
    int start1;                         //where enemies are spawned
    int start2;
    int towercount;
    int curtower=0;
    int enemycount;
    int curenemy=0;
    
};


#endif /* _STAGE_H_ */