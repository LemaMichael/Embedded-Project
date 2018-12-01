/*
* Reference: https://www.parallax.com/sites/default/files/downloads/28015-PING-Sensor-Product-Guide-v2.0.pdf
* Note: Cannot accurately measure the distance to an object that is more than 3 meters away
* Program:  http://learn.parallax.com/KickStart
 */

#define SIG PB3  // Signal pin (Pin 11)

const int pingPin = 11;
const int vibratePin = 7;
unsigned int duration, inches;

void setup()
{
    Serial.begin(9600);
}

void checkDistance(int inches) {
    if (inches < 11) {
        digitalWrite(vibratePin, HIGH);
        Serial.println("Vibration On");
    } else {
        digitalWrite(vibratePin, LOW);
        Serial.println("Vibration Off");
    }
}

void loop() {
    DDRB |= (1<<SIG); // Set PB3 to OUTPUT PIN.
    PORTB &= ~(1<<SIG); // Ensure pin is low.
    delayMicroseconds(2);
    PORTB |= (1<<SIG); // Start ranging.
    delayMicroseconds(5); // With 5 microsecond burst
    PORTB &= ~(1<<SIG); // End Ranging
    DDRB &= ~(1<<SIG); // Set pin to INPUT
    duration = pulseIn(pingPin, HIGH); // Read echo pulse
    inches = duration / 74 / 2; // Convert to inches
    checkDistance(inches);
    Serial.println(inches); // Display Result
    delay(200); // Short Delay
    
    // VIBRATION MOTOR
    pinMode(vibratePin, OUTPUT);
}
