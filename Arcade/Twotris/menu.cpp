#include "globals.h"
#include "menu.h"
#include "square.h"

#define LI 15 //left Indent
#define SBL 10 //space between lines
#define MENU_MAX 4

byte menu(){
  
  static byte menuCursor=1;
  Square curSquare(2,SBL*menuCursor+1,TYPE_SIMPLE);
  
  ab.setCursor(LI,SBL*1);
  ab.print(F("Play"));
  ab.setCursor(LI,SBL*2);
  ab.println(F("Settings"));
  ab.setCursor(LI,SBL*3);
  ab.println(F("Info"));
  ab.setCursor(LI,SBL*4);
  ab.println(F("Credit")); 

  curSquare.draw();

  if (ab.justPressed(UP_BUTTON)){
    if (menuCursor>1)
      menuCursor--;
    else menuCursor=MENU_MAX;
  }
  if (ab.justPressed(DOWN_BUTTON)){
    if (menuCursor<MENU_MAX)
      menuCursor++;
    else menuCursor=1;
  }  

  if (ab.justPressed(A_BUTTON)){
    //if (1==cursor)
    return menuCursor;  
  }
  
  return 0;
}

byte settings(){
  
  static byte settingsCursor=1;
  Square curSquare(2,SBL*settingsCursor+1,TYPE_SLASH);

  ab.setCursor(LI,SBL*1);
  ab.print(F("'Gift'    "));
  if (globalSettings&1)
    ab.print(F("Enabled"));
  else
    ab.print(F("Disabled"));
      
  ab.setCursor(LI,SBL*2);
  ab.print(F("Grid for P1   "));
  if (globalSettings&4)
    ab.print(F("On"));
  else
    ab.print(F("Off"));
    
  ab.setCursor(LI,SBL*3);
  ab.print(F("Grid for P2   "));
  if (globalSettings&2)
    ab.print(F("On"));
  else
    ab.print(F("Off"));
  
  ab.setCursor(LI,SBL*4);
  ab.print(F("P1 Speed      "));
  ab.print((22-fallingTimerInitP1)/2);

  ab.setCursor(LI,SBL*5);
  ab.print(F("P2 Speed      "));
  ab.print((22-fallingTimerInitP2)/2);  

  curSquare.draw();

  if (ab.justPressed(UP_BUTTON)){
    if (settingsCursor>1)
      settingsCursor--;
    else settingsCursor=MENU_MAX+1;
  }
  if (ab.justPressed(DOWN_BUTTON)){
    if (settingsCursor<MENU_MAX+1)
      settingsCursor++;
    else settingsCursor=1;
  }

  if (ab.justPressed(LEFT_BUTTON)){   
    if (4==settingsCursor){
        if (fallingTimerInitP1<20)
          fallingTimerInitP1+=2;
        else
          fallingTimerInitP1=MAX_SPEED;
    }
    else if (5==settingsCursor){
        if (fallingTimerInitP2<20)
          fallingTimerInitP2+=2;
        else
          fallingTimerInitP2=MAX_SPEED;
    }
  }
  if (ab.justPressed(A_BUTTON)||ab.justPressed(RIGHT_BUTTON)){
    switch (settingsCursor){
      case 1:
        if (globalSettings&1)
          globalSettings--;
        else
          globalSettings++;
      break;     
      case 3:
        if (globalSettings&2)
          globalSettings&=253;
        else
          globalSettings|=2;
      break;
      case 2:
        if (globalSettings&4)
          globalSettings&=251;
        else
          globalSettings|=4;
      break; 
      case 4:
        if (fallingTimerInitP1>MAX_SPEED)
          fallingTimerInitP1-=2;
        else
          fallingTimerInitP1=20; //default=20
      break;
      case 5:
        if (fallingTimerInitP2>MAX_SPEED)
          fallingTimerInitP2-=2;
        else
          fallingTimerInitP2=20; //default=20
      break;      
      default:
      break;
    }
  }  

  if (ab.justPressed(B_BUTTON)){
    return MENU_BACK;     
  }  
  return 0;
}

byte info(){
  ab.println(F("Move until you reach"));
  ab.println(F("a border to change"));
  ab.println(F("direction."));
  ab.setCursor(0,26);
  ab.println(F("Hold 'Turn' to drop"));
  ab.setCursor(0,41);
  ab.println(F("P1 Turn:   P1 Move:"));
  ab.println(F("P2 Turn:A  P2 Move:B"));
  ab.print(F("Pause: Left"));
  ab.drawChar(50,41,24,1,0,1);
  ab.drawChar(115,41,25,1,0,1);
  //ab.drawChar(30,40,23,1,1,0);
  //ab.drawChar(60,40,24,1,1,0);
  
  if (ab.justPressed(B_BUTTON)){
    return MENU_BACK;     
  }
  return 0;
}

byte credit(){
  ab.println(F("       TWOTRIS"));
  ab.println(F(""));
  ab.println(F("written by"));
  ab.println(F("    C" "\x82" "dric Martin"));
  ab.println(F(""));
  ab.println(F("March 2020"));
  
  if (ab.justPressed(B_BUTTON)){
    return MENU_BACK;     
  }
  return 0; 
}

/*
  ab.println("'Gift' enabled");
  ab.println("speed  ");*/
