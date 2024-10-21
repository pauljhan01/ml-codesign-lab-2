#include "dot_prod_2b.hpp"

//TODO (1): Set block size
//#define BLOCK_SIZE 16

const unsigned int BLOCK_SIZE = 16;
//TRIPCOUNT identifier
const unsigned int VECTOR_SIZE = 20480;
const unsigned int NUM_CHUNK = VECTOR_SIZE / BLOCK_SIZE;
const unsigned int REMAINING = VECTOR_SIZE % BLOCK_SIZE;
const unsigned int ITERATIONS = (REMAINING == 0) ? NUM_CHUNK : NUM_CHUNK + 1;
const unsigned int FINAL_WRITE = (REMAINING == 0) ? BLOCK_SIZE : REMAINING;


extern "C" {
void dot_prod_2b(const int *vec_a,     // Read-Only Vector 1
          const int *vec_b,         // Read-Only Vector 2
          int *results,             // Output Result
          const unsigned int vector_len //Vector size
) {

//TODO (2): Determine the correct depth
#pragma HLS INTERFACE m_axi port = vec_a offset = slave depth = 20480 bundle = gmem
#pragma HLS INTERFACE m_axi port = vec_b offset = slave depth = 20480 bundle = gmem
#pragma HLS INTERFACE m_axi port = results offset = slave depth=1 bundle = gmem

#pragma HLS INTERFACE s_axilite port = vec_a bundle = control
#pragma HLS INTERFACE s_axilite port = vec_b bundle = control
#pragma HLS INTERFACE s_axilite port = results bundle = control
#pragma HLS INTERFACE s_axilite port = vector_len bundle = control
#pragma HLS INTERFACE s_axilite port = return bundle = control

    unsigned int va_buffer[BLOCK_SIZE];   // Local SRAM to store vector A
    unsigned int vb_buffer[BLOCK_SIZE];   // Local SRAM to store vector B
    unsigned int temp_buffer[BLOCK_SIZE];
    unsigned int vout_buffer[1];          // Local Register to store result

    vout_buffer[0] = 0;
    for (int i = 0; i < ITERATIONS; i++) {
        
            //TODO (3): Load the buffers
            for(int j = 0; j < BLOCK_SIZE; j++){
                load:{
                    va_buffer[j] = vec_a[i * BLOCK_SIZE + j];
                    vb_buffer[j] = vec_b[i * BLOCK_SIZE + j];
                }
            }
            compute:{
                for(int j = 0; j < BLOCK_SIZE; j++){
                    temp_buffer[j] = va_buffer[j] * vb_buffer[j];
                }
            }
            //TODO (4) do the dot product!

    }
    for (int j = 0; j < BLOCK_SIZE; j++) {
        vout_buffer[0] += temp_buffer[j];
    }

    store:
        //TODO (5): write vout_buffer back to results
        results[0] = vout_buffer[0];
    }
}