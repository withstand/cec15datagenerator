/*==========================================================
 * jkiss.c - rand number generator JKISS
 *
 * ref: http://www0.cs.ucl.ac.uk/staff/d.jones/GoodPracticeRNG.pdf
 *========================================================*/
#include <math.h>


#include "datagenerator.h"

/* Public domain code for JKISS RNG */
/* Seed [0-4294967295] uint32 - max: 2^32 - 1 */
static unsigned int x = 123456789,y = 987654321,z = 43219876,c = 6543217; /* Seed variables */

#include <stdio.h>
void cec15_print_state()
{
	printf("%u %u %u %u ->", x, y, z, c);
}
unsigned int JKISS()
{
    unsigned long long t;
    x = 314527869 * x + 1234567;
    y ^= y << 5; 
    y ^= y >> 7; 
    y ^= y << 22;
    t = 4294584393ULL * z + c; 
    c = t >> 32; 
    z = t;
    return x + y + z;
}



void cec15_reseed(unsigned int x1, unsigned int y1, unsigned int z1, unsigned int c1)
{
	x = x1;
	y = y1;
	z = z1;
	c = c1;
}


double cec15_rand()
{
	return JKISS() / 4294967296.0;
}

#include "matrix2.h"


MAT* _m_rand_qc(MAT* m);
MAT* _myrotate(int m, MAT* Qout);
VEC* _myshift(VEC* v);
int _myuniform(int m);


void cec15_rotate(int m, double* mat)
{
	int i,j;
	MAT* Qout = m_get(m, m);
	_myrotate(m, Qout);
	for (i=0; i<Qout->m; i++)
		for (j=0; j<Qout->n; j++)
			mat[i*m+j] = Qout->me[i][j];

	M_FREE(Qout);
}

void cec15_rand_matrix(int m, int n, double* mat)
{
	int i;
	for (i=0; i<m*n; i++)
		mat[i] = cec15_rand();
}


void cec15_shift(int m, double* vec)
{
	VEC* v = v_get(m);
	_myshift(v);
	memcpy(vec, v->ve, sizeof(double)*m);
	V_FREE(v);
}
void cec15_shuffle(int m, int * shuf)
{
	int i,j;

	for (i=1; i<=m; i++)
	{
		j = _myuniform(i);
		shuf[i-1] = shuf[j-1];
		shuf[j-1] = i;
	}

}







/* generator data help functions */
MAT* _m_rand_qc(MAT* m)
{
	int i,j;
	for(i=0;i<m->m; i++)
		for (j=0; j<m->m; j++)
			m->me[i][j] = cec15_rand();
	return m;
}

MAT* _myrotate(int m, MAT* Qout)
{
	MAT *A, *QR;
	VEC *diag;
	int i;

	A = m_get(m, m);
	_m_rand_qc(A);

	QR = m_copy(A,MNULL);
	diag = v_get(A->m);
	Qout = m_resize(Qout,A->m, A->m);

	QRfactor(QR,diag);   
	//m_output(QR);

	Qout = makeQ(QR, diag, Qout);
	if ( m % 2 != 0)
		for(i=0; i<A->m; i++)
			Qout->me[i][Qout->n-1] *= -1; 

	 M_FREE(A);
	 M_FREE(QR);
	 V_FREE(diag);

	return Qout;

}


VEC* _myshift(VEC* v)
{
	int i;
	for(i=0;i<v->dim; i++)
		v->ve[i] = cec15_rand();
	return v;
}
int _myuniform(int m)
{
	return (int)(ceil(m * cec15_rand()));
}

