void main()
{// Temporary invincibility script
    void self = getlocalvar("self"); //Get calling entity.
    int Health = getentityproperty(self,"health");
    int Type = getlocalvar("attacktype");
    int eTime = openborvariant("elapsed_time");

    if(Health > 0 && Type != openborconstant("ATK_NORMAL2")){
      changeentityproperty(self, "invincible", 1);
      changeentityproperty(self, "invinctime", eTime + 400);
      changeentityproperty(self, "blink", 1);
    }
}