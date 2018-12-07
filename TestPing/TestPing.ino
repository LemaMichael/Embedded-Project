// ---------------------------------------------------------------------------
// Example NewPing library sketch that pings 3 sensors 20 times a second.
// ---------------------------------------------------------------------------

#include <NewPing.h>

#define SONAR_NUM 3      // Number of sensors.
#define MAX_DISTANCE 400 // Maximum distance (in cm) to ping.

const int vibratorPins[2] = {5, 7}; // Left and right Vibrator Motor Pins
unsigned int inches;


NewPing sonar[SONAR_NUM] = {   // Sensor object array.
  NewPing(9, 9, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping. 
  NewPing(10, 10, MAX_DISTANCE), 
  NewPing(11, 12, MAX_DISTANCE) 

};

void checkDistance(int inches, int index) {
  if (inches < 10 && index != 2) {
       digitalWrite(vibratorPins[index], HIGH);
  } else {
      digitalWrite(vibratorPins[index], LOW);
  } 

  if (inches < 10 && index == 2) {
    digitalWrite(5, HIGH);
    digitalWrite(7, HIGH);
  } else if (inches > 10 && index == 2){
    digitalWrite(5, LOW);
    digitalWrite(7, LOW);
  }

}

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.

  // VIBRATION MOTOR
  pinMode(5, OUTPUT);
  pinMode(7, OUTPUT);
}

void loop() { 
  for (int i = 0; i < SONAR_NUM; i++) { // Loop through each sensor and display results.
    Serial.print(i);
    Serial.print("=");
    inches = sonar[i].ping_in();
    Serial.print(inches);
    Serial.print("inch ");
    checkDistance(inches, i);
    delay(120); 
  }
  Serial.println();
}
