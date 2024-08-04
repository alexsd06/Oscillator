#include <LiquidCrystal.h>
#include <TimerOne.h>

//sudo chmod a+rw /dev/ttyUSB0

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
const int read_pin = A1;
int max_oscillation = 300;
int old_freq=0;
const int outputPin = 9; // Pin to output the square wave

void togglePin() {
  digitalWrite(outputPin, digitalRead(outputPin) ^ 1); // Toggle the output pin
}

void setup() {
  lcd.begin(16, 2);
  Timer1.initialize(500); // Set the period in microseconds
  Timer1.attachInterrupt(togglePin); // Attach the interrupt service routine
  pinMode(read_pin, INPUT);
  lcd.print("Oscillator V1.0");
  Serial.begin(9600);
}

void loop() {
  lcd.setCursor(0, 1);
  int value = analogRead(read_pin);
  int frequency = map(value, 0, 1023, 0, max_oscillation);
  lcd.print ("Using: ");
  lcd.print(frequency);
  lcd.print (" HZ ");
  if (abs(frequency-old_freq)>=5) {
    int period = 1000000 / frequency; // Period in microseconds
    Timer1.setPeriod(period);
    Serial.print("[");
    Serial.print(millis());
    Serial.print("] ");
    Serial.print("Updated timer frequency to ");
    Serial.print(frequency);
    Serial.println(" HZ!");
    old_freq=frequency;
  }
}
