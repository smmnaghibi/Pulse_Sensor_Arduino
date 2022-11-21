#include <Adafruit_NeoPixel.h>    // Library containing 
 
// Behavior setting variables
int pulsePin = 0; // Pulse Sensor purple wire connected to analog pin 0
int blinkPin = 13; // Digital pin to blink led at each beat
int fadePin = 5; // pin to do fancy neopixel effects at each beat
int fadeRate = 0; // used to fade LED on with PWM on fadePin
 
// these variables are volatile because they are used during the interrupt service routine
volatile int BPM; // used to hold the pulse rate
volatile int Signal; // holds the incoming raw data
volatile int IBI = 600; // holds the time between beats, the Inter-Beat Interval
volatile boolean Pulse = false; // true when pulse wave is high, false when it's low
volatile boolean QS = false; // becomes true when Arduoino finds a beat.
 
// Set up use of NeoPixels
const int NUMPIXELS = 12; // Put the number of NeoPixels you are using here
const int BRIGHTNESS = 60; // Set brightness of NeoPixels here
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, fadePin, NEO_GRB + NEO_KHZ800);
 
void setup(){
 pinMode(blinkPin,OUTPUT); // pin that will blink to your heartbeat!
// Serial.begin(115200); // Serial output data for debugging or external use
 strip.begin();
 strip.setBrightness(BRIGHTNESS);
 for (int x=0; x < NUMPIXELS; x++) { // Initialize all pixels to 'off'
 strip.setPixelColor(x, strip.Color(0, 0, 0));
 }
 strip.show(); // Ensure the pixels are off 
 delay(1000); // Wait a second
 interruptSetup(); // sets up to read Pulse Sensor signal every 2mS 
}
 
void loop(){
// sendDataSerial('S', Signal); // send Processing the raw Pulse Sensor data
 if (QS == true){ // Quantified Self flag is true when arduino finds a heartbeat
 fadeRate = 255; // Set 'fadeRate' Variable to 255 to fade LED with pulse
// sendDataSerial('B',BPM); // send heart rate with a 'B' prefix
// sendDataSerial('Q',IBI); // send time between beats with a 'Q' prefix
 QS = false; // reset the Quantified Self flag for next time 
 }
 ledFadeToBeat(); // Routine that fades color intensity to the beat
 delay(20); // take a break
}
 
void ledFadeToBeat() {
 fadeRate -= 15; // Set LED fade value
 fadeRate = constrain(fadeRate,0,255); // Keep LED fade value from going into negative numbers
 setStrip(fadeRate); // Write the value to the NeoPixels 
// sendDataSerial('R',fadeRate);
}
 
void sendDataSerial(char symbol, int data ) {
// Serial.print(symbol); // symbol prefix tells Processing what type of data is coming
// Serial.println(data); // the data to send culminating in a carriage return
}
 
void setStrip(int r) { // Set the strip to one color intensity (red)
 int g = 0; // Green is set to zero (for non-red colors, change this)
 int b = 0; // Blue is set to zero (for non-red colors, change this)
 for (int x=0; x < NUMPIXELS; x++) {
 strip.setPixelColor(x, strip.Color(r, g, b));
 }
 strip.show();
}
