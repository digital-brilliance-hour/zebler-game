#include "data/scripts/story/story_scroll.c"

void main()
{	
	scrollText("story3.txt",91,0.3,NULL(),0.04);
	drawstring(0360,253,1000,"Press Start To Skip");
  
	float y = getlayerproperty("background", 0, "zoffset");
	int ypos = getlocalvar("stagey");

	void blackMask = getglobalvar("Title2"); 
    float opacity = getlocalvar("opacitynum");
    if(opacity < 150) {
    	opacity += 1;
    	setlocalvar("opacitynum", opacity);
    	log(opacity);
    }
    else {
    	opacity = 150;
    }
      
    changedrawmethod(NULL(), "enabled", 1);
    changedrawmethod(NULL(), "alpha", 6);  
    changedrawmethod(NULL(), "channelb", opacity+10);
    changedrawmethod(NULL(), "channelg", opacity);
    changedrawmethod(NULL(), "channelr", opacity);
    drawsprite(blackMask, 0, 0, -1); 


	void p;
    int i, hp, mp, lv, num;
    for(i=0; i<4; i++){
        p = getplayerproperty(i, "entity");
        num = i+1;
        if(p){
       		changeentityproperty(p, "gfxshadow", 1);
       		changeentityproperty(p, "mp", 0);
            executeanimation(p, openborconstant("ANI_IDLE")); 
		    changedrawmethod(p, "enabled", 1);
		    changedrawmethod(p, "alpha", 6);  
		    changedrawmethod(p, "channelb", 0);
		    changedrawmethod(p, "channelg", 0);
		    changedrawmethod(p, "channelr", 0);
        }
    }
}

void oncreate() {
	setlocalvar("stagey", 0);
	setlocalvar("opacitynum", 0);
	changedrawmethod(NULL(), "reset", 1);
}