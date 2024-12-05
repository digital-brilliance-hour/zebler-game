#include "data/scripts/ilu.h"


void setarNPC(){
	void self = getlocalvar("self");
        setglobalvar("npcXPOS", getentityproperty(self,"x"));
}

void matarNPC(){
	       if(openborvariant("count_players")!=1){
    	       void self = getlocalvar("self");
  	       killentity(self);
 }
}

void leaper( float Vx, float Vy, float Vz )
{// Leap with desired speed!
    void self = getlocalvar("self");
    int dir = getentityproperty(self,"direction");

    if(dir==0){ // Facing left?
      Vx = -Vx ;
    }

    tossentity(self, Vy, Vx, Vz); //Leap!
}



void stayAir(int time)
{
	changeentityproperty(getlocalvar("self"),"tosstime",openborvariant("elapsed_time")+time);
}

void flip()
{
	void self=getlocalvar("self");
	changeentityproperty(self,"direction", !getentityproperty(self,"direction")); 
}


void wallAttack(void anim)
{
	void self=getlocalvar("self");
        if(getentityproperty(self,"animationid")!=openborconstant("ANI_FOLLOW5")){
	int iPIndex = getentityproperty(self,"playerindex"); //aqui abaixo vc seta em quais animacoes o player pode usar para grudar nos cantos e paredes
	if(playerkeys(iPIndex, 0, "jump","moveright")||playerkeys(iPIndex, 0, "jump","moveleft"))
	{}else{return;}

	

	int dir=getentityproperty(self,"direction");
	int x=getentityproperty(self,"x");
	int z=getentityproperty(self,"z");
	int a=getentityproperty(self,"a");
	int wall;
        int y = getentityproperty(self,"y");

	if(dir)
	{
		wall=checkwall(x+2,z);
		if (x - openborvariant("xpos")>460)wall=999; // regular estes valores para o seu tamanho de tela do projeto eu uso(960x540)
	}else{
		wall=checkwall(x-2,z);
		if (x - openborvariant("xpos")<14)wall=999; // regular estes valores para o seu tamanho de tela do projeto eu uso(960x540)
	}
	if ((wall>a)&&(y > 10)){
		changeentityproperty(self,"aiflag","attacking",0);
		changeentityproperty(self,"animation",openborconstant(anim));
	}
    }
}

void wallObj(void anim)
{
	void self=getlocalvar("self");

	int dir=getentityproperty(self,"direction");
	int x=getentityproperty(self,"x");
	int z=getentityproperty(self,"z");
	int a=getentityproperty(self,"a");
	int wall;

	if(-dir)
	{
		wall=checkwall(x+2,z);
		if (x - openborvariant("xpos")>460)wall=999; 
	}else{
		wall=checkwall(x-2,z);
		if (x - openborvariant("xpos")<14)wall=999; 
	}
	if (wall>a){
		changeentityproperty(self,"aiflag","attacking",0);
		changeentityproperty(self,"animation",openborconstant(anim));
	}
}


void limiter(int Limit)
{// Prevents hero from performing the animation if his/her health is less than Limit
    void self = getlocalvar("self");
    void Health = getentityproperty(self,"health"); //Get entity's HP.

   if(Health<=Limit) // Don't have enough HP?
   {
     setidle(self); //Don't play the animation.
   }
}

void norun()
{// Turns off running status
    void self = getlocalvar("self");
    changeentityproperty(self, "aiflag", "running", 0);
}



void block(int Flag)
{// Turns blocking status
    void self = getlocalvar("self");
    changeentityproperty(self, "aiflag", "blocking", Flag);
}

void looper(int Frame, int Limit)
{// Loops current animation
    void self = getlocalvar("self");
    void loop = getlocalvar("Loop" + self);

    if(loop==NULL()){ // Localvar empty?
      setlocalvar("Loop" + self, 0);
      loop = 0;
    } 
   
    if(loop < Limit){ // loops reach limit?
      updateframe(self, Frame); //Change frame
      setlocalvar("Loop" + self, loop+1); // Increment number of loops
    }
}





void beidle()
{// Go to IDLE animation!
    void self = getlocalvar("self");

    setidle(self);
}



void anichange(void Ani)
{// Animation changer
    void self = getlocalvar("self");

    changeentityproperty(self, "animation", openborconstant(Ani)); //Change the animation
}




void degravity(int Ratio)
{// Changes antigravity effect
    void self = getlocalvar("self");
    changeentityproperty(self, "antigravity", Ratio);
}

void gravity (int iG)
{
// controls the subject to gravity
// Douglas Baldan/O Ilusionista
void self = getlocalvar("self");
changeentityproperty(self,"subject_to_gravity",iG);
}

void move(int dx, int dz,int da)
{ // Moves entity freely and ignores obstacles
    void self = getlocalvar("self");
    int x = getentityproperty(self,"x"); //Get character's x coordinate
    int z = getentityproperty(self,"z"); //Get character's z coordinate
    int a = getentityproperty(self,"a"); //Get character's a coordinate
    int dir = getentityproperty(self,"direction"); //Get character's facing direction

     if(dir==0){ // Facing left?
      changeentityproperty(self, "position", x-dx, z+dz, a+da); //Move
     }
     else if(dir==1){ // Facing right?
      changeentityproperty(self, "position", x+dx, z+dz, a+da); //Move
     }
}

void dasher( float Vx, float Vy, float Vz )
{// Dash with desired speed!
    void self = getlocalvar("self");
    int dir = getentityproperty(self,"direction");

    if(dir==0){ // Facing left?
      Vx = -Vx ;
    }

    changeentityproperty(self, "velocity", Vx, Vz, Vy); //Move!
}

void stop()
{// Stop hero's movement!
    void self = getlocalvar("self");
    changeentityproperty(self, "velocity", 0, 0, 0);
	changeentityproperty(self, "speed", 0); //Stop moving!
}

void clearL()
{// Clears all local variables
     clearlocalvar();
}

void slammed(int Damage)
{
   // Hurt self
    void self = getlocalvar("self");
    damageentity(self, self, Damage, 1, openborconstant("ATK_NORMAL9")); // Slam damage is inserted here
    tossentity(self, 2, 0, 0);
}

void keyint(void Ani, int Frame, void Key, int Hflag, int Limit)
{// Change current animation if proper key is pressed or released provided HP is more than limit
    void self = getlocalvar("self");
    void Health = getentityproperty(self,"health");    
    int iPIndex = getentityproperty(self,"playerindex"); //Get player index
    void iRKey;

      if (Key=="U"){ //Up Required?
       iRKey = playerkeys(iPIndex, 0, "moveup"); // "Up"
	}

      if (Key=="D"){ //Down Required?
        iRKey = playerkeys(iPIndex, 0, "movedown"); // "Down"
	}

      if (Key=="J"){ //Jump Required?
        iRKey = playerkeys(iPIndex, 0, "jump"); // "Jump"
	}

      if (Key=="A"){ //Attack Required?
        iRKey = playerkeys(iPIndex, 0, "attack"); // "Attack"
	}

      if (Key=="S"){ //Special Required?
        iRKey = playerkeys(iPIndex, 0, "special"); // "Special"
	}

      if (Key=="A2"){ //Attack2 Required?
        iRKey = playerkeys(iPIndex, 0, "attack2"); // "Attack2"
	}

      if (Key=="UJ"){ //Up and Jump Required?
        iRKey = playerkeys(iPIndex, 0, "moveup", "jump"); // "Up" + "Jump"
	}

      if (Hflag==1){ //Not holding the button case?
        iRKey = !iRKey; //Take the opposite condition
	}

      if ((Health > Limit)&&iRKey){
        changeentityproperty(self, "animation", openborconstant(Ani)); //Change the animation
        changeentityproperty(self, "animpos", Frame);

        if (Key=="UJ"){ 
          // This is copy of dethrown
          changeentityproperty(self, "attacking", 0);
          changeentityproperty(self, "damage_on_landing", 0);
          changeentityproperty(self, "projectile", 0);
        }
      }
}

void keyflip()
{// Change hero's facing direction if left or right is pressed
    void self = getlocalvar("self");
    int iPIndex = getentityproperty(self,"playerindex"); //Get player index

    if (playerkeys(iPIndex, 0, "moveleft")){ // Left is pressed?
      changeentityproperty(self, "direction", 0); //Face left
    } else if (playerkeys(iPIndex, 0, "moveright")){ // Right is pressed?
      changeentityproperty(self, "direction", 1); //Face right
    }
}

void keymove(float H, float V)
{// Move hero if direction button is pressed
      void self = getlocalvar("self");
      int iPIndex = getentityproperty(self,"playerindex"); //Get player index
	float xdir = 0;
	float zdir = 0;

      if (playerkeys(iPIndex, 0, "moveleft")){// Left is pressed?
	  xdir = -H;
	} else if(playerkeys(iPIndex, 0, "moveright")){// Right is pressed?
	  xdir = H;
      }

	if(playerkeys(iPIndex, 0, "moveup")){// Up is pressed?
	  zdir = -V;
	} else if(playerkeys(iPIndex, 0, "movedown")){// Down is pressed?
	  zdir = V;
      }

	changeentityproperty(self, "velocity", xdir, zdir);
}

void keymoveH(float V)
{// Move hero if direction button is pressed
      void self = getlocalvar("self");
      int iPIndex = getentityproperty(self,"playerindex"); //Get player index
	float xdir = 0;
	float zdir = 0;

      if (playerkeys(iPIndex, 0, "moveleft")){// Left is pressed?
	  xdir = -V;
	} else if(playerkeys(iPIndex, 0, "moveright")){// Right is pressed?
	  xdir = V;
      }

	changeentityproperty(self, "velocity", xdir, zdir);
}



void spawn01map(void vName, float fX, float fY, float fZ)
{
	//spawn01 (Generic spawner)
	//Damon Vaughn Caskey + Douglas Baldan
	//07/06/2007
	//
	//Spawns entity next to caller.
	//
	//vName: Model name of entity to be spawned in.
	//fX: X location adjustment.
	//fZ: Y location adjustment.
      //fY: Z location adjustment.

	void self = getlocalvar("self"); //Get calling entity.
	int  iMap = getentityproperty(self, "map"); // Get caller's remap.
	void vSpawn; //Spawn object.
	int  iDirection = getentityproperty(self, "direction");

	clearspawnentry(); //Clear current spawn entry.
      setspawnentry("name", vName); //Acquire spawn entity by name.

	if (iDirection == 0){ //Is entity facing left?                  
          fX = -fX; //Reverse X direction to match facing.
	}

      fX = fX + getentityproperty(self, "x"); //Get X location and add adjustment.
      fY = fY + getentityproperty(self, "a"); //Get Y location and add adjustment.
      fZ = fZ + getentityproperty(self, "z"); //Get Z location and add adjustment.
	
	vSpawn = spawn(); //Spawn in entity.

	changeentityproperty(vSpawn, "position", fX, fZ, fY); //Set spawn location.
	changeentityproperty(vSpawn, "direction", iDirection); //Set direction.
	changeentityproperty(vSpawn, "map", iMap); //Set map.
    
	return vSpawn; //Return spawn.
}

void spawnD(void vName, float fX, float fY, float fZ, int pai)
{
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
	int  iDirection = pai;

	clearspawnentry(); //Clear current spawn entry.
      setspawnentry("name", vName); //Acquire spawn entity by name.

	if (iDirection == 0){ //Is entity facing left?                  
          fX = -fX; //Reverse X direction to match facing.
	}

      fX = fX + getentityproperty(self, "x"); //Get X location and add adjustment.
      fY = fY + getentityproperty(self, "a"); //Get Y location and add adjustment.
      fZ = fZ + getentityproperty(self, "z"); //Get Z location and add adjustment.
	
	vSpawn = spawn(); //Spawn in entity.

	changeentityproperty(vSpawn, "position", fX, fZ, fY); //Set spawn location.
	changeentityproperty(vSpawn, "direction", iDirection); //Set direction.
    
	return vSpawn; //Return spawn.
}

void spawn01(void vName, float fX, float fY, float fZ)
{
void self = getlocalvar("self"); //Get calling entity.
	void vSpawn; //Spawn object.
	int  iDirection = getentityproperty(self, "direction");

	clearspawnentry(); //Clear current spawn entry.
      setspawnentry("name", vName); //Acquire spawn entity by name.

	if (iDirection == 0){ //Is entity facing left?                  
          fX = -fX; //Reverse X direction to match facing.
	}

      fX = fX + getentityproperty(self, "x"); //Get X location and add adjustment.
      fY = fY + getentityproperty(self, "a"); //Get Y location and add adjustment.
      fZ = fZ + getentityproperty(self, "z"); //Get Z location and add adjustment.
	
	vSpawn = spawn(); //Spawn in entity.

	changeentityproperty(vSpawn, "position", fX, fZ, fY); //Set spawn location.
	changeentityproperty(vSpawn, "direction", iDirection); //Set direction.
    
	return vSpawn; //Return spawn.
}

void spawner(void vName, float fX, float fY, float fZ)
{	//Spawns entity next to caller and set them as child.
	//
	//vName: Model name of entity to be spawned in.
	//fX: X location adjustment.
	//fZ: Y location adjustment.
      //fY: Z location adjustment.

	void self = getlocalvar("self"); //Get calling entity.
	void vSpawn; //Spawn object.
	
	vSpawn = spawn01(vName, fX, fY, fZ); //Spawn in entity.

	changeentityproperty(vSpawn, "parent", self); //Set caller as parent.
    
	return vSpawn; //Return spawn.
}

void spawnbind(void Name, float dx, float dy, float dz)
{ // Spawn and bind other entity
   void self = getlocalvar("self");
   void Spawn;

   Spawn = spawn01(Name, dx, dy, 0);
   bindentity(Spawn, self, dx, dz, dy, 0, 0);
}

void shoot(void Shot, float dx, float dy, float dz)
{ // Shooting projectile
   void self = getlocalvar("self");
   int Direction = getentityproperty(self, "direction");
   int x = getentityproperty(self, "x");
   int y = getentityproperty(self, "a");
   int z = getentityproperty(self, "z");

   if (Direction == 0){ //Is entity facing left?                  
      dx = -dx; //Reverse X direction to match facing
   }

   projectile(Shot, x+dx, z+dz, y+dy, Direction, 0, 0, 0);
}

void shoot2(void Shot, float dx, float dy, float dz)
{ // Shooting projectile
   void self = getlocalvar("self");
   int Direction = getentityproperty(self, "direction");
   int x = getentityproperty(self, "x");
   int y = getentityproperty(self, "a");
   int z = getentityproperty(self, "z");

   if (Direction == 0){ //Is entity facing left?                  
      dx = -dx; //Reverse X direction to match facing
	projectile(Shot, x+dx, z+dz, y+dy, 1, 0, 0, 0);
   }
   if (Direction == 1){ //Is entity facing left?                  
      dx = -dx; //Reverse X direction to match facing
	projectile(Shot, x+dx, z+dz, y+dy, 0, 0, 0, 0);
   }

   
}


void toss(void Bomb, float dx, float dy, float dz)
{ // Tossing bomb
   void self = getlocalvar("self");
   int Direction = getentityproperty(self, "direction");
   int x = getentityproperty(self, "x");
   int y = getentityproperty(self, "a");
   int z = getentityproperty(self, "z");

   if (Direction == 0){ //Is entity facing left?                  
      dx = -dx; //Reverse X direction to match facing
   }

   projectile(Bomb, x+dx, z+dz, y+dy, Direction, 0, 1, 0);
}




void hpcost( int HCost)
{// Spend some life
    void self = getlocalvar("self");
    void Life = getentityproperty(self,"health"); //get health
if (Life > HCost){ //Does the entity have enough health?
       changeentityproperty(self, "health", Life-HCost);//consume health
      } 
}

void shoot(void Shot, float dx, float dy, float dz)
{ // Shooting projectile
   void self = getlocalvar("self");
   int Direction = getentityproperty(self, "direction");
   int x = getentityproperty(self, "x");
   int y = getentityproperty(self, "a");
   int z = getentityproperty(self, "z");
   void vShot;

   if (Direction == 0){ //Is entity facing left?                  
      dx = -dx; //Reverse X direction to match facing
   }

   vShot = projectile(Shot, x+dx, z+dz, y+dy, Direction, 0, 0, 0);
   return vShot;
}

void shooter(void Shot, float dx, float dy, float dz, float Vx, float Vy, float Vz)
{ // Shooting projectile with speed control
   void vShot = shoot(Shot, dx, dy, dz);

   changeentityproperty(vShot, "velocity", Vx, Vz, Vy);
   changeentityproperty(vShot, "speed", Vx);
}

void keyshoot(void Shot, float dx, float dy, float dz, float Vx, float Vz)
{ // Shooting projectile with key based speed control
    void self = getlocalvar("self");
    int iPIndex = getentityproperty(self,"playerindex"); //Get player index
    void vShot = shoot(Shot, dx, dy, dz);

    if (playerkeys(iPIndex, 0, "moveup")){
      changeentityproperty(vShot, "velocity", Vx, -Vz);
    } else if (playerkeys(iPIndex, 0, "movedown")){
      changeentityproperty(vShot, "velocity", Vx, Vz);
    } else {
      changeentityproperty(vShot, "velocity", Vx, 0);
    }
    changeentityproperty(vShot, "speed", Vx);
}

void toss(void Bomb, float dx, float dy, float dz)
{ // Tossing bomb
   void self = getlocalvar("self");
   int Direction = getentityproperty(self, "direction");
   int x = getentityproperty(self, "x");
   int y = getentityproperty(self, "a");
   int z = getentityproperty(self, "z");

   if (Direction == 0){ //Is entity facing left?                  
      dx = -dx; //Reverse X direction to match facing
   }

   projectile(Bomb, x+dx, z+dz, y+dy, Direction, 0, 1, 0);
}

void toss2(void Bomb, float dx, float dy, float dz)
{ // Tossing bomb
   void self = getlocalvar("self");
   int Direction = getentityproperty(self, "direction");
   int x = getentityproperty(self, "x");
   int y = getentityproperty(self, "a");
   int z = getentityproperty(self, "z");

   if (Direction == 0){ //Is entity facing left?                  
      dx = -dx; //Reverse X direction to match facing
   }
 if (Direction == 0){ //Is entity facing left?                  
   projectile(Bomb, x+dx, z+dz, y+dy, 1, 0, 1, 0);
   }
 if (Direction == 1){ //Is entity facing left?                  
   projectile(Bomb, x+dx, z+dz, y+dy, 0, 0, 1, 0);
   }
   
   
}

void velo001(float fX, float fZ, float fY){
     
    //velo001
	//Damon Vaughn Caskey
	//05/06/2007
	//
	//Replicates movement effect.
	//
	//fX: X axis speed.
	//fZ: Z axis speed.
	//fY: Y axis speed.
	
	void vSelf = getlocalvar("self"); //Get calling entity.
	
	if (getentityproperty(vSelf, "direction")==0){ //Is entity facing right?                  
     
         fX = -fX; ////Reverse X direction to match facing.
         
    }         
	
	changeentityproperty(vSelf, "velocity", fX, fZ, fY); //Apply movement.

}


void keyflip(int Inv)
{// Change hero's facing direction if left or right is pressed
    void self = getlocalvar("self");
    int iPIndex = getentityproperty(self,"playerindex"); //Get player index

    if (Inv == 0){
      if (playerkeys(iPIndex, 0, "moveleft")){ // Left is pressed?
        changeentityproperty(self, "direction", 0); //Face left
      } else if (playerkeys(iPIndex, 0, "moveright")){ // Right is pressed?
        changeentityproperty(self, "direction", 1); //Face right
      }
    } else if (Inv == 1){
      if (playerkeys(iPIndex, 0, "moveleft")){ // Left is pressed?
        changeentityproperty(self, "direction", 1); //Face right
      } else if (playerkeys(iPIndex, 0, "moveright")){ // Right is pressed?
        changeentityproperty(self, "direction", 0); //Face left
      }
    }
}


void spawn03(void vName, float fX, float fY, float fZ, int iDir)
{
	//spawn01 (Generic spawner)
	//Damon Vaughn Caskey
	//07/06/2007
	//
	//Spawns entity next to caller.
	//
	//vName: Model name of entity to be spawned in.
	//fX: X location adjustment.
	//fY: Y location adjustment.
      //fZ: Z location adjustment.

	void self = getlocalvar("self"); //Get calling entity.
	void vSpawn; //Spawn object.
	int  iDirection = getentityproperty(self, "direction");

	clearspawnentry(); //Clear current spawn entry.
      setspawnentry("name", vName); //Acquire spawn entity by name.

	if (iDirection == 0){ //Is entity facing left?                  
          fX = -fX; //Reverse X direction to match facing.
	}

      fX = fX + getentityproperty(self, "x"); //Get X location and add adjustment.
      fY = fY + getentityproperty(self, "a"); //Get Y location and add adjustment.
      fZ = fZ + getentityproperty(self, "z"); //Get Z location and add adjustment.
	
	vSpawn = spawn(); //Spawn in entity.

	changeentityproperty(vSpawn, "position", fX, fZ, fY); //Set spawn location.

	if (iDir == 1){  
	  changeentityproperty(vSpawn, "direction", iDirection); //Set direction
        } else if (iDir == -1){  
	  if (iDirection == 0){ 
	    changeentityproperty(vSpawn, "direction", 1); //Set direction
          } else {
	    changeentityproperty(vSpawn, "direction", 0); //Set direction
          }
        }
    
	return vSpawn; //Return spawn.
}

void slamstart() // Slam Starter for Cody/Guy grabbackward
{ // Slam Starter for nongrab slams
// Use finish or throw after using this
   void self = getlocalvar("self");
   void target = getlocalvar("Target" + self);

   if(target==NULL())
   {
     target = getentityproperty(self, "opponent");
     setlocalvar("Target" + self, target);
   }
   if(target!=NULL())
   {
     damageentity(target, self, 0, 1, openborconstant("ATK_NORMAL1")); // Slam Starter
   }
}

void slamstartGRAB() // Slam Starter for Cody/Guy grabbackward
{ // Slam Starter for nongrab slams
// Use finish or throw after using this
   void self = getlocalvar("self");
   void target = getlocalvar("Target" + self);

   if(target==NULL())
   {
     target = getentityproperty(self, "opponent");
     setlocalvar("Target" + self, target);
   }
   if(target!=NULL())
   {
if (checkgrab(target)){
     damageentity(target, self, 0, 1, openborconstant("ATK_NORMAL2")); // Slam Starter
}else{
depost(0);
clearL();
 performattack(self, openborconstant("ani_attack1"));
}
   }
}

void slamSuperGRAB() // Slam Starter for Cody/Guy grabbackward
{ // Slam Starter for nongrab slams
// Use finish or throw after using this
   void self = getlocalvar("self");
   void target = getlocalvar("Target" + self);

   if(target==NULL())
   {
     target = getentityproperty(self, "opponent");
     setlocalvar("Target" + self, target);
   }
   if(target!=NULL())
   {
if (checkgrab(target)){
     damageentity(target, self, 0, 1, openborconstant("ATK_NORMAL9")); // Slam Starter
}else{
depost(0);
clearL();
 performattack(self, openborconstant("ani_attack1"));
}
   }
}



void checkgrab(void target)
{ // Opponent Checker  
// This script checks hero's current opponent. If he/she/it is biker, jetpack, special enemy or non-enemy entity this function returns 0
// Otherwise it returns 1.

   // if(getentityproperty(target, "type") == openborconstant("TYPE_ENEMY")){
      char Tname = getentityproperty(target, "defaultname");

      if(Tname == "Crate" || Tname == "Box" || Tname == "Anti" || Tname == "Tower2" || Tname == "Drum" || Tname == "car2" || Tname == "fbucket" || Tname == "fence" || Tname == "Tower")
      { return 0;} 
	else if(Tname == "General" || Tname == "Doom" || Tname == "ParedePedra" || Tname == "Secret" || Tname == "Table" || Tname == "Trash" || Tname == "Trolly")
      { return 0;} 
	else if(Tname == "Alarm" || Tname == "Solomon" || Tname == "Doom2" || Tname == "Drone" || Tname == "SuperDome" || Tname == "Ares" || Tname == "KingShark" || Tname == "IceWall")
      { return 0;} 
	else if(Tname == "Violator" || Tname == "dex" || Tname == "GLWalle" || Tname == "Plant" || Tname == "SolomonSOR" || Tname == "PlantSOR" || Tname == "BombJoker" || Tname == "EBatmobile")
      { return 0;} 
	else if(Tname == "GLWall" || Tname == "Clayface" || Tname == "Darkseid" || Tname == "AguaViva" || Tname == "Bane" || Tname == "BaneSOR" || Tname == "ClayfaceSOR" || Tname == "ClawsterB")
      { return 0;}
	else if(Tname == "veia" || Tname == "Giganta" || Tname == "Darkseid2" || Tname == "Steppenwolf" || Tname == "Scare" || Tname == "ScareSOR" || Tname == "ParallaxE2" || Tname == "ParallaxE")
      { return 0;}
	else if(Tname == "GLBox" || Tname == "Krang" || Tname == "Boxa1" || Tname == "Boxa2" || Tname == "Boxa3" || Tname == "Boxa4" || Tname == "Boxa5" || Tname == "Boxa6")
      { return 0;}
	else if(Tname == "BoxaF" || Tname == "Boxa7" || Tname == "Boxa7g" || Tname == "Table" || Tname == "BoxaNPC" || Tname == "saco" || Tname == "BoxaNPCa" || Tname == "AlienFace")
      { return 0;}
	else if(Tname == "BoxEgg" || Tname == "AlienQ" || Tname == "BoxaT" || Tname == "AlienChest" || Tname == "TankMobile" || Tname == "Boxa8" || Tname == "Boxa9" || Tname == "Boxa10")
      { return 0;}
	else if(Tname == "AlienV" || Tname == "xxx" || Tname == "xxx" || Tname == "xxx" || Tname == "xxx" || Tname == "xxx" || Tname == "xxx" || Tname == "xxx")
      { return 0;}
	else {
        return 1;
      }
    //} else {
     // return 0; 
    //}
}

void position(int Frame, float dx, float dy, float dz, int face)
{ // Modify grabbed entity's position relative to grabber
   void self = getlocalvar("self");
   void target = getlocalvar("Target" + self);

   if(target==NULL())
   {
     target = getentityproperty(self, "grabbing");
     setlocalvar("Target" + self, target);
   }
   if(target!=NULL())
   {
     updateframe(target, Frame);
     bindentity(target, self, dx, dz, dy, face, 0);
   }
}

void depost(int Gr)
{// Release grabbed entity
   void self = getlocalvar("self");
   void target = getlocalvar("Target" + self);

   if(target==NULL())
   {
     target = getentityproperty(self, "grabbing");
     setlocalvar("Target" + self, target);
   }
   if(target!=NULL())
   {
     bindentity(target, NULL());

     if(Gr == 1)
     {
       int x = getentityproperty(target, "x");
       int z = getentityproperty(target, "z");
       changeentityproperty(target, "position", x, z, 0);
     }
   }
}


void throw(int Damage, int Type, int x, int y, int z, int Face)
{ // Damage as throw finisher
   void self = getlocalvar("self");
   void target = getlocalvar("Target" + self);
   int SDir = getentityproperty(target,"direction");
   int MDir;

   if(Face==0){ // Same facing?
       MDir = SDir;
   }

   if(Face==1){ // Opposite facing?

     if(SDir==0){ // Facing left?
       MDir = 1;
     } else { MDir = 0;}
   }

   if(target==NULL())
   {
     target = getentityproperty(self, "grabbing");
     setlocalvar("Target" + self, target);
   }
   if(target!=NULL())
   {
     int dir = getentityproperty(target,"direction"); //Get opponent's facing direction
     if(dir==0){ // Facing left?
       x = -x;
     }

     if(Type==1)
     {
       damageentity(target, self, 0, 1, openborconstant("ATK_NORMAL1")); // 1st throw type
     }

     if(Type==2)
     {
       damageentity(target, self, 0, 1, openborconstant("ATK_NORMAL1")); // 2nd throw type
     }

     if(Type==3)
     {
       damageentity(target, self, 0, 1, openborconstant("ATK_NORMAL1")); // 3rd throw type
     }

     changeentityproperty(target, "attacking", 1);
     changeentityproperty(target, "damage_on_landing", Damage);
     changeentityproperty(target, "projectile", 1);
     changeentityproperty(target, "direction", MDir);
     tossentity(target, y, x, z); // Toss opponent ;)
   }
}
