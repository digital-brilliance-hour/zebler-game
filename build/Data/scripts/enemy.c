//Script for harder enemies

#include "data/scripts/library/spawn.h"
#include "data/scripts/library/basic.h"
#include "data/scripts/library/target.h"
#include "data/scripts/library/enemies.h"

void layer(int layer)
{// Set's enemy's layer
    void self = getlocalvar("self");
    changeentityproperty(self, "setlayer", layer);
}

void givescore(int Add)
{// Gives score to players
    void P1 = getplayerproperty(0, "entity");
    void P2 = getplayerproperty(1, "entity");

    if(P1!=NULL()){
      int P1Score = getplayerproperty(0, "score");
      changeplayerproperty(0, "score", P1Score+Add);
    }
}

void spawnMover(void Name, float dx, float dy, float dz, int Num)
{ // Spawn mover, store it and bind it
   void self = getlocalvar("self");
   void Spawn;

   Spawn = spawn01(Name, dx, dy, 0);
   setentityvar(self, Num, Spawn); // Stores spawned gun to be killed later
   bindentity(self, Spawn, dx, dz, dy, 1, 0); // Bind self to spawned gun
}

void killgun(int Num, int Flag)
{ // Kill bound gun based on number
    void self = getlocalvar("self");
    void Gun = getentityvar(self, Num);

    if(Gun!=NULL()){
      bindentity(Gun, NULL());
      if(Flag==1){
        damageentity(Gun, self, 1000, 0, openborconstant("ATK_NORMAL"));
      } else {
        killentity(Gun);
      }
    }
}

void randomMove(int V)
{ // Moves with random angle
// V : Base velocity
    int r = rand()%180;
    int Vx;
    int Vy;

    Vx = V*cos(r);
    Vy = V*sin(r);

    dasher(Vx,Vy,0);
}
