//Library scripts for enemy functions

void dasherP( float Vx, float Vy, int Flip)
{// Dash with desired speed!
// Won't apply if enemy is in midair
    void self = getlocalvar("self");
    int dir = getentityproperty(self,"direction");
    int y = getentityproperty(self, "a");
    int b = getentityproperty(self, "base");

    if(dir==0 && Flip==1){ // Facing left?
      Vx = -Vx ;
    }

    if(y <= b){
      changeentityproperty(self, "velocity", Vx, 0, Vy); //Move!
    }
}

void attack0(void Ani)
{// Attack interruption
    void self = getlocalvar("self");

    performattack(self, openborconstant(Ani)); //Attack!
}

void attack1(int RxMin, int RxMax, int RyMin, int RyMax, void Ani)
{// Attack interruption with range check
    void self = getlocalvar("self");
    void target = findtarget(self); //Get nearest player
    float x = getentityproperty(self, "x");
    float y = getentityproperty(self, "a");
    int dir = getentityproperty(self, "direction");

    if(target!=NULL()){
      float Tx = getentityproperty(target, "x");
      float Ty = getentityproperty(target, "a");
      float Disx = Tx - x;
      float Disy = Ty - y;

      if( Disx >= RxMin && Disx <= RxMax && Disy >= RyMin && Disy <= RyMax && dir == 1) // Target within range on right facing?
      {
        performattack(self, openborconstant(Ani)); //Change the animation
      } else if( Disx >= -RxMax && Disx <= -RxMin && Disy >= RyMin && Disy <= RyMax && dir == 0) // Target within range on left facing?
      {
        performattack(self, openborconstant(Ani)); //Change the animation
      }
    }
}
