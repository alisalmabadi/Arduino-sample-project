// Calculate the time
void CalculateTime() {
  unsigned long time = millis();

  time /= 1000;
  ss = time % 60;

  time -= ss;
  time /= 60;
  mm = time % 60;

  time -= mm;
  time /= 60;
  hh = time % 24;

  time -= hh;
  time /= 24;
  dd = time;
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
  Serial.print("button check\n");
  readKey = analogRead(0);
  if (readKey < 790 && KeyPress == false) {
    lcd.clear();
    KeyPress = true;
    button = evaluateButton(readKey);
    Serial.print(button);
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
      case 3: // ********** Setting **********
        switch (button) {
          case 2: // ***** Up *****
            if (pointerLoc[3] > 0) {
              pointerLoc[3]--;
            } else if (pageLoc[3] > 0) {
              pageLoc[3]--;
            }
            break;
          case 3: // ***** Down *****
            if (pointerLoc[3] < 1) {
              pointerLoc[3]++;
            } else if ((pageLoc[3] + 1) < (SettItemNum - 1)) {
              pageLoc[3]++;
            }
            break;
          case 4: // ***** Left *****
            state = 1;
            break;
          case 1: // ***** Right *****
          case 5:
            switch (pageLoc[3] + pointerLoc[3]) {
              case 0:
                Light = ~Light;
                break;
              case 1:
                ;
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
      lcd.setCursor(1, 0);
      lcd.print("Atrapiece");
      char time[17];
      sprintf(time, "%02i days %02i:%02i:%02i", dd, hh, mm, ss);
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

      char Time[17];
      sprintf(Time, "%02i days %02i:%02i:%02i", dd, hh, mm, ss);
      settItems[1] = Time;

      lcd.setCursor(1, 0);
      lcd.print(settItems[pageLoc[3]]);

      lcd.setCursor(1, 1);
      lcd.print(settItems[pageLoc[3] + 1]);

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
