
#ifndef Bullet_h
#define Bullet_h
#include <SFML/Graphics.hpp>
#include "SpriteActor.h"
#include "Virus.h"

class Bullet : public SpriteActor{

    public:
        Bullet();
        Bullet(float, float, int, int, int, int, Virus*);
        void follow();
        bool detectHit();
        

    private:
        Virus* target;

};

#endif