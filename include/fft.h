#ifndef FFT_H
#define FFT_H

#include "complex.h"

uint32_t find_peak(complex* data_in, size_t start_index, size_t stop_index);
void find_peaks(complex* data_in, uint32_t* freq_outputs, size_t stop_index, size_t num_outputs);
void itterative_fft(double* array_in, complex* array_out, size_t n);
double get_max_frequency(complex* data_in, size_t N, uint32_t sampling_freq);
// Utility functions
unsigned int bitReverse(uint32_t x, uint32_t N);

#endif // FFT_H