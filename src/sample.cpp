#include <Arduino.h>

//#define ADC_PIN 36

#define MICROS_PER_SECOND 1000000 // [uS] ==> Number of micro-seconds per second
#define DISPLAY_PERIOD 5          // [s]=

uint32_t sampling_pin;

void sampling_initilize(uint32_t adc_pin)
{
    sampling_pin = adc_pin;
    pinMode(sampling_pin, INPUT);
}

void adc_sample(double* data, size_t sample_size, size_t sample_rate)
{
    uint64_t last_adc_read_time = 0;
    uint64_t current_time;
    size_t data_index = 0;
    uint32_t sampling_period_micros = MICROS_PER_SECOND / sample_rate;
    delay(5); // TODO remove later 5ms delay
    while (data_index < sample_size)
    {
        current_time = esp_timer_get_time();
        if (current_time - last_adc_read_time >= sampling_period_micros)
        {
            data[data_index] = analogRead(sampling_pin);
            last_adc_read_time = current_time;
            data_index++;
        }
    }
    return;
}

/**
 * @brief Samples at the highest possible frequency, and then returns the ammount of time
 * required to sample.
 * 
 * @param data 
 * @param sample_size 
 * @return uint32_t 
 */
uint32_t timed_adc_sample(double* data, size_t sample_size)
{
    for(uint32_t i=0; i<sample_size; i++)
    {
        
    }
}

void printData(uint16_t *data, size_t size)
{
    double average = 0;
    Serial.printf("Data = [");
    for (size_t i = 0; i < size; i++)
    {
        Serial.printf("%u", data[i]);
        average += data[i];
        if (i + 1 < size)
            Serial.printf(",");
    }

    average /= size;

    Serial.printf("]\n\nDone!!");
    Serial.printf("\n\n");
    Serial.printf("Average sample = %f\n", average);
    Serial.printf("Sample size = %zu\n", size);
    //Serial.printf("Sampling rate = %u\n", SAMPLE_RATE);
    Serial.printf("\n\n\n\n");
}