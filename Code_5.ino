#include <LiquidCrystal.h>
int sensorValue;
const int moisturePin = A0;             // moisteure sensor pin
const int rs = 12, en = 11, d4 = 10, d5 = 9, d6 = 8, d7 = 7;
const int thh=700;
const int thl=400;
const int motorPin = 6;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

 
void setup()
{  
  lcd.begin(16, 2);
  Serial.begin(9600);  // sets the serial port to 9600
  sensorValue = analogRead(0);                  // read analog input pin 0            
  pinMode(motorPin, OUTPUT);    
  digitalWrite(motorPin, LOW); // keep motor off initally            
  lcd.print("Smart Irrigation");
  lcd.setCursor(5,1);
  lcd.print("System");
  lcd.setCursor(6,2);
  delay(2000);                                
} 

void loop()
{
    lcd.clear();
    lcd.setCursor(0,0);
    sensorValue= analogRead(moisturePin);
    lcd.print(sensorValue);
    lcd.setCursor(0,1);
    if (sensorValue < 500) 
    {
    digitalWrite(motorPin, LOW);         // tun off motor
    lcd.print(" Pump OFF");
    }  
    if (sensorValue > 500 && sensorValue < 600)
    {
    digitalWrite(motorPin, HIGH);        //turn on motor 
    lcd.print(" Pump ON");
    }
    if (sensorValue > 600) 
    {
    digitalWrite(motorPin, HIGH);          // turn on motor   
     lcd.print(" Pump ON");
    }
    delay(1000);       // delay in between reads for stability
    
}
