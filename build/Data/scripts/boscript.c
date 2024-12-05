void velo001(float fX, float fZ, float fY){
	void vSelf = getlocalvar("self"); 
	if (getentityproperty(vSelf, "direction")==0){                  
		fX = -fX; 
	}        
	changeentityproperty(vSelf, "velocity", fX, fZ, fY);
}void clearL(){
	clearlocalvar();
}void faint(){
	void vSelf = getlocalvar("self");
	void Health = getentityproperty(vSelf,"health"); 
	if (Health <= 150){
		changeentityproperty(vSelf, "animation", openborconstant("ANI_ATTACK2")); 
	}
}void ani001(void vAni, int iFrame){
	void vSelf = getlocalvar("self"); 
	changeentityproperty(vSelf, "animation", openborconstant(vAni)); 
	changeentityproperty(vSelf, "animpos", iFrame); 
}void spawn01(void vName, float fX, float fY, float fZ){
	//spawn01 (Generic spawner)
	//Damon Vaughn Caskey
	//07/06/2007
	//
	//Spawns entity next to caller.
	//
	//vName: Model name of entity to be spawned in.
	//fX: X location adjustment.
	//fZ: Y location adjustment.
      //fY: Z location adjustment.

	void self = getlocalvar("self"); //Get calling entity.
	void vSpawn; //Spawn object.
	int  iDirection = getentityproperty(self, "direction");

	clearspawnentry(); //Clear current spawn entry.
      setspawnentry("name", vName); //Acquire spawn entity by name.

	if (iDirection == 0){ //Is entity facing left?                  
          fX = -fX; ////Reverse X direction to match facing.
	}

      fX = fX + getentityproperty(self, "x"); //Get X location and add adjustment.
      fY = fY + getentityproperty(self, "a"); //Get Y location and add adjustment.
      fZ = fZ + getentityproperty(self, "z"); //Get Z location and add adjustment.
	
	vSpawn = spawn(); //Spawn in entity.

	changeentityproperty(vSpawn, "position", fX, fZ, fY); //Set spawn location.
	changeentityproperty(vSpawn, "direction", iDirection); //Set direction.
    
	return vSpawn; //Return spawn.
}void shoot(void Shot, float dx, float dy, float dz){ // Shooting projectile
   void self = getlocalvar("self");
   int Direction = getentityproperty(self, "direction");
   int x = getentityproperty(self, "x");
   int y = getentityproperty(self, "a");
   int z = getentityproperty(self, "z");

   if (Direction == 0){ //Is entity facing left?                  
      dx = -dx; //Reverse X direction to match facing
   }

   projectile(Shot, x+dx, z+dz, y+dy, Direction, 0, 0, 0);
}void shoot2(void Shot, float dx, float dy, float dz){ // Shooting targetted projectile
   void self = getlocalvar("self");
   int Direction = getentityproperty(self, "direction");
   int x = getentityproperty(self, "x");
   int y = getentityproperty(self, "a");
   int z = getentityproperty(self, "z");
   float Vx = getlocalvar("x"+self);
   float Vz = getlocalvar("z"+self);
   void vShot;

   if (Direction == 0){ //Is entity facing left?                  
      dx = -dx; //Reverse X direction to match facing
   }

   vShot = projectile(Shot, x+dx, z+dz, y+dy, Direction, 0, 0, 0);

   if( Vx!=NULL() && Vz!=NULL() ){
     changeentityproperty(vShot, "velocity", Vx, Vz); //Move projectile towards target!

     if (Direction == 0){ //Is entity facing left?                  
       changeentityproperty(vShot, "speed", -Vx);
     } else {changeentityproperty(vShot, "speed", Vx);}
   }
}void toss(void Bomb, float dx, float dy, float dz){ // Tossing bomb
   void self = getlocalvar("self");
   int Direction = getentityproperty(self, "direction");
   int x = getentityproperty(self, "x");
   int y = getentityproperty(self, "a");
   int z = getentityproperty(self, "z");

   if (Direction == 0){ //Is entity facing left?                  
      dx = -dx; ////Reverse X direction to match facing
   }

   projectile(Bomb, x+dx, z+dz, y+dy, Direction, 0, 1, 0);
}void target(float Velx, float Velz){// Targetting opponent before leaping or dashing
    void self = getlocalvar("self");
    int dir = getentityproperty(self, "direction");
    float x = getentityproperty(self, "x");
    float z = getentityproperty(self, "z");

    setlocalvar("T"+self, findtarget(self)); //Get nearest player

    if( getlocalvar("T"+self) != NULL()){
      void target = getlocalvar("T"+self);
      float Tx = getentityproperty(target, "x");
      float Tz = getentityproperty(target, "z");
      float Disx = Tx - x;
      float Disz = Tz - z;

      if(Disx < 0){
        Disx = -Disx;
      }

      if(Disz < 0){
        Disz = -Disz;
      }

      if(Disz < Disx)
      {
        if(Tx < x){
          setlocalvar("x"+self, -Velx);
        } else { setlocalvar("x"+self, Velx); }

        setlocalvar("z"+self, Velx*(Tz-z)/Disx);
      } else {
        if(Tz < z){
          setlocalvar("z"+self, -Velz);
        } else { setlocalvar("z"+self, Velz); }

        setlocalvar("x"+self, Velz*(Tx-x)/Disz);
      }

    } else {
      setlocalvar("z"+self, 0);
      if(dir==0){
        setlocalvar("x"+self, -Velx);
      } else { setlocalvar("x"+self, Velx); }
    }
}
void posdie(){
    void self = getlocalvar("self");
    int x = getentityproperty(self,"x"); 
    int z = getentityproperty(self,"z"); 
    int a = getentityproperty(self,"a"); 
    int dir = getentityproperty(self,"direction"); 
    if(x < -50){
    	killentity(self);
    }
}
void posdie2(){
    void self = getlocalvar("self");
    int x = getentityproperty(self,"x"); 
    int z = getentityproperty(self,"z"); 
    int a = getentityproperty(self,"a"); 
    int dir = getentityproperty(self,"direction"); 
    if(x > 370){
    	killentity(self);
    }
}