#include <LiquidCrystal.h>

LiquidCrystal lcd(10, 11, 2, 3, 4, 5, 6, 7, 8, 9);

const int sampleCount = 20;
const int delayTime = 5;
int avg[sampleCount];
const int bmpCount = 10;
int bpmAvg[10];
int bpmI = 0;
int i = 0;
int lastReadValue;
int loopCounter = 0;
int led = 12;
int lastState = 0;
unsigned long lastMs;
unsigned long elapsed;

void setup () {
  pinMode(led, OUTPUT);
  lcd.begin (2,16);
}

void loop () {  
  int readValue = analogRead(5);
  int total = 0;
  
  unsigned long ms;
  loopCounter ++;
  ms = millis();  

  avg[i] = readValue - lastReadValue;
  i++;
  if(i >= sampleCount){
     i = 0; 
  }
  lastReadValue = readValue;
  for(int ctr=0; ctr < sampleCount; ctr++){
    total += avg[ctr];
  }
  if(total -25 > 0) {
    digitalWrite(led, HIGH);
    if(lastState == 0){
      elapsed = ms - lastMs;
      lastMs = ms;
    } 
    lastState = 1;
  } else {
    digitalWrite(led, LOW);
    lastState = 0; 
  }
  if(loopCounter == 100){
    lcd.setCursor(0,0);
    lcd.print("       ");
    lcd.setCursor(0,0);
        
    lcd.print(60000 / elapsed);

    lcd.setCursor(0,1);
    lcd.print("       ");
    lcd.setCursor(0,1); 
    lcd.print(ms);

    loopCounter = 0;
  }
  delay(delayTime);
}


