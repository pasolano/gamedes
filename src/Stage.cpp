#include "Stage.h"
#include <SFML/Graphics.hpp>

Stage::Stage(){
    // Test to set up first stage
    height = 12;
    width = 16;
    tower_count = 20;
    virus_count = 50;
    virus_total = 50;
    start1 = 15;
    start2 = 6;
    virus_tex = Texture();
    if(virus_tex.loadFromFile("../data/covid.png")){
        // std::cout << "TEXTURE" << std::endl;
        ;
    }
    // use malloc if these are local variables? 
    // populate virus list
    for (int i = 0; i < virus_count; i++) {
        auto temp_virus = Virus(start1, start2, Left, Viruses::covid, 13, map);
        temp_virus.setTexture(&virus_tex);
        auto temp_pair = std::pair<Virus, sf::Int64>(temp_virus, 1500000);
        virus_list.push_back(temp_pair);
    }
    cur_virus_pair = virus_list.begin();
    base_loc = Vector2i(7,6);
    gold = 100;
    base_health = 10;
    virus_kill_count = 0;
    }

Stage::Stage(sf::Texture* vir_tex){
    // Test to set up first stage
    height = 12;
    width = 16;
    int map_values[192] = {0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,7,6,6,6,6,6,6,8,0,0,0,0,0,0,0,0,5,3,0,0,0,0,3,5,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,5,0,0,0,0,0,
    0,0,0,5,3,0,0,0,0,3,5,0,0,0,0,0,0,0,0,5,0,0,0,1,0,0,5,0,0,0,7,6,0,0,0,5,0,0,0,5,0,0,5,0,0,0,5,3,0,0,0,5,0,0,0,5,0,3,5,3,0,3,5,0,0,0,0,5,3,0,3,5,0,0,9,6,6,6,10,0,0,0,0,9,6,6,6,10,0,0,0,0,3,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    std::copy(std::begin(map_values), std::end(map_values), std::begin(map));
    tower_count = 20;
    virus_count = 50;
    virus_total = 50;
    start1 = 15;
    start2 = 6;
    virus_tex = Texture();
    if(virus_tex.loadFromFile("../data/covid.png")){
        // std::cout << "TEXTURE" << std::endl;
    }
    // use malloc if these are local variables? 
    // populate virus list
    for (int i = 0; i < virus_count; i++) {
        auto temp_virus = Virus(start1, start2, Left, Viruses::covid, 13, map_values);
        temp_virus.setTexture(vir_tex);
        auto temp_pair = std::pair<Virus, sf::Int64>(temp_virus, 1500000);
        virus_list.push_back(temp_pair);
    }
    cur_virus_pair = virus_list.begin();
    base_loc = Vector2i(7,6);
    gold = 220;
    base_health = 100;
    virus_kill_count = 0;
}

int* Stage::getMap()
{
    return map;
}

int Stage::getGold()
{
    return gold;
}

void Stage::setGold(int g)
{
    gold = g;
}
int Stage::getValueOnMap(int x,int y){          //inputs are coordinates on the map, top-left is (0,0)
    return map[y * width + x];
}
void Stage::setValueOnMap(int x, int y, int v){
    map[y * width + x] = v;
}
bool Stage::build(Towers type, int posx, int posy ){    //If the player clicks on a slot, the position of the slot should be defense object
    if(map[posx + width * posy] != 3){
        int a=map[posx + width * posy];        
        return false;   //position is not valid;
    }
    int tower_cost;
    switch (type)
    {
        case Towers::first:
            tower_cost = 100;
            break;
    }

    if(gold < tower_cost){
        return false;
    }

    gold -= tower_cost;
    setValueOnMap(posx,posy,4);
    //determine by enum
    Tower new_tower = Tower(posx,posy,type);
    tower_list.push_back(pair<Tower, Int64>(new_tower, 0));
    //cur_tower=boost::next(cur_tower);
    return true;

}

bool Stage::attackFirstVirus(Tower* tower, PlayerView* pView){  //x,y are coordinates of the tower, and r is the range of the tower 
    for (auto & virus : virus_list) {
        Virus* enemy = &(virus.first);
        if(enemy->isAlive()){
            auto virus_pos = enemy->getPosition();
            float posx = virus_pos.x;
            float posy = virus_pos.y;
            auto tower_pos = tower->GetPosition();
            float x = tower_pos.x;
            float y = tower_pos.y;
            float r = tower->GetRadius();
            if ((posx-x)*(posx-x)+(posy-y)*(posy-y)<=r*r)
            {
                tower->Attack(enemy, pView->getTexture());
                bullet_list.push_back(tower->getBullet());
                return true;
            }
        }
    }
    return false;
}

std::list<std::pair<Tower, Int64>>* Stage::getTowerList()
{
    return &tower_list;
}

std::list<std::pair<Virus, Int64>>* Stage::getVirusList()
{
    return &virus_list;
}

std::list<Bullet>* Stage::getBulletList(){
    return &bullet_list;
}

void Stage::update(Int64 elapsedTime, PlayerView* pView)
{
    // check if time to spawn virus
    virus_timer += elapsedTime/2;
    if ((virus_timer >= (*cur_virus_pair).second) && (virus_count > 0)) {
        spawnVirus();
        virus_timer = 0;
        virus_count--;
    }

    // update all viruses
    for (auto& pair : virus_list) {
        int x=pair.first.update(elapsedTime, &base_loc, &base_health);
        if(x==1){
            gold+=10;
        }
    }

    // update all towers
    for (auto& pair : tower_list) {
        auto tower = &(pair.first);
        if ((tower->GetAttackSpeed() * 1000000) <= pair.second) // TODO doesnt use microseconds
        {
            tower->SetReadyToAttack(true);
            pair.second = 0;
        }
        else
        {
            pair.second += elapsedTime;
        }
        if (tower->GetReadyToAttack())
        {
            // try to attack a virus
            if (attackFirstVirus(&(pair.first), pView))
            {
                tower->SetReadyToAttack(false);
            }
        }
    }

    // update all bullets
    for(auto& bullet : bullet_list){
        bullet.follow(elapsedTime);
        if(bullet.detectHit()){ // if dead
            virus_kill_count++;
        }
    }
}

void Stage::spawnVirus() {
    (*cur_virus_pair).first.setAlive(true);
    cur_virus_pair = next(cur_virus_pair);
}

bool Stage::baseAlive()
{
    return (base_health > 0);
}

bool Stage::allVirusKilled()
{
    return (virus_kill_count == virus_list.size());
}