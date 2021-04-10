#include "Stage.h"
#include <SFML/Graphics.hpp>
Stage::Stage()
{
    this->height = 16;
    this->width = 12;
    this->map[192];
};

Stage::Stage(int x, int y)
{
    this->width = x;
    this->heigth = y;
    this->map[width*height];
}

int* Stage::getMap()
{
    return this->map;
}

int Stage::getGold()
{
    return gold;
};

void Stage::setGold(int g)
{
    this->gold = g;
};
int Stage::getValueOnMap(int x,int y){          //inputs are coordinates on the map, top-left is (0,0)
    return Stage::map[y*width+x];
}
void Stage::setValueOnMap(int x, int y, int v){
    Stage::map[y*width+x]=v;
}
bool Stage::build(Tower tower, int posx,int posy ){    //If the player clicks on a slot, the position of the slot should be defense object
    if(Stage::map[posx+Stage::width*posy]!=3){
        return false;   //position is not valid;

    }
    if(Stage::gold<tower.getCost()){
        return false;
    }
    Stage::gold-=tower.getCost();
    
    Stage::setValueOnMap(posx,posy,4);
    //determine by enum 
    Stage::towerlist[curtower]=Tower(posx,posy,1);
    curtower+=1;
    return true;

};
void Stage::spawnEnemy(){
    if(Stage::curenemy<Stage::enemycount){
        enemy=Stage::viruslist[Stage::curenemy];
        enemy.setAlive();
        enemy.spawn(Stage::startx,Stage::starty,0,13);
        curenemy+=1;
    };
};
void Stage::allAttack(){
    for(int i = 0; i < this->tower_count; i++)
    {
        //tower=&towerlist[i];?
        //tower.attack();
        ;
    }
};

void Stage::attackFirstEnemyInRange(Tower tower){  //x,y are coordinates of the tower, and r is the range of the tower 
    for(int i=0;i<enemycount;i++){
        enemy=viruslist[i];
        if(!enemy.isAlive()){
            posx=enemy.getx();
            posy=enemy.gety();
            x=tower.getx();
            y=tower.gety();
            r=tower.getRange();
            if ((posx-x)*(posx-x)+(posy-y)*(posy-y)<=r*r){
                //tower.attack(enemy);
            }
        }
    }
}

void Stage::updateTowers(){
    for(int i=0;i<curtower;i++){
        
            tower=towerlist[i];
            Stage::attackFirstEnemyInRange(tower);
        
    }
}

