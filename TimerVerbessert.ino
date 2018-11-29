#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd( 0x27, 16, 2);

//VARIABLEN

int MILLIS;
int SECONDS;
int MINUTES;
int MENUE;
int ZAEHLEN; 
int TIMESTAMP;
int HIGHSCORE[5];
int ZWISCHENZEIT[10][10]; 
int ZEIGEREINS;
int ZEIGERZWEI;
int SPALTEZWEI;

void setup()
  {    
    //MENUE AUFBAUEN
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("(1) START");
    lcd.setCursor(0,1);
    lcd.print("(2) ");
    lcd.setCursor(0,0);

    pinMode(2, INPUT); //Starttaste
    pinMode(3, INPUT); //Stopptaste
    pinMode(4, INPUT); //Zeitnehmen (und spiechern)
    pinMode(5, INPUT); //Stopp

    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = 0;
    OCR1A = 625;
    TCCR1B |= (1<<CS12);
    TIMSK1 |= (1<<OCIE1A);
    }
    
ISR(TIMER1_COMPA_vect){

  TCNT1 = 0;

  if(MILLIS <= 99)
  {
    MILLIS += 1;
  }
  else
  {
    MILLIS = 0;
    SECONDS += 1;
  }
  if(SECONDS > 59)
  {
    SECONDS = 0;
    MINUTES += 1;
  }
}

void TOTIMESTAMP(){
     MINUTES * 60 * 100 + SECONDS * 100 + MILLIS = TIMESTAMP;
  }

void SPEICHERN(){
      ZWISCHENZEIT[ZEIGERZWEI,SPALTEZWEI] = TIMESTAMP;
  }

void HSSPEICHERN(){
      for(i = 0; i <= 4 i++){
         if(HIGHSCORE[i] > TIMESTAMP){
            int HELP, HELP2;
            HELP = HIGHSCORE[i];
            HIGHSCORE[i] = TIMESTAMP;
            for(k= i; k >= 1; k--){
              HELP2 = HIGHSCORE[k - 1];
              HIGHSCORE[k - 1] = HELP;
              HELP = HELP2;
              }
          } 
        }
  } 


void ZEITZEIGEN(){

    lcd.setCursor(0,0);
    if(MINUTES < 10)
    {
      lcd.print("0");
    }
    lcd.print(MINUTES);
    lcd.print(".");
    if(SECONDS < 10)
    {
      lcd.print("0");
    }
    lcd.print(SECONDS);
    lcd.print(".");
    lcd.print(MILLIS);
}

void AKTIVZAEHLEN(){
     ZAEHLEN = 1;
     while(ZAEHLEN){
        ZEITZEIGEN();
        lcd.setCursor(0,0);
        if(digitalRead(3)== HIGH){
          ZAEHLEN = 0;
          lcd.setCursor(0,1);
          lcd.print("(3) ZURUCK ");
        }
      }
  }

void STOPPUHR(){
      MENUE = 1;
      ZAEHLEN = 1;
      MILLIS = SECONDS = MINUTES = 0;
      TCNT1 = 0;
      lcd.setCursor(0,1);
      lcd.print("(2) STOPP       ");
      lcd.setCursor(0,0);
      lcd.print("                ");

      AKTIVZAEHLEN();
      
      while(digitalRead(4) != HIGH){
        if(digitalRead(2)!= LOW){
            //SPEICHERN(); 
            //ERSTELLEN COUNTER FÜR FAHRER UND PLATZ
            //EINBINDER DER BEIDEN SPEICHERFUNKTIONEN UND POTENZIELLE ÜBERGABE DER VARABLEN ( GLOBAL IST HÄSSLICH)
            delay(200);
            AKTIVZAEHLEN();
            }
      }
}



void loop()

  {

    if(MENUE != 0){
    lcd.setCursor(0,0);
    lcd.print("(1) START       ");
    lcd.setCursor(0,1);
    lcd.print("(2) SPEICHER    ");
    }
    if (digitalRead(2) == HIGH)
    {
      STOPPUHR();
    }
}
