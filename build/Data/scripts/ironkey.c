void main()
{
    int iPlIndex = getlocalvar("player"); //Get calling player
    void vSelf = getplayerproperty(iPlIndex , "entity"); //Get calling entity
    void vAniID = getentityproperty(vSelf,"animationID"); //Get current animation ID
//    void vAniPos = getentityproperty(vSelf, "animpos"); //Get current animation frame
    int iDir = getentityproperty(vSelf, "direction");  //Get current facing direction
    int iSpeed = getentityproperty(vSelf, "speed");
    int eTime = openborvariant("elapsed_time");
    float xdir;
    float zdir;

    void iUp = playerkeys(iPlIndex, 1, "moveup"); // New key status of "Up"
    void iDown = playerkeys(iPlIndex, 1, "movedown"); // New key status of "Down"
    void iLeft = playerkeys(iPlIndex, 1, "moveleft"); // New key status of "Left"
    void iRight = playerkeys(iPlIndex, 1, "moveright"); // New key status of "Right"
    void iJump = playerkeys(iPlIndex, 1, "jump"); //New key status of "Jump"
    void iSpecial = playerkeys(iPlIndex, 1, "Special"); //New key status of "Special"
    void iAttack = playerkeys(iPlIndex, 1, "attack"); //New key status of "Attack"
    void iAttack2 = playerkeys(iPlIndex, 1, "attack2"); // New key status of "Attack 2"
    void iAttack3 = playerkeys(iPlIndex, 1, "attack3"); // New key status of "Attack 3"
    void iAttack4 = playerkeys(iPlIndex, 1, "attack4"); // New key status of "Attack 4"

    void iUpR = playerkeys(iPlIndex, 2, "moveup"); // Release status of "Up"
    void iDownR = playerkeys(iPlIndex, 2, "movedown"); // Release status of "Down"
    void iLeftR = playerkeys(iPlIndex, 2, "moveleft"); // Release status of "Left"
    void iRightR = playerkeys(iPlIndex, 2, "moveright"); // Release status of "Right"
    void iAttackR = playerkeys(iPlIndex, 2, "attack"); //Release status of "Attack"

    void iDownH = playerkeys(iPlIndex, 0, "movedown");
    void iUpH = playerkeys(iPlIndex, 0, "moveup");
    void iLeftH = playerkeys(iPlIndex, 0, "moveleft");
    void iRightH = playerkeys(iPlIndex, 0, "moveright");

//Flip while ducking
    if(vAniID == openborconstant("ANI_DUCK") ){ //Ducking?
      if(iLeft){ //Left pressed?
        changeentityproperty(vSelf, "direction", 0);
      } else if(iRight){ //Right pressed?
        changeentityproperty(vSelf, "direction", 1);
      }
    }

//Float mode switch
    if(iJump){
      if(vAniID == openborconstant("ANI_JUMPSPECIAL")){ 
        changeentityproperty(vSelf, "animation", openborconstant("ANI_JUMP"),2);
        changeentityproperty(vSelf, "tosstime", eTime);
        updateframe(vSelf, 1);
      }
    }
}
