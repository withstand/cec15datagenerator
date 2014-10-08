#ifndef DATAGENERATOR_H
#define DATAGENERATOR_H

// rand number generator
void cec15_reseed(unsigned int x1, unsigned int y1, unsigned int z1, unsigned int c1);
double cec15_rand();
void cec15_rand_matrix(int m, int n, double* mat);

void cec15_rotate(int m, double* mat);
void cec15_shift(int m, double* vec);
void cec15_shuffle(int m, int * shuf);
void cec15_print_state();

#endif // DATAGENERATOR_H