void main()
{//Script for items
    void self = getlocalvar("self");
    void target = getlocalvar("damagetaker"); // Get player who picks the item
    int SFX = loadsample("data/sounds/coin.wav");
    int SFX2 = loadsample("data/sounds/heal.wav");

    char Item = getentityproperty(self,"defaultname");
    int MHealth = getentityproperty(target,"maxhealth"); // Get player's max health
    int Health = getentityproperty(target,"health"); // Get player's health
    int PIndex = getentityproperty(target,"playerindex"); // Get player's index
    int PScore = getplayerproperty(PIndex,"score"); // Get player's score

    if(Item=="Coin" || Item=="Coin2"){
      playsample(SFX, 0, 120, 120, 100, 0);
    } else if(Item=="Health"){
      playsample(SFX2, 0, 120, 120, 100, 0);

      if(Health==MHealth){
        changeplayerproperty(PIndex, "score", PScore+14); // Give score
      } else {
        changeentityproperty(target, "health", Health+5); // Give health
      }
      changeplayerproperty(PIndex, "score", PScore-1); // cancels score bit
    }
}