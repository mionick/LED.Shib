
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
  
  pinMode (REDPIN, OUTPUT); 
  pinMode (GREENPIN, OUTPUT); 
  pinMode (BLUEPIN, OUTPUT); 


}

// =======================================================================================================================
//                                                  FINAL
// =======================================================================================================================

// Precalculated sine values for each angle 
const byte lights[360]={
  0,   0,   0,   0,   0,   1,   1,   2, 
  2,   3,   4,   5,   6,   7,   8,   9, 
 11,  12,  13,  15,  17,  18,  20,  22, 
 24,  26,  28,  30,  32,  35,  37,  39, 
 42,  44,  47,  49,  52,  55,  58,  60, 
 63,  66,  69,  72,  75,  78,  81,  85, 
 88,  91,  94,  97, 101, 104, 107, 111, 
114, 117, 121, 124, 127, 131, 134, 137, 
141, 144, 147, 150, 154, 157, 160, 163, 
167, 170, 173, 176, 179, 182, 185, 188, 
191, 194, 197, 200, 202, 205, 208, 210, 
213, 215, 217, 220, 222, 224, 226, 229, 
231, 232, 234, 236, 238, 239, 241, 242, 
244, 245, 246, 248, 249, 250, 251, 251, 
252, 253, 253, 254, 254, 255, 255, 255, 
255, 255, 255, 255, 254, 254, 253, 253, 
252, 251, 251, 250, 249, 248, 246, 245, 
244, 242, 241, 239, 238, 236, 234, 232, 
231, 229, 226, 224, 222, 220, 217, 215, 
213, 210, 208, 205, 202, 200, 197, 194, 
191, 188, 185, 182, 179, 176, 173, 170, 
167, 163, 160, 157, 154, 150, 147, 144, 
141, 137, 134, 131, 127, 124, 121, 117, 
114, 111, 107, 104, 101,  97,  94,  91, 
 88,  85,  81,  78,  75,  72,  69,  66, 
 63,  60,  58,  55,  52,  49,  47,  44, 
 42,  39,  37,  35,  32,  30,  28,  26, 
 24,  22,  20,  18,  17,  15,  13,  12, 
 11,   9,   8,   7,   6,   5,   4,   3, 
  2,   2,   1,   1,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0, 
  0,   0,   0,   0,   0,   0,   0,   0};


// RGB
int inputColor[3] = {255,255,255};
int currentColor[3] = {255,255,255};

// This value will oscilate between 0 and 1 in the loop.
float inputStrength = 1.0;
float currentStrength = 1.0;

float currentFadeSpeed = 0.01;
float angularSpeed = 1;

boolean isRainbow = false;
boolean isSolid = false;

int colorAngle = 0; // 0-360

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
      // Set colors with Capital letter
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

      // Properties, rainbow, solid (not fading), brightness
      case 'r':
        setRainbow();
      break;
      case 's':
        setSolid();
      break;
      case 'b':
        setStrength();
      break;
      case 'a':
        setAngularSpeed();
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

    currentFadeSpeed = value;
}

void setAngularSpeed() {
    angularSpeed = Serial.parseFloat();
}

void setRainbow() {
    float value = Serial.parseInt();

    isRainbow = value > 0;
}

void setSolid() {
    float value = Serial.parseInt();

    isSolid = value > 0;
}



void setStrength() {
    float value = Serial.parseFloat();

    // Sanitize input value
    value = min(value, 1);
    value = max(value, 0);

    inputStrength = value;
}
void setColor(int index) {
    int value = Serial.parseInt();

    // Sanitize input value
    value = min(value, PWM_HIGH);
    value = max(value, PWM_LOW);

    inputColor[index] = value;
}

void loop() {

  //update COLOR
  if (isRainbow) {
    // increment color wheel angle
    colorAngle = (int)(colorAngle + angularSpeed);
    if (colorAngle > 359) {
      colorAngle = 0;
    }

    // Lookup correct color values for this angle
    currentColor[0] = lights[(colorAngle+120)%360];
    currentColor[1] = lights[colorAngle];
    currentColor[2] = lights[(colorAngle+240)%360];
  } else {
    // Just one color.
    currentColor[0] = inputColor[0];
    currentColor[1] = inputColor[1];
    currentColor[2] = inputColor[2];
  }

  // update BRIGHTNESS
  if (isSolid) {
    currentStrength = inputStrength;
  } else {
    // Safety check
    currentStrength += currentFadeSpeed;
    if ( currentStrength > 1) {
      currentStrength = 1;
      currentFadeSpeed = -currentFadeSpeed;
    } else if (currentStrength < 0) {
      currentStrength = 0;
      currentFadeSpeed = -currentFadeSpeed;
    }
  }


  // OUTPUT
  for (int i = 0; i < numBuckets; i++) {
    brightness[i] = (int)(currentColor[i] * currentStrength);
  }
  // set the brightness of outputs
  analogWrite(REDPIN, brightness[0]);
  analogWrite(GREENPIN, brightness[1]);
  analogWrite(BLUEPIN, brightness[2]);
  
  // wait for 30 milliseconds to see the dimming effect
  delay(30);
}

