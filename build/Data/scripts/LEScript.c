//Script for lesser enemies

#include "data/scripts/library/spawn.h"
#include "data/scripts/library/basic.h"
#include "data/scripts/library/enemies.h"


void givescore(int Add)
{// Gives score to players
    void P1 = getplayerproperty(0, "entity");

    if(P1!=NULL()){
      int P1Score = getplayerproperty(0, "score");
      changeplayerproperty(0, "score", P1Score+Add);
    }
}

void spawnM(void Name, float dx, float dy, float dz)
{ // Spawn certain entity and matches its map with own's map
   void self = getlocalvar("self");
   int map = getentityproperty(self,"map");
   void Spawn;

   Spawn = spawn01(Name, dx, dy, 0);
   changeentityproperty(Spawn, "map", map);
}

void dropItem(float dx, float dy, float Vx)
{ // Drops item
// Dropped item is based on random
   int r = rand()%20;
   void Spawn;

   if(r > 10){
     Spawn = spawn01("Coin1", dx, dy+10, 0);
     changeentityproperty(Spawn, "velocity", -Vx);

     Spawn = spawn01("Health", dx-10, dy, 0);
     changeentityproperty(Spawn, "velocity", -Vx);

     Spawn = spawn01("Coin2", dx+10, dy-10, 0);
     changeentityproperty(Spawn, "velocity", -Vx);
   } else if(r < -10){
     Spawn = spawn01("Health", dx, dy+10, 0);
     changeentityproperty(Spawn, "velocity", -Vx);

     Spawn = spawn01("Coin1", dx-10, dy, 0);
     changeentityproperty(Spawn, "velocity", -Vx);
   } else {
     Spawn = spawn01("Health", dx, dy, 0);
     changeentityproperty(Spawn, "velocity", -Vx);
   }
}
