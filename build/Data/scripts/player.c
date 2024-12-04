#import "data/scripts/library/spawn.h"
#import "data/scripts/library/basic.h"

void keyint(void Ani, int Frame, void Key, int Hflag)
{// Change current animation if proper key is pressed or released
// Animation is changed to attack mode

    void self = getlocalvar("self");
    int Dir = getentityproperty(self, "direction");
    int iPIndex = getentityproperty(self,"playerindex"); //Get player index
    void iRKey;

      if (Key=="U"){ //Up Required?
        iRKey = playerkeys(iPIndex, 0, "moveup"); // "Up"
      } else if (Key=="D"){ //Down Required?
        iRKey = playerkeys(iPIndex, 0, "movedown"); // "Down"
      } else if (Key=="L"){ //Left Required?
        iRKey = playerkeys(iPIndex, 0, "moveleft"); // "Left"
      } else if (Key=="R"){ //Right Required?
        iRKey = playerkeys(iPIndex, 0, "moveright"); // "Right"
      } else if (Key=="F"){ //Forward Required?
        if (Dir == 0){ // Facing Left?
          iRKey = playerkeys(iPIndex, 0, "moveleft"); // "Left"
        } else { // Facing Right
          iRKey = playerkeys(iPIndex, 0, "moveright"); // "Right"
        }
      } else if (Key=="B"){ //Backward Required?
        if (Dir == 1){ // Facing Right?
          iRKey = playerkeys(iPIndex, 0, "moveleft"); // "Left"
        } else { // Facing Left
          iRKey = playerkeys(iPIndex, 0, "moveright"); // "Right"
        }
      } else if (Key=="J"){ //Jump Required?
        iRKey = playerkeys(iPIndex, 0, "jump"); // "Jump"
      } else if (Key=="A"){ //Attack Required?
        iRKey = playerkeys(iPIndex, 0, "attack"); // "Attack"
      } else if (Key=="S"){ //Special Required?
        iRKey = playerkeys(iPIndex, 0, "special"); // "Special"
      }

      if (Hflag==1){ //Not holding the button case?
        iRKey = !iRKey; //Take the opposite condition
      }

      if (iRKey){
        if (Ani=="ANI_IDLE"){ // Going idle?
          setidle(self, openborconstant("ANI_IDLE")); //Be idle!
        } else {
          performattack(self, openborconstant(Ani)); //Change the animation
        }
        updateframe(self, Frame); //Change frame
      }
}

void keymove(float Vx)
{// Move hero if direction button is pressed
      void self = getlocalvar("self");
      int iPIndex = getentityproperty(self,"playerindex"); //Get player index
	float xdir = 0;

      if (playerkeys(iPIndex, 0, "moveleft")){// Left is pressed?
	  xdir = -Vx;
	} else if(playerkeys(iPIndex, 0, "moveright")){// Right is pressed?
	  xdir = Vx;
      }

	changeentityproperty(self, "velocity", xdir);
}

void keyfly(float V)
{// Move hero if direction button is pressed
    void self = getlocalvar("self");
    int iPIndex = getentityproperty(self,"playerindex"); //Get player index
    int a = getentityproperty(self,"a"); //Get player's altitude
    int Atap = getglobalvar("Atap");
    float xdir = 0;
    float ydir = 0;

    if(playerkeys(iPIndex, 0, "moveleft")){ // Left is pressed?
      xdir = -V;
    } else if(playerkeys(iPIndex, 0, "moveright")){ // Right is pressed?
      xdir = V;
    }

    if(playerkeys(iPIndex, 0, "moveup") && (a <= Atap)){ // Up is pressed?
      ydir = V;
    } else if(playerkeys(iPIndex, 0, "movedown") && (a >= 0)){ // Down is pressed?
      ydir = -V;
    }

    changeentityproperty(self, "velocity", xdir, 0, ydir);
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

void keyshootA(float dx, float dy, float V, int Time, int Flag)
{// Shoot directed projectile based on pressed direction button
//Only fires if Attack1 button is held
    void self = getlocalvar("self");
    int iDir = getentityproperty(self, "direction");
    int iPIndex = getentityproperty(self,"playerindex"); //Get player index
    int TPhase = getentityvar(self, 0);
    int SFX = loadsample("data/sounds/shoot.wav");
    void iForwardH; void iBackwardH; int R;

    if(iDir == 0){ // Facing Left?
      iForwardH = playerkeys(iPIndex, 0, "moveleft"); // "Left"
      iBackwardH = playerkeys(iPIndex, 0, "moveright"); // "Right"
    } else { // Facing Right
      iForwardH = playerkeys(iPIndex, 0, "moveright"); // "Right"
      iBackwardH = playerkeys(iPIndex, 0, "moveleft"); // "Left"
    }

    if(playerkeys(iPIndex, 0, "attack")){
      if(TPhase != NULL() && TPhase <= openborvariant("elapsed_time")){
        setentityvar(self, 0, NULL());
        TPhase = NULL();
      }
      if(TPhase == NULL()){
        playsample(SFX, 0, 120, 120, 100, 0);
        setentityvar(self, 0, openborvariant("elapsed_time") + 2*Time);

        if(Flag == 1){
	  R = getentityvar(self, 1);

          if(R == NULL()){
	    R = 0;
          }
        } else {
          if(playerkeys(iPIndex, 0, "moveup")){// Up is pressed?
            if(iBackwardH){
	      R = 135;
            } else if(iForwardH){
	      R = 45;
            } else {
	      R = 90;
            }
          } else if(playerkeys(iPIndex, 0, "movedown")){// Down is pressed?
            if(iBackwardH){
	      R = 225;
            } else if(iForwardH){
	      R = 315;
            } else {
	      R = 270;
            }
          } else {
            if(iBackwardH){
  	      R = 180;
            } else {
	      R = 0;
            }
          }
	  setentityvar(self, 1, R);
        }
        WShoot(dx, dy, V, R);
      }
      setglobalvar("A1", 1);
    } else {
      setglobalvar("A1", NULL());
    }
}

void keyshootH(float dx, float dy, float V, int Time)
{// Shoot directed projectile based on last shot direction (for strafing)
//Only fires if Attack1 button is held
  void self = getlocalvar("self");
  void KeyH = getglobalvar("A1");

  if(KeyH!=NULL()){
    keyshootA(dx, dy, V, Time, 1);
  } else {
    keyshootA(dx, dy, V, Time, 0);
  }
}

void WShoot(float dx, float dy, float V, int R)
{ // Shoots defined projectile based on current weapon power
    int WP = getglobalvar("WP");
    int Sy = cos(R);
    int Sx = sin(R);

    if(WP >= 6){
      shooterAngle("Bit2", dx-7*Sx, dy+7*Sy, V, R+10);
      shooterAngle("Bit2", dx, dy, V, R);
      shooterAngle("Bit2", dx+7*Sx, dy-7*Sy, V, R-10);
    } else if(WP==5){
      shooterAngle("Bit1", dx-10*Sx, dy+10*Sy, V, R+10);
      shooterAngle("Bit2", dx-5*Sx, dy+5*Sy, V, R);
      shooterAngle("Bit1", dx+5*Sx, dy-5*Sy, V, R);
      shooterAngle("Bit1", dx+10*Sx, dy-10*Sy, V, R-10);
    } else if(WP==4){
      shooterAngle("Bit1", dx-7*Sx, dy+7*Sy, V, R+10);
      shooterAngle("Bit2", dx, dy, V, R);
      shooterAngle("Bit1", dx+7*Sx, dy-7*Sy, V, R-10);
    } else if(WP==3){
      shooterAngle("Bit2", dx-5*Sx, dy+5*Sy, V, R);
      shooterAngle("Bit1", dx+5*Sx, dy-5*Sy, V, R);
    } else if(WP==2){
      shooterAngle("Bit2", dx, dy, V, R);
    } else {
      shooterAngle("Bit1", dx, dy, V, R);
    }
}

void keyshild(float dx, float dy, float V, int Time)
{// Shoots shield pieces
//Only fires if Attack2 button is held
    void self = getlocalvar("self");
    int iDir = getentityproperty(self, "direction");
    int iPIndex = getentityproperty(self,"playerindex"); //Get player index
    int TPhase = getentityvar(self, 0);
    int SFX = loadsample("data/sounds/spark.wav");
    void Sild;

    if(playerkeys(iPIndex, 0, "attack2")){
      if(TPhase != NULL() && TPhase <= openborvariant("elapsed_time")){
        setentityvar(self, 0, NULL());
        TPhase = NULL();
      }
      if(TPhase == NULL()){
        playsample(SFX, 0, 120, 120, 100, 0);
        setentityvar(self, 0, openborvariant("elapsed_time") + 2*Time);

        shooter("BhildU", dx, dy, 0, V);
        shooter("BhildS", dx, dy, V, 0);
        shooter("BhildD", dx, dy, 0, -V);
        Sild = shooter("BhildS", dx, dy, -V, 0);

        changeentityproperty(Sild, "direction", 0);
      }
    }
}

void keyshoot(void Shot, float dx, float dy, float V, int Time)
{// Shoot projectile forward
//Only fires if Attack1 button is held
    void self = getlocalvar("self");
    int TPhase = getentityvar(self, 0);
    int iPIndex = getentityproperty(self,"playerindex"); //Get player index
    int SFX = loadsample("data/sounds/shoot.wav");

    if(playerkeys(iPIndex, 0, "attack")){
      if(TPhase != NULL() && TPhase <= openborvariant("elapsed_time")){
        setentityvar(self, 0, NULL());
        TPhase = NULL();
      }
      if(TPhase == NULL()){
        playsample(SFX, 0, 120, 120, 100, 0);
        setentityvar(self, 0, openborvariant("elapsed_time") + 2*Time);

        shooterAngle(Shot, dx, dy, V, 0);
      }
    }
}
