
// ======== VARIABLES ========

int sensorValue;

// ======== CONSTANTS ========
const int PWM_HIGH = 255;
const int PWM_LOW = 0;


const int SENSOR_HIGH = 0;
const int SENSOR_LOW = 1023;

// ======== PINS ========
const byte REDPIN = 10;
const byte GREENPIN = 9; 
const byte BLUEPIN = 11; 

const byte AUDIOPIN = A0;

int numBuckets = 3;

int brightness[3] = {0, 0, 0};    // how bright the LED is
int fadeAmount[3] = {2, 4, 6};    // how many points to fade the LED by

long secondsPassed = 0;


int safeAdd(int a, int b, int mini, int maxi) {
  int result = a + b;
  result = max(result, mini);
  result = min(result, maxi);
  return result;
}

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN , OUTPUT);
  
  // https://arduino.stackexchange.com/questions/16698/arduino-constant-clock-output
  // set up 8 MHz timer on CLOCKOUT (OC1A)
  pinMode (REDPIN, OUTPUT); 
  pinMode (GREENPIN, OUTPUT); 
  pinMode (BLUEPIN, OUTPUT); 

  pinMode (AUDIOPIN, INPUT); 
//   set up Timer 1
  //TCCR1A = bit (COM1A0);  // toggle OC1A on Compare Match
  //TCCR1B = bit (WGM12) | bit (CS10);   // CTC, no prescaling
  //OCR1A =  0;       // output every cycle

  //analogWrite(CLOCKOUT , 100);
  //digitalWrite(CLOCKOUT , HIGH);
}

// Attempted Audio Read. Failure. Audio input is just noise.
// AUDIO VARIABLES
int audioSignal = 0;
int maxSignalSeen = 0;
int singleBrightness = 0;

void loop3() {
  audioSignal = analogRead(AUDIOPIN);
  if (audioSignal > maxSignalSeen) {
    maxSignalSeen = audioSignal;
  }

  singleBrightness = map(audioSignal, 0, maxSignalSeen, 0, 100);
  analogWrite(REDPIN, singleBrightness );
  analogWrite(GREENPIN, singleBrightness );

    // Monitor input
  if (millis() / 1000 > secondsPassed) {
    audioSignal = analogRead(AUDIOPIN);
    secondsPassed++;

    Serial.println(audioSignal);
  }
  
}

// Testing All three colors
void loop() {

  // update brightness for each pin
  for (int i = 0; i < numBuckets; i++) {
    brightness[i] = brightness[i] + fadeAmount[i];
    // Safety check
    if ( brightness[i] > PWM_HIGH) {
      brightness[i] = PWM_HIGH;
      fadeAmount[i] = -fadeAmount[i];
    } else if (brightness[i] < PWM_LOW) {
      brightness[i] = PWM_LOW;
      fadeAmount[i] = -fadeAmount[i];
    }
  }
  // set the brightness of outputs
  analogWrite(REDPIN, brightness[0]);
  analogWrite(GREENPIN, brightness[1]);
  analogWrite(BLUEPIN, brightness[2]);
  
  // wait for 30 milliseconds to see the dimming effect
  delay(30);


}
