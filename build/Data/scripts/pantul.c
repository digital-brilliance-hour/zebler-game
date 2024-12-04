void main()
{// Script for 'pantul dinding'
// Flips facing direction & velocity
    void self = getlocalvar("self");
    float Vx = getentityproperty(self,"xdir");
    int dir = getentityproperty(self,"direction");

    if(dir==0){ // Facing left?
      changeentityproperty(self, "direction", 1);
    } else {
      changeentityproperty(self, "direction", 0);
    }
    changeentityproperty(self, "velocity", -Vx);
}