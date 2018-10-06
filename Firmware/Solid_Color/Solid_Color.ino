
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


// =======================================================================================================================

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


// =======================================================================================================================
//                                                  SINGLE COLOR DEMO
// =======================================================================================================================
/*
 * This section will read colors from serial connection and fade that color on and off.
 * 
 */
// RGB
// Start with white so we see SOMETHING at the start.
int color[3] = {255,255,255};
// This value will oscilate between 0 and 1 in the loop.
float strength = 1.0;
float fadeSpeed = 0.1;
/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() {
    // get the new byte:
    char inChar = (char)Serial.read();
    byte selectedPin = 0;

    // Select the value to change based on input char.
    switch(inChar) {
      case 'R':
        setColor(0);
      break;
      
      case 'G':
        setColor(1);
      break;
      
      case 'B':
        setColor(2);
      break;
      
      case 'S':
        setFadeSpeed();
      break;
      
      // Default should break out of here without doing anything. Only process messages we understand.
      default:
      return;
    }


    
}

void setFadeSpeed() {
    float value = Serial.parseFloat();

    // Sanitize input value
    value = min(value, 1);
    value = max(value, 0);

    fadeSpeed = value;
}
void setColor(int index) {
    int value = Serial.parseInt();

    // Sanitize input value
    value = min(value, PWM_HIGH);
    value = max(value, PWM_LOW);

    color[index] = value;
}

void loop() {
  // Safety check
  strength += fadeSpeed;
  if ( strength > 1) {
    strength = 1;
    fadeSpeed = -fadeSpeed;
  } else if (strength < 0) {
    strength = 0;
    fadeSpeed = -fadeSpeed;
  }
  for (int i = 0; i < numBuckets; i++) {
    brightness[i] = (int)(color[i] * strength);
  }
  // set the brightness of outputs
  analogWrite(REDPIN, brightness[0]);
  analogWrite(GREENPIN, brightness[1]);
  analogWrite(BLUEPIN, brightness[2]);
  
  // wait for 30 milliseconds to see the dimming effect
  delay(30);
}





// =======================================================================================================================
// Testing All three colors in a random Cycle
void loop4() {

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
