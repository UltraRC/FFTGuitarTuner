#ifndef SAMPLE_H
#define SAMPLE_H

void sampling_initilize(uint32_t adc_pin);
void adc_sample(double* data, size_t sample_size, size_t sample_rate);
void printData(uint16_t *data, size_t size);

#endif // SAMPLE_H