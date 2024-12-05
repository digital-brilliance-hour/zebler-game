void main()
{ 
    void self = getlocalvar("self");
    int y = getentityproperty(self,"y");
    int HP = getentityproperty(self,"health");
    int Vy = getentityproperty(self,"tossv");
    int Limit = getglobalvar("Atap");

    if(Limit == NULL()){
      Limit = 9999;
    }

    if(y >= Limit){ // Reached y limit
      changeentityproperty(self, "position", NULL(), NULL(), Limit);
      changeentityproperty(self, "velocity", NULL(), NULL(), -0.1);
    }

    if(Vy < 0 && y < -120 && HP > 50){
      changeentityproperty(self, "health", HP-50);
      changeentityproperty(self, "subject_to_gravity", 0);
      performattack(self, openborconstant("ANI_FOLLOW5"));
    }
}


