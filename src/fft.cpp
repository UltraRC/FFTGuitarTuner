#include <Arduino.h>
#include <stdint.h>
#include "complex.h"
#include "fft.h"

// Iterative FFT function to compute the DFT
// of given coefficient vector
//void fft(vector<cd>& a, vector<cd>& A, int log2(n))
void itterative_fft(double* array_in, complex* array_out, size_t n)
{
    // bit reversal of the given array
	for (uint32_t i = 0; i < n; ++i) {
		uint32_t rev = bitReverse(i, n);
		array_out[i] = (complex){array_in[rev], 0};
	}
	// j is iota
	const complex J = {0,1};

	for (uint32_t s = 1; s <= log2(n); ++s) {
		int m = 1 << s; // 2 power s
		int m2 = m >> 1; // m2 = m/2 -1
        complex w = {1,0};

		// principle root of nth complex
		// root of unity.
        complex wm = im_exp(PI/m2);

		for (int j = 0; j < m2; ++j) {
			for (int k = j; k < n; k += m) {
				// t = twiddle factor
                complex t = multiply(w, array_out[k + m2]);
                complex u = array_out[k];
				// similar calculating y[k]
                array_out[k] = add(u, t);
				// similar calculating y[k+n/2]
                array_out[k + m2] = subtract(u, t);
			}
			w = multiply(w, wm);
		}
	}
}

/**
 * @brief Seach for the largest peak in fft data below Nyquist frequency (N/2) and excluding DC
 * @param data_in 
 * @param N 
 * @param sampling_freq 
 */
double get_max_frequency(complex* data_in, size_t N, uint32_t sampling_freq)
{
    double max_freq = find_peak(data_in, 1, N/2);
    double delta_freq = (double)sampling_freq / (double)N; // Resolution of each frequency bin
    //Serial.printf("max_freq: %.3f, delta_freq: %.3f\n\n", max_freq, delta_freq);
    return delta_freq * max_freq;
}

/**
 * @brief Returns the index of the largest array element
 * 
 * @param data_in ==> Array of complex numbers
 * @param stop_index ==> Searches starting at index zero and finishes at stop_index
 * @return double 
 */
uint32_t find_peak(complex* data_in, size_t start_index, size_t stop_index)
{
    double max_item = 0;
    uint32_t max_item_index;

    for(uint32_t i=start_index; i<stop_index; i++)
    {
        double mag = magnitude(data_in[i]);

        if(mag > max_item)
        {
            max_item = mag;
            max_item_index = i;
        }
    }
    return max_item_index;
}


/**
 * @brief Finds the highest magnitude complex entries of an array of complex numbers
 * 
 * @param data_in ==> Array of complex numbers
 * @param freq_outputs ==> An array of the highest magnitude items passed in data_in
 * @param stop_index  ==> Encodes the index of data_in array to stop searching at
 * @param num_outputs ==> Encodes how many largest magnitude entries to find
 */

void find_peaks(complex* data_in, uint32_t* freq_outputs, size_t stop_index, size_t num_outputs)
{
    // first start by searching whole array
    
    // Store the adresses of the highest entries
    complex* highest_entries[num_outputs]; // All void pointer (0x00) by default

    // Find address of largest entry, this variable should not be updated until it is confirmed that it is not already on the list
    complex null_entry = {0,0};
    complex* largest_entry = &null_entry; // Default is first entry of data_in

    uint32_t current_index = 0;

    // Keep track of how full the freq_outputs array is
    uint32_t largest_entry_index = 0;

    while(1)
    {
        // If |data| > |max_item| THEN max_item = data
        if(magnitude(data_in[current_index]) > magnitude(*largest_entry))
        {
            if(largest_entry_index == 0)
            {
                largest_entry = &data_in[current_index];            
            }
            // Next largest entry needs to be smaller than the last LARGEST entry
            else if(magnitude(data_in[current_index]) < magnitude(*highest_entries[largest_entry_index-1]))
            {
                largest_entry = &data_in[current_index];
            }
        }
        current_index++;

        if(current_index >= stop_index)
        {
            current_index = 0;

            highest_entries[largest_entry_index] = largest_entry;
            largest_entry_index++;
            Serial.printf("MAG ==> %.5f\n", magnitude(*largest_entry));
            largest_entry = &null_entry;
        }

        if (largest_entry_index >= num_outputs) break; // When list is full
    }

    for(uint32_t i=0; i<num_outputs; i++)
    {
        Serial.printf("highest_entries[i] => %u, highest_entries => %u, sizeof(complex*) => %u\n", (uint32_t)highest_entries[i], (uint32_t)highest_entries, sizeof(complex*));
        freq_outputs[i] = ((uint32_t)highest_entries[i] - (uint32_t)data_in) / sizeof(complex*);
    }
    
}

/**
 * @brief Utility function for reversing the bits of given index x
 */
unsigned int bitReverse(uint32_t x, uint32_t N)
{
    uint32_t n = 0;
	for (uint32_t i = 0; i < log2(N); i++)
	{
		n <<= 1;
		n |= (x & 1);
		x >>= 1;
	}
	return n;
}