// Calculate the time
void CalculateTime() {
  unsigned long time = millis();

  time /= 1000;
  ss = time % 60;
  ss += orgs;
  ss %=60;

  time -= ss;
  time /= 60;
  mm = time % 60;
  mm += orgm;
  mm %=60;
  
  time -= mm;
  time /= 60;
  hh = time % 24;
  hh += orgh;
  hh %= 24;
  
/*
  time -= hh;
  time /= 24;
  dd = time;
  */
}

// Convert Analoge voltage to button number
int evaluateButton(int x) {
  int result = 0;
  if (x < 50) {
    result = 1; // right
  } else if (x < 195) {
    result = 2; // up
  } else if (x < 380) {
    result = 3; // down
  } else if (x < 555) {
    result = 4; // left
  } else if (x < 790) {
    result = 5; // select
  }
  return result;
}

// Check the button that pressed and actuate
void buttoncheck() {
  Serial.print("button check \n");
  readKey = analogRead(0);
  if (readKey < 790 && KeyPress == false) {
    lcd.clear();
    KeyPress = true;
    button = evaluateButton(readKey);
    Serial.print(button);
    Serial.print("\n");

    
    switch (state) {
      case 0: // ********** Home Screen **********
        if (button == 1 || button == 5) { // Right or Select
          state = 1;
          pointerLoc[1] = 0;
          pageLoc[1] = 0;
        }
        break;
      case 1: // ********** Main Menu **********
        switch (button) {
          case 2: // ***** Up *****
            if (pointerLoc[1] > 0) {
              pointerLoc[1]--;
            } else if (pageLoc[1] > 0) {
              pageLoc[1]--;
            }
            break;
          case 3: // ***** Down *****
            if (pointerLoc[1] < 1) {
              pointerLoc[1]++;
            } else if ((pageLoc[1] + 1) < (MenuItemNum - 1)) {
              pageLoc[1]++;
            }
            break;
          case 4: // ***** Left *****
            state = 0;
            break;
          case 1: // ***** Right *****
          case 5:
            switch (pageLoc[1] + pointerLoc[1]) {
              case 0:
                state = 2;
                pointerLoc[2] = 0;
                pageLoc[2] = 0;
                break;
              case 1:
                state = 3;
                pointerLoc[3] = 0;
                pageLoc[3] = 0;
                break;
              case 2:
                state = 0;
                break;
            }
            break;
        }
        break;
      case 2: // ********** Select Mode **********
        switch (button) {
          case 2: // ***** Up *****
            if (pointerLoc[2] > 0) {
              pointerLoc[2]--;
            } else if (pageLoc[2] > 0) {
              pageLoc[2]--;
            }
            break;
          case 3: // ***** Down *****
            if (pointerLoc[2] < 1) {
              pointerLoc[2]++;
            } else if ((pageLoc[2] + 1) < (ModeItemNum - 1)) {
              pageLoc[2]++;
            }
            break;
          case 4: // ***** Left *****
            state = 1;
            break;
          case 1: // ***** Right *****
          case 5:
            switch (pageLoc[2] + pointerLoc[2]) {
              case 0:
                Mode = 0;
                break;
              case 1:
                Mode = 1;
                break;
              case 2:
                Mode = 2;
                break;
              case 3:
                Mode = 3;
                break;
              case 4:
                state = 1;
                break;
            }
            break;
        }
        break;
      case 3: // ********** Setting **********/
        switch (button) {
          case 2: // ***** Up *****
          if(!EditClock){
            if (pointerLoc[3] > 0) {
              pointerLoc[3]--;
            } else if (pageLoc[3] > 0) {
              pageLoc[3]--;
            }
          }else{ /***EditClock is true so edit time based on settime***/
             switch (settime){
              case 1: //edit hour 
               oldhh = hh;
               newh = oldhh;
               newh++;
               newh %= 24;
               orgh = newh - hh;
                CalculateTime();   
                break;
              case 2: //edit minute
                oldmm = mm;
                newm = oldmm;      
               newm++;
               newm %= 60;
               orgm = newm - mm;
               CalculateTime();
               
                break;
              case 3: //edit seconds
               oldss = ss;
                news = oldss;
               news++;
               news %= 60;
               orgs = news - ss;
               CalculateTime();
                break;
             }
             
          }
            break;
          case 3: // ***** Down *****
            if(!EditClock){
            if (pointerLoc[3] < 1) {
              pointerLoc[3]++;
              } else if ((pageLoc[3] + 1) < (SettItemNum - 1)) {
              pageLoc[3]++;
             }
            }else{ /***EditClock is true so edit time based on settime***/
              switch (settime){
              case 1: //edit hour 
               oldhh = hh;
               newh = oldhh;
               newh--;
               if (newh == -1) {newh = 23;}
               newh %= 24;
               orgh = newh - hh;
               CalculateTime();
                break;
              case 2: //edit minute
                oldmm = mm;
               newm = oldmm;
               newm--;
               newm %= 60;
               if (newm == -1){newm = 29;}
               newm %= 60;
               orgm = newm - mm;
               CalculateTime();
             
                break;
              case 3: //edit seconds
               oldss = ss;
               news = oldss;
               news--;          
               if (news == -1) {news = 59;}
               news %= 60;
               orgs = news - ss;
               CalculateTime();
               break;
             }
            }
            break;
          case 4: // ***** Left *****
            if(!EditClock){
            state = 1;
             }else{ /*** if EditClock is true move left for editting values ***/
                if(settime == 3){
                  settime=2;
                }else if(settime == 2){
                  settime=1;
                }else if(settime == 1){
                  settime=3;
                }
             }
            break;
          case 1: // ***** Right And Select *****
          if(EditClock == true){ /*** if EditClock is true move right for editting values ***/
               if(settime == 3){
                  settime=1;
                }else if(settime == 2){
                  settime=3;
                }else if(settime == 1){
                  settime=2;
                }
                break;
          }
              
          case 5:
            switch (pageLoc[3] + pointerLoc[3]) {
              case 0:
                if(Light == true){
                   Light = false;
                }else{
                   Light = true;
                }
                break;
                
              case 1: /**set edit on or off(set value) **/
                 if(EditClock == true){
                  EditClock = false;
                  settime = 0;
                }else{
                  EditClock = true;
                  settime = 1;
                }
                break;
              case 2:
                state = 1;
                break;
            }
            break;
        }

    }

  } else if (readKey >= 790) {
    KeyPress = false;
  }
}

// Display Value on the LCD
void Display() {
  switch (state) {
    case 0: // ********** Home **********
    Serial.print("Home Screen \n");
     CalculateTime();
      lcd.setCursor(1, 0);
      lcd.print("Atrapiece");
      char time[17];
      sprintf(time, "Time : %02i:%02i:%02i",hh, mm, ss);
      lcd.setCursor(0, 1);
      lcd.print(time);
      break;
    case 1: // ********** Main Menu **********

      lcd.setCursor(1, 0);
      lcd.print(menuItems[pageLoc[1]]);

      lcd.setCursor(1, 1);
      lcd.print(menuItems[pageLoc[1] + 1]);

      lcd.setCursor(0, pointerLoc[1]);
      lcd.write(byte(0));

      if (pageLoc[1] > 0) {
        lcd.setCursor(15, 0);
        lcd.write(byte(1));
      }
      if ((pageLoc[1] + 1) < (MenuItemNum - 1)) {
        lcd.setCursor(15, 1);
        lcd.write(byte(2));
      }
      break;
    case 2: // ********** Mode **********
      lcd.setCursor(1, 0);
      lcd.print(modeItems[pageLoc[2]]);

      lcd.setCursor(1, 1);
      lcd.print(modeItems[pageLoc[2] + 1]);

      lcd.setCursor(0, pointerLoc[2]);
      lcd.write(byte(0));

      if (pageLoc[2] > 0) {
        lcd.setCursor(15, 0);
        lcd.write(byte(1));
      }
      if ((pageLoc[2] + 1) < (ModeItemNum - 1)) {
        lcd.setCursor(15, 1);
        lcd.write(byte(2));
      }
      break;
    case 3: // ********** Setting **********
      if (Light == true) {
        settItems[0] = "Light : ON";
      } else {
        settItems[0] = "Light : OFF";
      }
      
      lcd.setCursor(1, 0);
      lcd.print(settItems[pageLoc[3]]);
      if(EditClock == false){
      timesetting(settime);
      char Time[17];
      sprintf(Time,"%s:%02i:%02i:%02i",Edit,hh, mm, ss);
      settItems[1] = Time;
      lcd.setCursor(1, 1);
      lcd.print(settItems[pageLoc[3] + 1]);
     }else{
      timesetting(settime);
      char Time[17];
      sprintf(Time,"%s:%02i:%02i:%02i",Edit,hh, mm, ss);
      settItems[1] = Time;
         lcd.setCursor(1, 1);
         lcd.print(settItems[pageLoc[3] + 1]);
      }
     
      lcd.setCursor(0, pointerLoc[3]);
      lcd.write(byte(0));

      if (pageLoc[3] > 0) {
        lcd.setCursor(15, 0);
        lcd.write(byte(1));
      }
      if ((pageLoc[3] + 1) < (SettItemNum - 1)) {
        lcd.setCursor(15, 1);
        lcd.write(byte(2));
      }
     
      break;
  }
}

void timesetting(int settime) {
  switch(settime){
    case 0:
      Edit = "Edit";
      break;
    case 1:
       Edit = "Hour";
      break;
    case 2:
       Edit = "Min";
      break;
    case 3:
       Edit = "Sec ";
      break;      
  }
}

/*un used function in second method**
long CalculateMillis(long orgh,long orgm,long orgs){
//hour milli seconds
newmillis = orgh * 60 * 60 * 1000;
newmillis +=orgm * 60 * 1000;
newmillis += orgs * 1000;
 return newmillis;
}
**/
