//Library scripts for spawning

void spawn01(void vName, float fX, float fY, float fZ)
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
	changeentityproperty(vSpawn, "direction", iDirection); //Set direction.
    
	return vSpawn; //Return spawn.
}

void spawn02(void vName, float fX, float fY, float fZ)
{
	//Spawns entity based on left screen edge
	//
	//vName: Model name of entity to be spawned in.
	//fX: X distance relative to left edge
	//fY: Y height from ground
      //fZ: Z location adjustment

	void self = getlocalvar("self"); //Get calling entity.
	void vSpawn; //Spawn object.
	int Direction = getentityproperty(self, "direction");
        int XPos = openborvariant("xpos"); //Get screen edge's position
        int Screen = openborvariant("hResolution"); // Get screen width

	clearspawnentry(); //Clear current spawn entry.
      setspawnentry("name", vName); //Acquire spawn entity by name.

   if (Direction == 0){ //Is entity facing left?                  
      fX = Screen-fX; //Reverse X direction to match facing and screen length
   }

      fZ = fZ + getentityproperty(self, "z"); //Get Z location and add adjustment.

	vSpawn = spawn(); //Spawn in entity.

	changeentityproperty(vSpawn, "position", fX + XPos, fZ, fY); //Set spawn location.
	return vSpawn; //Return spawn.
}

void spawn03(void vName, float fX, float fY, float fZ, int Dir)
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
	//Dir: Direction setting

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
	changeentityproperty(vSpawn, "direction", Dir); //Set direction.
    
	return vSpawn; //Return spawn.
}

void spawner(void vName, float fX, float fY, float fZ)
{	//Spawns entity next to caller and set them as child.
	//
	//vName: Model name of entity to be spawned in.
	//fX: X location adjustment.
	//fY: Y location adjustment.
      //fZ: Z location adjustment.

	void self = getlocalvar("self"); //Get calling entity.
	void vSpawn; //Spawn object.
	
	vSpawn = spawn01(vName, fX, fY, fZ); //Spawn in entity.

	changeentityproperty(vSpawn, "parent", self); //Set caller as parent.
    
	return vSpawn; //Return spawn.
}

void shooter(void Shot, float dx, float dy, float Vx, float Vy)
{ // Shooting special projectile with speed control
   void self = getlocalvar("self");
   int Direction = getentityproperty(self, "direction");
   void vShot;

   if (Direction == 0){ //Is entity facing left?                  
      Vx = -Vx; //Reverse Vx direction to match facing
   }

   vShot = spawn01(Shot, dx, dy, 0);
   changeentityproperty(vShot, "velocity", Vx, 0, Vy);
   changedrawmethod(vShot, "reset", 1);
   return vShot;
}

void shooterM(void Shot, float dx, float dy, float Vx, float Vy)
{ // Shooting special projectile with speed control and matches its map with own's map
   void self = getlocalvar("self");
   int map = getentityproperty(self,"map");
   void Spawn;

   Spawn = shooter(Shot, dx, dy, Vx, Vy);

   if(map != 1){
     changeentityproperty(Spawn, "map", map);
   }
}

void shooterAngle(void Shot, float dx, float dy, float V, int Angle)
{ // Shooting special projectile with speed control at defined Angle
   void self = getlocalvar("self");
   int Direction = getentityproperty(self, "direction");
   int Vx = V*cos(Angle);
   int Vy = 2*V*sin(Angle);
   void vShot;

   vShot = shooter(Shot, dx, dy, Vx, Vy);

   if (Direction == 1){
     Angle = 360-Angle;
   }

   if(Angle >= 360){
     Angle = Angle-360;
   } else if(Angle < 0){
     Angle = Angle+360;
   }

   changedrawmethod(vShot, "rotate", Angle);
   return vShot;
}
