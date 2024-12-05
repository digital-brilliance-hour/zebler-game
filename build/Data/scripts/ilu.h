void hpcost( int HCost)
{// Spend some life
    void self = getlocalvar("self");
    void Life = getentityproperty(self,"health"); //get health
if (Life > HCost){ //Does the entity have enough health?
       changeentityproperty(self, "health", Life-HCost);//consume health
      } 

}




void paleta(int Pal)
{// 
    void self = getlocalvar("self"); //Get calling entity.
    int oPal = getentityproperty(self, "mapdefault");

    if (Pal > 0){
	changeentityproperty(self, "colourmap", Pal);
   }
	else{
changeentityproperty(self, "colourmap", oPal);

}

}

void regen (int regH)
{// Spend some life
    void self = getlocalvar("self");// get caller
    void Life = getentityproperty(self,"health"); //get health
    changeentityproperty(self, "health", Life+regH);//add health
}

void checkPal(void Ani, int Remap)
{// Attack interruption if there's player
// Only occurs if remap matches
    void self = getlocalvar("self");
    int Map = getentityproperty(self, "map");
    void target = findtarget(self); //Find player

    if(target!=NULL() && Map!=Remap){
      performattack(self, openborconstant(Ani)); //Attack!
    }
}

void spawnAni(void vName, float fX, float fY, float fZ, void Ani, float Vx, float Vy, float Vz)
{
	//spawnB (Generic spawner) + Specific animation + velocities
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
    	performattack(vSpawn, openborconstant(Ani)); 
	changeentityproperty(vSpawn, "velocity", Vx, Vy, Vz);

	return vSpawn; //Return spawn.
}
void spawn000(void vName, float fX, float fY, float fZ)
{
	//spawn01 (Generic spawner) without direction
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

      fX = fX + getentityproperty(self, "x"); //Get X location and add adjustment.
      fY = fY + getentityproperty(self, "a"); //Get Y location and add adjustment.
      fZ = fZ + getentityproperty(self, "z"); //Get Z location and add adjustment.
	
	vSpawn = spawn(); //Spawn in entity.

	changeentityproperty(vSpawn, "position", fX, fZ, fY); //Set spawn location.
    
	return vSpawn; //Return spawn.
}

void teleportentityrandomlyonscreen(int screenwidth)
{
  //MatMan v0.02
  //Screenwidth needs to be put in manually as openborcvarial hresolution doesn't work
	void self = getlocalvar("self");
  int ichancex = 0;
  int ichancey = 0;
  ichancex = rand()%screenwidth;
  if (ichancex < 0) { ichancex = -ichancex ;}
  ichancex = ichancex + openborvariant("xpos");
  ichancey = rand()%screenwidth;
  if (ichancey < 0) { ichancey = -ichancey ;}
  ichancey = ichancey + openborvariant("ypos");// + openborvariant("PLAYER_MIN_Z");
  changeentityproperty(self, "position", ichancex, getentityproperty(self, "z"), getentityproperty(self, "a"));

  //TODO: Need to set it that it randomly place's the entity along the z plane.
  //changeentityproperty(self, "position", ichancex, ichancey, getentityproperty(self, "a"));

  //changeentityproperty(self, "position", fx, fz, fy);
  //openborvariant("PLAYER_MIN_Z");
  //openborvariant("PLAYER_MAX_Z");
  return self;
}


void randomteleonscreen()
{// Randomly teleports onscreen

    void self = getlocalvar("self"); //Get calling entity
    int XPos = openborvariant("xpos"); //Get screen edge's position
    int Screen = openborvariant("hResolution"); // Get screen width
    int Width = openborvariant("PLAYER_MAX_Z") - openborvariant("PLAYER_MIN_Z"); // Get width
    int iRx = rand()%(Screen/2) + Screen/2 ;
    int iRz;

    iRz = rand()%(Width/2) + Width/2 ;

    changeentityproperty(self, "position", iRx + XPos, iRz + openborvariant("PLAYER_MIN_Z")); //Randomly teleport
}

void fixRandom()
{// Randomly teleports onScreenB

    void self = getlocalvar("self"); //Get calling entity
    int XPosB = openborvariant("XPos"); //Get ScreenB edge's position
    int ScreenB = openborvariant("hResolution"); // Get ScreenB WidthB
    int WidthB = openborvariant("PLAYER_MAX_Z") - openborvariant("PLAYER_MIN_Z"); // Get WidthB
    int iRxB = rand()%(ScreenB/2) + ScreenB/2 ;
    int iRzB;

    iRzB = rand()%(WidthB/2) + WidthB/2 ;

    changeentityproperty(self, "position", iRxB + XPosB, iRzB + openborvariant("PLAYER_MIN_Z")); //Randomly teleport
}


void antiwallCollide(int Dist, void Ani)
{// Checks if there is wall at defined distance (Dist)
// If there is wall, change animation to Ani
   void self = getlocalvar("self");
   int Direction = getentityproperty(self, "direction");
   int x = getentityproperty(self, "x");
   int y = getentityproperty(self, "a");
   int z = getentityproperty(self, "z");
   float H;

   if (Direction == 0){ //Is entity facing left?                  
      Dist = -Dist; //Reverse Dist to match facing
   }

   H = checkwall(x+Dist,z);
   if(H > y)
   {
      changeentityproperty(self, "animation", openborconstant(Ani));
   }
}

void antiwallRandom(int Dist)
{// Checks if there is wall at defined distance (Dist)
// If there is wall, change to random position to avoid landing on walls
   void self = getlocalvar("self");
   int Direction = getentityproperty(self, "direction");
   int x = getentityproperty(self, "x");
   int y = getentityproperty(self, "a");
   int z = getentityproperty(self, "z");
   float H;

   if (Direction == 0){ //Is entity facing left?                  
      Dist = -Dist; //Reverse Dist to match facing
   }

   H = checkwall(x+Dist,z);
   if(H > y)
   {
    //   void self = getlocalvar("self"); //Get calling entity
    //int XPos = openborvariant("xpos"); //Get screen edge's position
    //int Screen = openborvariant("hResolution"); // Get screen width
    //int Width = openborvariant("PLAYER_MAX_Z") - openborvariant("PLAYER_MIN_Z"); // Get width
    //int iRx = rand()%(Screen/2) + Screen/2 ;
    //int iRz;

    //iRz = rand()%(Width/2) + Width/2 ;

    //changeentityproperty(self, "position", iRx + XPos, iRz + openborvariant("PLAYER_MIN_Z")); //Randomly teleport
	randomteleonscreen();

   }
}
void randomJump (int vx, int vy)
{
	// Douglas Baldan / O Ilusionista
	// version 1.0 - 23/07/13
	// makes the entity execute a jump into a random direction
      void vSelf = getlocalvar("self"); // Gets the caller
      int Xr = rand()%vx;	// Random X vel, between the chosen velocity
      int Yr = 2+rand()%vy;	// Random Y vel + 1, to ensure a vertical jump, between the chosen velocity
      if (Yr <0){			// If the Y is negative,
		Yr = Yr*-1;			// Make it positive
      }
      changeentityproperty(vSelf, "velocity", Xr, 0, Yr); // Change entity velocity
       }
//void randomPitch (void iSample, int basePitch, int rangePitch)
//{
//int iPitch = basePitch+(rand()%rangePitch);
//if (iPitch <0){iPitch = iPitch *-1}
//int iSound = loadsample(iSample);
//playsample(iSound, 0, openborvariant("effectvol"), openborvariant("effectvol"), iPitch, 0)
//}