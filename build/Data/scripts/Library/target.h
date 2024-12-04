//Library scripts for targetting

void target0(float Velx, float Vely, float Tx, float Ty, float dx, float dy, void Vel, int Flip)
{// Basic Targetting certain coordinate before dashing
// Velx = Desired x Velocity
// Vely = Desired y Velocity
// Tx = target x coordinate
// Ty = target y coordinate
// dx = x added distance
// dy = y added distance
// Vel = Desired output

    void self = getlocalvar("self");
    int dir = getentityproperty(self, "direction");
    float x = getentityproperty(self, "x");
    float y = getentityproperty(self, "a");
    float Vx;
    float Vy;

    if(Flip == 1){
      if(Tx < x){
        changeentityproperty(self, "direction", 0);
      } else {
        changeentityproperty(self, "direction", 1);
      }
    }

    x = x+dx;
    y = y+dy;
    float Disx = Tx - x;
    float Disy = Ty - y;

//Set both distance as positive value
    if(Disx < 0){
      Disx = -Disx;
    }

    if(Disy < 0){
      Disy = -Disy;
    }

// Calculate velocity for targetting
    if(Disy < Disx)
    {
      if(Tx < x){
        Vx = -Velx;
      } else { Vx = Velx; }

      Vy = Velx*(Ty-y)/Disx;
    } else {
      if(Ty < y){
        Vy = -Vely;
      } else { Vy = Vely; }

      Vx = Vely*(Tx-x)/Disy;
    }

    if(Vel == "x"){
      return Vx;
    }
    if(Vel == "y"){
      return Vy;
    }
}

void target1(void Target, float Velx, float Vely, float dx, float dy, int Stop, void Vel, int Flip)
{// Targetting certain entity before dashing
// Target = Targetted entity
// Velx = Desired x Velocity
// Vely = Desired y Velocity
// dx = x added distance
// dy = y added distance
// Stop = flag to stop moving if there's no target

    void self = getlocalvar("self");
    int dir = getentityproperty(self, "direction");
    float x = getentityproperty(self, "x");
    float y = getentityproperty(self, "a");
    float Vx;
    float Vy;

    if (dir == 0){ //Is entity facing left?                  
      dx = -dx; //Reverse X direction to match facing
    }

    if( Target != NULL()){
      float Tx = getentityproperty(Target, "x");
      float Ty = getentityproperty(Target, "a");

      Vx = target0(Velx, Vely, Tx, Ty, dx, dy, "x", Flip);
      Vy = target0(Velx, Vely, Tx, Ty, dx, dy, "y", Flip);
    } else {
      if(Stop == 1){
        Vy = 0;
        Vx = 0;
      } else if(Stop == 2){
        Vy = NULL();
        Vx = NULL();
      } else {
        Vy = 0;
        if(dir==0){
          Vx = -Velx;
        } else { Vx = Velx; }
      }
    }

    if(Vel == "x"){
      return Vx;
    }
    if(Vel == "y"){
      return Vy;
    }
}

void target0T(float Time, float Tx, float Ty, float dx, float dy, void Vel, int Flip)
{// Basic Targetting certain coordinate before dashing
// Produced velocity will be required speed to get to target within specified time
// Time = specified time
// Tx = target x coordinate
// Ty = target y coordinate
// dx = x added distance
// dy = y added distance
// Vel = Desired output

    void self = getlocalvar("self");
    int dir = getentityproperty(self, "direction");
    float x = getentityproperty(self, "x");
    float y = getentityproperty(self, "a");
    float Vx;
    float Vy;

    if(Flip == 1){
      if(Tx < x){
        changeentityproperty(self, "direction", 0);
      } else {
        changeentityproperty(self, "direction", 1);
      }
    }

    x = x+dx;
    y = y+dy;
// Calculate velocity for targetting

    Vx = (Tx-x)/Time;
    Vy = (Ty-y)/Time;

    if(Vel == "x"){
      return Vx;
    }
    if(Vel == "y"){
      return Vy;
    }
}

void target1T(void Target, float Time, float dx, float dy, void Vel, int Flip)
{// Targetting certain entity before dashing
// Produced velocity will be required speed to get to target within specified time
// Target = Targetted entity
// Time = Specified time
// dx = x added distance
// dy = y added distance

    void self = getlocalvar("self");
    int dir = getentityproperty(self, "direction");
    float x = getentityproperty(self, "x");
    float y = getentityproperty(self, "a");
    float Vx;
    float Vy;

    if (dir == 0){ //Is entity facing left?                  
      dx = -dx; //Reverse X direction to match facing
    }

    if( Target != NULL()){
      float Tx = getentityproperty(Target, "x");
      float Ty = getentityproperty(Target, "a");

      Vx = target0T(Time, Tx, Ty, dx, dy, "x", Flip);
      Vy = target0T(Time, Tx, Ty, dx, dy, "y", Flip);
    } else {
      Vy = 0;
      Vx = 0;
    }

    if(Vel == "x"){
      return Vx;
    }
    if(Vel == "y"){
      return Vy;
    }
}

void target(float Velx, float Vely, float dx, float dy, int Stop, int Flip)
{// Targetting opponent before leaping or dashing.
// Velx = x Velocity
// Vely = y Velocity
// dx = x added distance
// dy = y added distance
// Stop = flag to stop moving if no target is found

    void self = getlocalvar("self");

    setlocalvar("T"+self, findtarget(self)); //Get nearest player

    void target = getlocalvar("T"+self);
    setlocalvar("x"+self, target1(target, Velx, Vely, dx, dy, Stop, "x", Flip) );
    setlocalvar("y"+self, target1(target, Velx, Vely, dx, dy, Stop, "y", Flip) );
    setlocalvar("T"+self, NULL()); //Clears variable
}

void targetT(float Time, float dx, float dy, int Flip)
{// Targetting opponent before leaping or dashing.
// Time = specified time
// dx = x added distance
// dy = y added distance

    void self = getlocalvar("self");

    setlocalvar("T"+self, findtarget(self)); //Get nearest player

    void target = getlocalvar("T"+self);
    setlocalvar("x"+self, target1T(target, Time, dx, dy, "x", Flip) );
    setlocalvar("y"+self, target1T(target, Time, dx, dy, "y", Flip) );
    setlocalvar("T"+self, NULL()); //Clears variable
}

void targetB(float Time, float dx, float dy, int Flip)
{// Targetting opponent before tossing bomb
// Time = specified time
// dx = x added distance
// dy = y added distance
// Flip = flip flag

    void self = getlocalvar("self");
    int dir = getentityproperty(self, "direction");
    float x = getentityproperty(self, "x");
    float y = getentityproperty(self, "a");
    float Vx;

    setlocalvar("T"+self, findtarget(self)); //Get nearest target
    void Target = getlocalvar("T"+self);

    if( Target != NULL()){
      float Tx = getentityproperty(Target, "x");
      float Ty = getentityproperty(Target, "a");
      float C;
      float Sy = y + dy - Ty;

      if (Sy < 0){ //Negative?
        Sy = -Sy; //Invert to positive
      }

      C = 0.5*(x-Tx)*(y+dy-Ty)/(Time+Sy);

      if (dir == 0){ //Is entity facing left?                  
        dx = -dx; //Reverse X direction to match facing
      }

      Vx = target0T(Time, Tx, Ty, dx-C, 0, "x", Flip);

    } else {
      Vx = 0;
    }

    setlocalvar("x"+self, Vx );
    setlocalvar("T"+self, NULL()); //Clears variable
}

void dash(int X, int Y)
{// Dash with previously attained speed!
    void self = getlocalvar("self");
    float Vx = getlocalvar("x"+self);
    float Vy = getlocalvar("y"+self);

    if( Vx!=NULL() && Vy!=NULL() ){
      if( X==1 ){
        Vy = 0;
      } else if( Y==1 ){
        Vx = 0;
      }

      changeentityproperty(self, "velocity", Vx, 0, Vy);
    }
}

void leap()
{// Leap with previously attained speed!
    void self = getlocalvar("self");
    float Vx = getlocalvar("x"+self);
    float Vy = getlocalvar("y"+self);

    if( Vx!=NULL() && Vy!=NULL() ){
      tossentity(self, Vy, 2*Vx); //Leap towards target!
    }
}

void leapMax(float VM)
{// Leap with previously attained speed!
// Max velocity applied
    void self = getlocalvar("self");
    float Vx = getlocalvar("x"+self);
    float Vy = getlocalvar("y"+self);

    if( Vx!=NULL() && Vy!=NULL() ){
      if(2*Vx>=VM){
        Vx = VM/2;
      }

      tossentity(self, Vy, 2*Vx); //Leap towards target!
    }
}

void shootT(void Shot, float dx, float dy)
{ // Shooting targetted projectile
   void self = getlocalvar("self");
   float Vx = getlocalvar("x"+self);
   float Vy = getlocalvar("y"+self);
   void vShot;

   if( Vx!=NULL() && Vy!=NULL() ){
     vShot = shooter(Shot, dx, dy, Vx, 2*Vy);
     changeentityproperty(vShot, "velocity", Vx, 0, 2*Vy);
   }
}

void turnT(float D, int Inv, int Flag, int dA)
{// Turn to targetted opponent
// D : Initial deviation
// Inv : Inverted flag
// Flag : Instant flag, 0 = instant, 1 = gradual
// Need to reset drawmethod first before using this
   void self = getlocalvar("self");
   float Vx = getlocalvar("x"+self);
   float Vy = getlocalvar("y"+self);
   float Angle = getlocalvar("Angle"+self);
   float R;

   if(Angle == NULL()){
     Angle = 0;
     setlocalvar("Angle"+self, 0);
   }

   if( Vx!=NULL() && Vy!=NULL() ){
     R = antitang2(Vy, Vx);

     if(Flag == 1){
       Angle = 360 - Angle;

       if(R - Angle > 180){
         R = R - 360;
       } else if(R - Angle < -180){
         R = R + 360;
       }

       if(R <= Angle){
         dA = -dA;
       }
       turnA(dA, Inv);
     } else {
       turn(R, D, Inv);
     }
   }
}

void shootTD(void Shot, float dx, float dy, float R)
{ // Shooting targetted projectile with deviation
   void self = getlocalvar("self");
   float Vx = getlocalvar("x"+self);
   float Vy = getlocalvar("y"+self);
   float V;
   float Sx;
   float Sy;
   void vShot;
   float Angle;

   if( Vx!=NULL() && Vy!=NULL() ){
     Angle = antitang2(Vy, Vx);
     V = sqrt(Vx*Vx+Vy*Vy);
     Sx = V*cos(Angle+R);
     Sy = V*sin(Angle+R);

     vShot = shooter(Shot, dx, dy, Sx, 2*Sy);
     changeentityproperty(vShot, "velocity", Sx, 0, 2*Sy);
   }
}

void shootTA(void Shot, float dx, float dy, float R)
{ // Shooting targetted projectile with certain angle
   void self = getlocalvar("self");
   float Vx = getlocalvar("x"+self);
   float Vy = getlocalvar("y"+self);
   int Dir = getentityproperty(self, "direction");
   float V; float Angle;

   if(Dir == 0){
     Vx = -Vx;
   }

   if( Vx!=NULL() && Vy!=NULL() ){
     Angle = antitang2(Vy, Vx);
     V = sqrt(Vx*Vx+Vy*Vy);

     shooterAngle(Shot, dx, dy, V, Angle+R);
   }
}

void tossT(void Shot, float dx, float dy, float Vy)
{ // Tossing targetted bombs
   void self = getlocalvar("self");
   float Vx = getlocalvar("x"+self);
   int Direction = getentityproperty(self, "direction");

   if (Direction == 0){ //Is entity facing left?                  
      Vx = -Vx; //Reverse Vx direction to match facing
   }

   if( Vx!=NULL() && Vy!=NULL() ){
     shooter(Shot, dx, dy, Vx, Vy);
   }
}
