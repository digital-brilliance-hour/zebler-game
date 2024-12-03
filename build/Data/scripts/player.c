void shoot(void Shot, float dx, float dy, float dz){
	void self = getlocalvar("self");
	int Direction = getentityproperty(self, "direction");
	int x = getentityproperty(self, "x");
	int y = getentityproperty(self, "a");
	int z = getentityproperty(self, "z");
	if (Direction == 0){
		dx = -dx;
	}
	projectile(Shot, x+dx, z+dz, y+dy, Direction, 0, 0, 0);
}void toss(void Bomb, float dx, float dy, float dz){
	void self = getlocalvar("self");
	int Direction = getentityproperty(self, "direction");
	int x = getentityproperty(self, "x");
	int y = getentityproperty(self, "a");
	int z = getentityproperty(self, "z");

	if (Direction == 0){
		dx = -dx; 
	}
	projectile(Bomb, x+dx, z+dz, y+dy, Direction, 0, 1, 0);
}void flipdir(){
	void self = getlocalvar("self");
	changeentityproperty(self, "direction", !getentityproperty(self, "direction"));
}void ani001(void vAni, int iFrame){
	void vSelf = getlocalvar("self"); 
	changeentityproperty(vSelf, "animation", openborconstant(vAni)); 
	changeentityproperty(vSelf, "animpos", iFrame); 
}void ani002(void vAni, int iFrame){
	void vSelf = getlocalvar("self"); 
	void vTarget = getentityproperty(vSelf, "opponent");
	changeentityproperty(vTarget, "animation", openborconstant(vAni)); 
	changeentityproperty(vTarget, "animpos", iFrame); 
}void clearL(){
	clearlocalvar();
}void clearG(){
	clearglobalvar();
}void velo001(float fX, float fZ, float fY){
	void vSelf = getlocalvar("self");
	if (getentityproperty(vSelf, "direction")==0){
		fX = -fX; 
	}
	changeentityproperty(vSelf, "velocity", fX, fZ, fY); 
}void keyint(void Ani, int Frame, void Key, int Hflag, int Limit){
	void self = getlocalvar("self");
	void vMp = getentityproperty(self,"mp");
	int iPIndex = getentityproperty(self,"playerindex");
	void iRKey;
	if (Key=="U"){
		iRKey = playerkeys(iPIndex, 0, "moveup");
	}
	if (Key=="D"){
		iRKey = playerkeys(iPIndex, 0, "movedown");
	}
	if (Key=="F"){ 
		if (getentityproperty(self,"direction")){ 
			iRKey = playerkeys(iPIndex, 0, "moveright");
		}
		else{
			iRKey = playerkeys(iPIndex, 0, "moveleft");
		}
	}
	if (Key=="B"){ 
		if (getentityproperty(self,"direction")){ 
			iRKey = playerkeys(iPIndex, 0, "moveleft");
		}
		else{
			iRKey = playerkeys(iPIndex, 0, "moveright");
		}
	}
	if (Key=="J"){
		iRKey = playerkeys(iPIndex, 0, "jump");
	}
	if (Key=="A"){
		iRKey = playerkeys(iPIndex, 0, "attack");
	}
	if (Key=="A2"){
		iRKey = playerkeys(iPIndex, 0, "attack2");
	}
	if (Key=="S"){
		iRKey = playerkeys(iPIndex, 0, "special");
	}
	if (Key=="UA"){
		iRKey = playerkeys(iPIndex, 0, "moveup", "attack");
	}
	if (Key=="BA"){
		iRKey = playerkeys(iPIndex, 0, "moveleft", "attack");
	}
	if (Key=="DA"){
		iRKey = playerkeys(iPIndex, 0, "movedown", "attack");
	}
	if (Key=="SD"){ 
		iRKey = playerkeys(iPIndex, 0, "special", "movedown"); 
	}
	if (Key=="SB"){ 
		if (getentityproperty(self,"direction")){ 
			iRKey = playerkeys(iPIndex, 0, "moveleft", "special");
		}
		else{
			iRKey = playerkeys(iPIndex, 0, "moveright", "special");
		}
	}
	if (Key=="DJ"){ 
		iRKey = playerkeys(iPIndex, 0, "movedown", "jump"); 
	}
	if (Key=="UJ"){ 
		iRKey = playerkeys(iPIndex, 0, "moveup", "jump"); 
	}
	if (Key=="FJ"){ 
		if (getentityproperty(self,"direction")){ 
			iRKey = playerkeys(iPIndex, 0, "moveright", "jump");
		}
		else{
			iRKey = playerkeys(iPIndex, 0, "moveleft", "jump");
		}
	}
	if (Key=="BJ"){ 
		if (getentityproperty(self,"direction")){ 
			iRKey = playerkeys(iPIndex, 0, "moveleft", "jump");
		}
		else{
			iRKey = playerkeys(iPIndex, 0, "moveright", "jump");
		}
	}
	if (Hflag==1){ 
		iRKey = !iRKey; 
	}
	if ((vMp > Limit)&&iRKey){
		changeentityproperty(self, "animation", openborconstant(Ani));
		changeentityproperty(self, "animpos", Frame);
	}
}void keycheck(){
	void self = getlocalvar("self");
	int player = getentityproperty(self, "playerindex");
	float xdir = 0;
	float zdir = 0;
	float speed = 1.7;
	if(playerkeys(0, 0, "moveleft"))
	xdir = -speed;
	else if(playerkeys(0, 0, "moveright"))
	xdir = speed;
	if(playerkeys(0, 0, "moveup"))
	zdir = -speed/2.0;
	else if(playerkeys(0, 0, "movedown"))
	zdir = speed/2.0;
	changeentityproperty(self, "velocity", xdir, zdir, 0);
}
void shoot2(void Shot, float dx, float dy, float dz)
{ // Shooting targetted projectile
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
}

void target(float Velx, float Velz)
{// Targetting opponent before leaping or dashing
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
        changeentityproperty(self, "direction", 0);
      } else {
        changeentityproperty(self, "direction", 1);
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
