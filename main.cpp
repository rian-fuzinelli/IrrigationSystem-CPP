#include <LiquidCrystal.h>
#include <math.h>

LiquidCrystal lcd_1(12, 11, 5, 4, 3, 2);

int response = 0;

void setup()
{
  	Serial.begin(115200);
  	lcd_1.begin(16, 2);
    
  	pinMode(A3, INPUT); // temp
  	pinMode(A2, INPUT); // umity
  	pinMode(5, OUTPUT);
  	pinMode(10, OUTPUT); // piezo
  	pinMode(6, OUTPUT); // handler CC

  	lcd_1.noCursor();
}

void loop() {
  	int umity = analogRead(A2);
  	float temperature = get_temperature();
  
  	lcd_1.setCursor(0, 0);
  	lcd_1.print(temperature);
  	lcd_1.print(" C     ");
  	lcd_1.setCursor(0, 1);
  
    if (temperature >= 25) {
      	digitalWrite(10, HIGH);
    } else {
      	digitalWrite(10, LOW);
    }
  	
  	if (umity <= 292) {
      	lcd_1.print("Irrigando...");
      	digitalWrite(6, HIGH);
    } else {
      	digitalWrite(6, LOW);
    }
  
  	if (umity >= 584) {
      	lcd_1.print("Alta umidade");
    }
  	
  
    _delay_ms(10);
}

float get_temperature() {
 	float temp = analogRead(A3);
  
  	temp = (double)temp / 1024.0; // conversion A/D
  	temp = temp * 5;  // tension
  	temp = temp - 0.5; // approximately
  	temp = temp * 100;  // convert to Celsius
  
  	return round(temp);
}

void show_tmp(float temperature) {
  	lcd_1.setCursor(0, 0);
  	lcd_1.print("1. Temperatura");
  	lcd_1.setCursor(0, 1);
  	lcd_1.print(" ");
  	lcd_1.print(temperature);
  	lcd_1.print(" C     ");
}
