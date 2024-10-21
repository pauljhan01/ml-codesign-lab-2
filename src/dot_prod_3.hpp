#ifndef _DOT_PROD_3_H_
#define _DOT_PROD_3_H_

extern "C" {
    void dot_prod_3(const int *vec_a,  // Vector A
                     const int *vec_b,  // Vector B
                     int *results,      // Results
                     const unsigned int vector_len     // Length of A,B
    );
}

#endif