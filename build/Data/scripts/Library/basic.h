//Library scripts for basic functions

void platform(int Flag)
{// Turns subject's platform status
    void self = getlocalvar("self");
    changeentityproperty(self, "Subject_to_Platform", Flag);
}

void layer(int layer)
{// Set's enemy's layer
    void self = getlocalvar("self");
    changeentityproperty(self, "setlayer", layer);
}

void offscreenkill( float dx, int E )
{// Check position relative to screen. If enemy is offscreen, suicide!
//  dx : Distance to screen edge
//  E  : Edge selection, 0 = left, 1 = right

    void self = getlocalvar("self");
    int x = getentityproperty(self,"x"); //Get character's x coordinate
    int XPos = openborvariant("xpos"); //Get screen edge's position
    int Screen = openborvariant("hResolution"); // Get screen width

    if( (x > XPos + Screen + dx) && (E == 1) ){ // Offscreen to the right?
      killentity(self); //Suicide!
    } else if( (x < XPos - dx) && (E == 0) ){ // Offscreen to the left?
      killentity(self); //Suicide!
    }
}

void offroomkill(float dx)
{// Check position relative to room. If enemy is offroom, suicide!
//  dx : Distance to room edge

    void self = getlocalvar("self");
    int x = getentityproperty(self,"x"); //Get character's x coordinate
    int Width = openborvariant("levelwidth"); // Get room width

    if( x > Width + dx ){ // Offroom to the right?
      killentity(self); //Suicide!
    } else if( x < -dx ){ // Offroom to the left?
      killentity(self); //Suicide!
    }
}

void floater( int Time )
{// Floats in Time centiseconds
    void self = getlocalvar("self");
    int eTime = openborvariant("elapsed_time");

    changeentityproperty(self, "tosstime", eTime + 2*Time);
}

void beidle()
{// Go to IDLE animation!
    void self = getlocalvar("self");

    setidle(self, openborconstant("ANI_IDLE"));
}

void suicide()
{ // Suicide!!
    void self = getlocalvar("self");

    killentity(self); //Suicide!
}

void move(int dx, int dz, int da, int Flip)
{ // Moves entity freely or ignores obstacles
    void self = getlocalvar("self");
    int x = getentityproperty(self,"x"); //Get character's x coordinate
    int z = getentityproperty(self,"z"); //Get character's z coordinate
    int a = getentityproperty(self,"a"); //Get character's a coordinate
    int dir = getentityproperty(self,"direction"); //Get character's facing direction

    if(dir==0 && Flip==1){ // Facing left?
      dx = -dx ;
    }

    changeentityproperty(self, "position", x+dx, z+dz, a+da); //Move
}

void flip()
{// Flip to opposite direction
    void self = getlocalvar("self");
    int dir = getentityproperty(self,"direction");

    if(dir==0){ // Facing left?
      changeentityproperty(self, "direction", 1);
    } else {
      changeentityproperty(self, "direction", 0);
    }
}

void anichange(void Ani)
{ // Animation changer
    void self = getlocalvar("self");

    changeentityproperty(self, "animation", openborconstant(Ani)); //Change the animation
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
      setlocalvar("Loop" + self, loop+1); // Increment number of loops
      updateframe(self, Frame); //Change frame
    } else if(loop==Limit){ // loops reach limit?
      setlocalvar("Loop" + self, NULL());
    }
}

void degravity(int Ratio)
{// Changes antigravity effect
    void self = getlocalvar("self");
    changeentityproperty(self, "antigravity", Ratio);
}

void clearL()
{ // Clears all local variables
     clearlocalvar();
}

void dasher( float Vx, float Vy, int Flip)
{// Dash with desired speed!
    void self = getlocalvar("self");
    int dir = getentityproperty(self,"direction");

    if(dir==0 && Flip==1){ // Facing left?
      Vx = -Vx ;
    }

    changeentityproperty(self, "velocity", Vx, 0, Vy); //Move!
}

void leaper( float Vx, float Vy, int Flip)
{// Leap with desired speed!
    void self = getlocalvar("self");
    int dir = getentityproperty(self,"direction");

    if(dir==0 && Flip==1){ // Facing left?
      Vx = -Vx ;
    }

    tossentity(self, Vy, Vx); //Leap!
}

void turn(int Angle, float D, int Inv)
{// Turn to defined Angle in degrees
// D : Initial deviation
// Inv : Inverted flag
// Need to reset drawmethod first before using this
   void self = getlocalvar("self");
   float R;

   if(Inv == 1){
     R = 180 - Angle + D;
   } else {
     R = D - Angle;
   }

   if(R < 0){
     R = R + 360; // to "positivate" R
   } else if(R >= 360){
     R = R - 360; // to put R under 360
   }

   changedrawmethod(self, "rotate", R);
   setlocalvar("Angle"+self, R);
}

void turnA(int Angle, int Inv)
{// Turn with defined Angle in degrees
// Need to reset drawmethod first before using this
   void self = getlocalvar("self");
   int D = getlocalvar("Angle"+self);
   float R;

   if(D == NULL()){
     D = 0;
     setlocalvar("Angle"+self, 0);
   }

   if(Inv == 1){
     R = 180 - Angle + D;
   } else {
     R = D - Angle;
   }

   if(R < 0){
     R = R + 360; // to "positivate" R
   } else if(R >= 360){
     R = R - 360; // to put R under 360
   }

   changedrawmethod(self, "rotate", R);
   setlocalvar("Angle"+self, R);
}

void antitang(float x)
{// Calculating inverse tangent using infinite series with less elements
// Real plane only
  float A;
  float B;
  float C;
  float D;
  float E;
  float F;
  float Z;
  int Fix;
  int Mul;
  float Hasil;

  if(x<=1 && x>=-1){
    Mul = 1;
    Fix = 0;
  } else if(x<-1){
    x = 1/x;
    Mul = -1;
    Fix = -90;
  } else {
    x = 1/x;
    Mul = -1;
    Fix = 90;
  }

  A = -0.3333*x*x*x;

  B = 0.2*x*x*x*x*x;

  C = -0.1428*x*x*x*x*x*1*x*x;

  D = 0.1111*x*x*x*x*x*1*x*x*x*x;

  E = -0.0909*x*x*x*x*x*1*x*x*x*x*x*1*x;

  F = 0.0769*x*x*x*x*x*1*x*x*x*x*x*1*x*x*x;

  Z = x + A + B + C + D + E + F; // result in radians

  Hasil = Fix + Mul*Z*57.2958; // convert to degrees

  return Hasil;
}

void antitang2(float y, float x)
{// Calculating inverse tanget with antitang above + quadrant check
// For complex plane
  float Hasil;
  float c;

  c = 0.5*2/x; // redundant but necessary

  if(x==0 && y>0){
    Hasil = 90;
  } else if(x==0 && y<0){
    Hasil = -90;
  } else if(x==0 && y==0){
    Hasil = 0; // the result is supposed to be undefined
  } else if(x>0 && y>=0){ // 1st quadrant
    Hasil = antitang(y*c);
  } else if(x>0 && y<0){ // 4th quadrant
    Hasil = antitang(y*c) + 360;
  } else if(x<0){ // 2nd & 3rd quadrant
    Hasil = antitang(y*c) + 180;
  }

  return Hasil;
}
