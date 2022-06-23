#include <Arduino.h>
#include "fft.h"
#include "complex.h"
#include "sample.h"

//#define DEBUG

#define N 2048                                                      // Length of data array
#define SAMPLING_FREQ 2048                                          // [Hz] ==> Samping rate
#define ADC_PIN 36                                                  // Audio sampling pin

double sample_data[N];                                              // Holds sampled audio data
complex fft_data[N];                                                // Holds the FFT data

void setup()
{
    Serial.begin(115200);
    sampling_initilize(ADC_PIN);
    Serial.printf("\n\n\n");
}

void loop()
{
    adc_sample(sample_data, N, SAMPLING_FREQ);                      // Take audio sample
    itterative_fft(sample_data, fft_data, N);                       // Calculate the FFT of audio sample

    double f_max = get_max_frequency(fft_data, N, SAMPLING_FREQ);   // Find the largest highest magnitude frequency component
    Serial.printf("Largest frequency is %.3f Hz\n", f_max);         // Print the largest frequency to the serial monitor
    
    #ifdef DEBUG
    Serial.printf("Data = [");
    for(uint32_t i=0;i<N;i++)
    {
        //Serial.printf("%.2f", magnitude(fft_data[i]));
        Serial.printf("%.2f", sample_data[i]);
        if(i<N-1) Serial.printf(", ");
    }
    Serial.printf("]\n\n");
    #endif // DEBUG
    
    delay(50);                                                      // Give time for things to settle down
}