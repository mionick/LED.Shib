#include <arduinoFFT.h>
 
#define SAMPLES 8            //Must be a power of 2
#define SAMPLING_FREQUENCY 1000 //Hz, must be less than 10000 due to ADC
 
arduinoFFT FFT = arduinoFFT();
 
unsigned int sampling_period_us;
unsigned long microseconds;
 
double vReal[SAMPLES];
double vImag[SAMPLES];

const byte REDPIN = 10;
const byte GREENPIN = 9; 
const byte BLUEPIN = 11; 

const byte pins[3] = {10, 9, 11};
double maxSignalSeen = 0;

byte output[3] = {0,0,0};

void setup() {
    Serial.begin(115200);
    pinMode (REDPIN, OUTPUT); 
    pinMode (GREENPIN, OUTPUT); 
    pinMode (BLUEPIN, OUTPUT); 
 
    sampling_period_us = round(1000000*(1.0/SAMPLING_FREQUENCY));
}
 
void loop() {
   
    /*SAMPLING*/
    for(int i=0; i<SAMPLES; i++)
    {
        microseconds = micros();    //Overflows after around 70 minutes!
     
        vReal[i] = analogRead(0);
        vImag[i] = 0;
     
        while(micros() < (microseconds + sampling_period_us)){
        }
    }
 
    /*FFT*/
    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
    double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
 
    /*PRINT RESULTS*/
    //Serial.println("Peak:");
    //Serial.println(peak);     //Print out what frequency is the most dominant.
 
    for(int i=0; i<(SAMPLES/2); i++)
    {
        /*View all these three lines in serial terminal to see which frequencies has which amplitudes*/
         
        //Serial.print((i * 1.0 * SAMPLING_FREQUENCY) / SAMPLES, 1);
        //Serial.print(" ");
        //Serial.println(vReal[i], 1);    //View only this line in serial plotter to visualize the bins
    }
    //Serial.println("");
    delay(10);  //Repeat the process every second OR:
    //while(1);       //Run code once

    for (int i = 1; i < 2; i++) {
      if (vReal[i] > maxSignalSeen) {
        maxSignalSeen = vReal[i];
      }
    }

    for (int i = 1; i < 2; i++) {
        // set the brightness of outputs
        output[i-1]= ( output[i-1] + map(vReal[i], 0, maxSignalSeen, 0, 255) )/2;
        analogWrite(pins[i-1], output[i-1]);
    }
    
}
