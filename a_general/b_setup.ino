void setup(){
 // Initializes serial communication
  Serial.begin(9600);


  // Creates the byte for the 3 custom characters
  lcd.createChar(0, menuCursor);
  lcd.createChar(1, upArrow);
  lcd.createChar(2, downArrow);

  /***************/

  // Set up the LCD's number of columns and rows: 
  lcd.begin(16,2);
  lcd.clear();
  
  // Set the cursor at the begining of the first row
  lcd.setCursor(1,0);

  // Print Start time
  lcd.print("Atrapiece");
}
