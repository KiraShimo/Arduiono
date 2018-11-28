#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd( 0x27, 16, 2);
//VARIABLEN
int MILLIS;
int SECONDS;
int MINUTES;
int MENUE; 

void setup()
  { 
    noInterrupts();
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = 0;
    OCR1A = 625;
    TCCR1B |= (1<<CS12);
    TIMSK1 |= (1<<OCIE1A);
    //MENUE AUFBAUEN
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("(1) START/RESET");
    lcd.setCursor(0,1);
    lcd.print("(2) STOPP");
    
    
    
    pinMode(2, INPUT); //Starttaste
    pinMode(3, INPUT); //Stopptaste
    interrupts();
  }

ISR(TIMER1_COMPA_vect){
  TCNT1 = 0;

   if(MINUTES <= 59)
  {
    if(SECONDS == 59)
      MINUTES += 1;
  }
  else{
      MINUTES = 0;
    }  

   if(SECONDS <= 59)
  {
    if(MILLIS == 59)
      SECONDS += 1;
  }
  else{
      SECONDS = 0;
    }
  
  if(MILLIS <= 59)
  {
    MILLIS += 1;
  }
  else{
      MILLIS = 0;
    }
    
  }
  
void ZEITZEIGEN()
  {
    
    lcd.print(MINUTES);
    lcd.print(".");
    lcd.print(SECONDS);
    lcd.print(".");
    lcd.print(MILLIS);
    lcd.print(".");
}

void loop()
  {
    if (digitalRead(2) == HIGH)
      {
        
      lcd.setCursor(0,0);
      lcd.print("GESTARTET ...");
      lcd.setCursor(0,1);
      while(1){
        ZEITZEIGEN();
        delay(100);
        lcd.setCursor(0,0);
        if(digitalRead(2) == LOW)break;
      }
      }
    if (digitalRead(3) == HIGH)
  {
    MENUE = 1;
    }
    
    while(MENUE == 1) {
      if (digitalRead(3) == LOW){
           ZEITZEIGEN();
           MENUE = 0;
           delay(4000);
           lcd.setCursor(0,0);
           lcd.print("(1) START/RESET");
           lcd.setCursor(0,1);
           lcd.print("(2) STOPP");
           break;
        }
    
  }
  
}
