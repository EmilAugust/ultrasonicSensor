#define echoPin 13 // Definerer trigPin sin port som er 13
#define trigPin 12 // Definerer trigPin sin port som er 12

#include <Wire.h> // Inkluderer et library. Dette libraryet er ment for kommunikasjon mellom LCD displayet.
#include <LiquidCrystal_I2C.h> // Inkluderer et library for LCD-displayet. Dette er hoved libraryet og er det viktigste.

LiquidCrystal_I2C lcd(0x3F, 16, 2); // Velger addressen til displayet og velger at displayet har en 16x2 layout. Adressen fant jeg ved å kjøre en kode i Arduino.

// Definerer variabler
long duration; // variabel for tiden det tar for lydbølgen
int distance; // variabel for distanse

void setup() {
  pinMode(trigPin, OUTPUT); // Setter trigPin(port 12) til OUTPUT
  pinMode(echoPin, INPUT); // Setter echoPin(port 13) til INPUT
  
  Serial.begin(9600); // Bestemmer hvor mye data som skal kommunisere. Dette skjer i bits per sekund.

  lcd.begin(); // Denne koden gjør at displayet skrur seg på i layouten jeg har bestemt.
}

void loop() {
  // Denne koden gjør at trigPin er aktiv og vil gi strøm i 10 mikrosekunder
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Denne koden leser echoPin og returnerer tiden det tar for lydbølgen i mikrosekunder.
  duration = pulseIn(echoPin, HIGH);
  
  // Kalkulererer distansen
  distance = duration * 0.034 / 2; // Her gjør jeg om tid til disntanse

  lcd.clear(); // Fjerner alt på displayer for å gjøre klart til nytt innhold
  lcd.print("Distance: "); // Skriver "Distance: " på displayet
  lcd.setCursor(0, 1); // Her velger jeg at den skal begynne å skrive på neste linje på displayet
  lcd.print(distance); // Her skrives distansen til ultrasonic sensoren
  lcd.print(" cm"); // Til slutt skrives det " cm" for å vise at det er målt i centimeter
  
  // Denne koden gjør at distansen vises i serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Det her resetter trigPin og gjør klart til at koden skal repiteres
  digitalWrite(trigPin, LOW);
  delay(200); // bruker delay for å ha en pause i koden. I dette tilfellet varer pausen i 0,2 sekunder.
}
