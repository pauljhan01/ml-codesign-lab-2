#ifndef _DOT_PROD_2A_H_
#define _DOT_PROD_2A_H_

extern "C" {
    void dot_prod_2a(const int *vec_a,  // Vector A
                     const int *vec_b,  // Vector B
                     int *results,      // Results
                     const unsigned int vector_len     // Length of A,B
    );
}

#endif