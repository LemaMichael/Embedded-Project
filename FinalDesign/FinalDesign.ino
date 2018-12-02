/*
* Reference: https://www.parallax.com/sites/default/files/downloads/28015-PING-Sensor-Product-Guide-v2.0.pdf
* Note: Cannot accurately measure the distance to an object that is more than 3 meters away
* Program:  http://learn.parallax.com/KickStart
 */


// Using two PING Sensors
const int signalPins[] = {10, 11}; // Left and right Signal Pins
const int vibratorPins[] = {6, 7}; // Left and right Vibrator Motor Pins
char *pingName[] = {"Left ", "Right "};
unsigned int duration, inches;

void setup()
{
    Serial.begin(9600);
    
    // VIBRATION MOTOR
     pinMode(6, OUTPUT);
     pinMode(7, OUTPUT);
}

void checkDistance(int inches, int index) {
    if (inches < 12) {
        digitalWrite(vibratorPins[index], HIGH);
        Serial.print(pingName[index]);
        Serial.print("Vibrator is ON: ");
    } else {
        digitalWrite(vibratorPins[index], LOW);
        Serial.print(pingName[index]);
        Serial.print("Vibrator is OFF: ");
    }
 }


// PING
void ping(int index) {
    pinMode(signalPins[index], OUTPUT); // Set pin to OUTPUT
    digitalWrite(signalPins[index], LOW); // Ensure pin is low
    delayMicroseconds(2);
    digitalWrite(signalPins[index], HIGH); // Start ranging
    delayMicroseconds(5); // With 5 microsecond burst
    digitalWrite(signalPins[index], LOW); // End Ranging
    pinMode(signalPins[index], INPUT); //  Set pin to INPUT
    duration = pulseIn(signalPins[index], HIGH); // Read echo pulse
    inches = duration / 74 / 2; // Convert to inches
    checkDistance(inches, index);
    Serial.print(inches); // Display Result
    Serial.println(" inches");
    delay(50); // Short Delay
}

void loop() {
  for (int i = 0; i < 2; i++) {
    ping(i);
  }
 
}
